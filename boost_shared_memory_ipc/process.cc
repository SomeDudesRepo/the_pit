#include <signal.h>

#include <atomic>
#include <cstdio>
#include <condition_variable>
#include <future>
#include <iostream>
#include <mutex>

#include "boost/interprocess/shared_memory_object.hpp"
#include "boost/interprocess/mapped_region.hpp"
#include "boost/interprocess/sync/scoped_lock.hpp"

#include "queue_struct.h"

using namespace boost::interprocess;

std::mutex g_mutex;
std::condition_variable g_cond_var;
std::atomic_bool g_ctrlc_pressed(false);

void SigHandler(int signum) {
  std::cout << "Signal received: " << signum << std::endl;
  g_ctrlc_pressed.store(true);
  g_cond_var.notify_one();
}

int main () {
  signal(SIGINT, SigHandler);
  signal(SIGTERM, SigHandler);

  // Create a shared memory object.
  shared_memory_object shm(open_only, "MySharedMemory", read_write);

  try {
    // Map the whole shared memory in this process
    mapped_region region(shm,          // What to map
                         read_write);  // Map it as read-write

    // Get the address of the mapped region
    void* addr = region.get_address();

    // Obtain a pointer to the shared structure
    IpcBidirectionalQueue* data = static_cast<IpcBidirectionalQueue*>(addr);

    std::vector<std::string> test_strings(TestVector(50, "process")), received_strings;
    std::cout << "Process will try to send " << test_strings.size() << " strings." << std::endl;

    auto receiving_future = 
        std::async(std::launch::async,
                   [&received_strings, &data] () {
                     while (!g_ctrlc_pressed.load()) {
                       scoped_lock<interprocess_mutex> lock(data->pwcr_mutex);
                       if (!data->child_read.timed_wait(
                               lock,
                               Until(boost::posix_time::milliseconds(100)),
                               [&data] ()->bool { return data->message_from_parent; }))
                         continue;

                       // Print the message
                       std::cout << data->parent_message << std::endl;
                       received_strings.push_back(std::string(data->parent_message));
                       // Notify the other process that the buffer is empty
                       data->message_from_parent = false;
                       data->parent_write.notify_one();
                     }
                   });

    auto sending_future = 
        std::async(std::launch::async,
                   [&test_strings, &data] () {
                     auto it(test_strings.begin());
                     while (it != test_strings.end()) {
                       scoped_lock<interprocess_mutex> lock(data->cwpr_mutex);
                       if (!data->child_write.timed_wait(
                               lock,
                               Until(boost::posix_time::milliseconds(100)),
                               [&data] ()->bool { return !data->message_from_child; }))
                         continue;

                       // Print the message
                       std::cout << (*it) << std::endl;
                       std::sprintf(data->child_message, "%s", (*it).c_str());
                       // Notify the other process that the buffer is full
                       data->message_from_child = true;
                       data->child_read.notify_one();
                       ++it;
                     }
                   });
    sending_future.get();
    receiving_future.get();
  }
  catch(interprocess_exception &ex) {
    std::cout << ex.what() << std::endl;
    return 1;
  }

  return 0;
}
