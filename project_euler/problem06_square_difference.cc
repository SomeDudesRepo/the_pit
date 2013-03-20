#include <stdio.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <set>
#include <boost/cstdint.hpp>

int main() {
  boost::uint64_t lowest(100), result(0);
  for (boost::uint64_t n = lowest; n >= 0 && n < 101; --n) {
    result += n * ( (n-1) * n / 2 );
  }
  std::cout << "Difference: " << 2 * result << std::endl;
  return 0;
}
