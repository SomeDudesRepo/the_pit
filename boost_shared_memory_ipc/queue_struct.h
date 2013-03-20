#include <string>
#include <queue>

#include "boost/date_time.hpp"
#include "boost/interprocess/sync/interprocess_mutex.hpp"
#include "boost/interprocess/sync/interprocess_condition.hpp"

struct trace_queue {
  enum { kMessageSize = 10000 };

  trace_queue() : message_in(false) {}
  boost::interprocess::interprocess_mutex mutex;
  boost::interprocess::interprocess_condition cond_empty;
  boost::interprocess::interprocess_condition cond_full;
  char items[kMessageSize];
  bool message_in;
};

struct IpcBidirectionalQueue {
  enum { kMessageSize = 10000 };

  IpcBidirectionalQueue()
      : cwpr_mutex(),
        pwcr_mutex(),
        parent_read(),
        parent_write(),
        child_read(),
        child_write(),
        message_from_parent(false),
        message_from_child(false) {}
  boost::interprocess::interprocess_mutex cwpr_mutex, pwcr_mutex;
  boost::interprocess::interprocess_condition parent_read, parent_write, child_read, child_write;
  char parent_message[kMessageSize], child_message[kMessageSize];
  bool message_from_parent, message_from_child;
};

std::vector<std::string> TestVector(int max_elements, const std::string& identity) {
  std::vector<std::string> v;
  int max(std::rand() % max_elements);
  for (int n(0); n != max; ++n)
    v.push_back(identity + std::to_string(n));
  return v;
}


boost::posix_time::ptime Until(const boost::posix_time::time_duration &duration) {
  return boost::posix_time::microsec_clock::universal_time() + duration;
}
