#include <stdio.h>
#include <math.h>
#include <iostream>
#include <boost/cstdint.hpp>

int main() {
  boost::uint64_t temp(0), count(0), result(0), a;
  for (int n = 1000000; n > 1; --n) {
    count = 0;
    temp = n;
    while (temp != 1) {
      if (temp%2 == 0)
        temp /= 2;
      else
        temp = temp *3 + 1;
      ++count;
    }    
    if (count > result) {
      result = count;
      a = n;
    }
  }
  
  std::cout << "Largest number: " << a << " with " << result << " iterations." << std::endl;
  return 0;
}
