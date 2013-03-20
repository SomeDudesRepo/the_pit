#include <stdio.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <set>
#include <boost/cstdint.hpp>

int main() {
  boost::uint64_t sum(55), element(10), divisors(0), rounds(1), max(0);
  bool done(false);
  for (int n = 0; max < 500; ++n) {
    divisors = 0;
    ++element;
    sum += element;
    std::cout << sum << "\t1-" << element << "\t";
    for (boost::uint64_t n = 1; n <= sum; ++n) {
      if (sum%n == 0) {
        ++divisors;
        std::cout << n << ",";
      }
    }
    std::cout << "\t" << divisors << std::endl;
    if (divisors > max)
      max = divisors;
  }
  std::cout << "!!!!!!!!!!!!! " << max << std::endl;
/*
  while (!done) {
    divisors = 0;
    ++element;
    sum += element;
    for (boost::uint64_t n = 1; n <= sum  && divisors < 500; ++n) {
      if (sum%n == 0)
        ++divisors;
    }
    if (divisors == 500)
      done = true;
    if (rounds%20 == 0)
      std::cout << rounds << "-" << sum << "\t";
    ++rounds;
  }
  std::cout << "\nSmallest tree number: " << sum << std::endl;
*/
  return 0;
}
