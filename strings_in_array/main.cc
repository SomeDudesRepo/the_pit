#include <iostream>
#include <string>
#include <vector>

#include "boost/date_time/posix_time/posix_time.hpp"
#include "boost/random/mersenne_twister.hpp"
#include "boost/random/uniform_int.hpp"
#include "boost/random/variate_generator.hpp"

const int g_array_size(100000);
char g_string_array[g_array_size];
boost::mt19937 g_random_number_generator(
    static_cast<unsigned int>(
        boost::posix_time::microsec_clock::universal_time().time_of_day().total_microseconds()));

int RandomNumber(int max) {
  boost::uniform_int<> uniform_distribution(0, max);
  boost::variate_generator<boost::mt19937&, boost::uniform_int<>> uni(
      g_random_number_generator, 
      uniform_distribution);
  return uni() % max;
}

std::string RandomAlphaNumericString(const size_t& length) {
  static const char alpha_numerics[] =
      "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
  std::string random_string(length, 0);
  for (auto it = random_string.begin(); it != random_string.end(); ++it)
    *it = alpha_numerics[RandomNumber(61)];

  return random_string;
}

void PopulateArray() {
  std::cout << "==== PopulateArray ====" << std::endl;
  int position(0);
  for (int i(0); i != 10; ++i) {
    std::string random_string(RandomAlphaNumericString(5 + RandomNumber(5)));
    std::memcpy(g_string_array + position, random_string.c_str(), random_string.size());
    position += random_string.size() + 1;
    std::cout << random_string << std::endl;
  }
  g_string_array[++position] = '\0';
}

void PrintArray() {
  bool previous_null(false);
  std::string s;
  
  for (int n(0); n != g_array_size; ++n) {
    char c = g_string_array[n];
    if (c == '\0' && previous_null)
      break;
    
    if (c == '\0') {
      s.append(1, '\n');
      previous_null = true;
    } else {
      s.append(1, c);
      previous_null = false;
    }
  }

  std::cout << "==== PrintArray ====" << std::endl;
  std::cout << s;
}

std::vector<std::string> ExtractStrings() {
  bool previous_null(false);
  std::vector<std::string> strings(1, "");
  
  for (int n(0); n != g_array_size; ++n) {
    char c = g_string_array[n];
    if (c == '\0' && previous_null)
      break;
    
    if (c == '\0') {
      strings.push_back("");
      previous_null = true;
    } else {
      strings.back().append(1, c);
      previous_null = false;
    }
  }
  strings.pop_back();
  
  return strings;
}

void PrintStringsVector(const std::vector<std::string>& strings) {
  std::cout << "==== PrintStringsVector ====" << std::endl;
  for (const auto& s : strings)
    std::cout << s << std::endl;
}  

std::vector<int> FindWordLimits() {
  bool previous_null(false);
  std::vector<int> word_limits(1, -1);
  
  for (int n(0); n != g_array_size; ++n) {
    char c = g_string_array[n];
    if (c == '\0' && previous_null)
      break;
    
    if (c == '\0') {
      word_limits.push_back(n);
      previous_null = true;
    } else {
      previous_null = false;
    }
  } 
  return word_limits;
}

void SortArray() {
  std::vector<int> word_limits(FindWordLimits());
  while (word_limits.size() != 2) {
    for (int a(0); a != word_limits.size() - 2; ++a) {
      std::string current(g_string_array + word_limits.at(a) + 1, 
                          g_string_array + word_limits.at(a + 1)), 
                  next(g_string_array + word_limits.at(a + 1) + 1, 
                       g_string_array + word_limits.at(a + 2));
      int count(0), max(std::min(current.size(), next.size()));
      bool swap(false);
      while (count != max) {
        if (current.at(count) == next.at(count)) {
          ++count;
          continue;
        }
        
        if (current.at(count) > next.at(count))
          swap = true;
        break;
      }
      if (swap) {
        std::memcpy(g_string_array + word_limits.at(a) + 1, next.c_str(), next.size());
        word_limits.at(a + 1) = word_limits.at(a) + next.size() + 1;
        g_string_array[word_limits.at(a + 1)] = '\0';
        std::memcpy(g_string_array + word_limits.at(a + 1) + 1, current.c_str(), current.size());
      }
    }
    word_limits.pop_back();
  }
}

int main() {
  PopulateArray();

  std::vector<std::string> strings(ExtractStrings());
  
  std::sort(std::begin(strings), std::end(strings));
  PrintStringsVector(strings);
  
  SortArray();
  PrintArray();
 
  return 0;
}