#include <stdio.h>
#include <iostream>
#include <vector>
#include <boost/cstdint.hpp>

int main() {
  boost::uint64_t count(1), temp(0);  
  std::vector<boost::uint64_t> fib_terms;
  fib_terms.push_back(1);
  fib_terms.push_back(2);
  while (fib_terms[count] < boost::uint64_t(4000000)) {
    temp = fib_terms[count] + fib_terms[count-1];
    fib_terms.push_back(temp);
    ++count;
  }
  temp = 0;
  for (size_t n = 0; n < fib_terms.size() - 1; ++n) {
    if ((n%3) == 1)
      temp += fib_terms[n];
  }
  std::cout << "Sum: " << temp << std::endl;
  return 0;
}
