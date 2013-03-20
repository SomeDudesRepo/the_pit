#include <stdio.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <set>
#include <boost/cstdint.hpp>

void SetupPrimeVector(std::vector<boost::uint64_t> *vec) {
  vec->clear();
  vec->push_back(2);
  vec->push_back(3);
  vec->push_back(5);
  vec->push_back(7);
}

int main() {
  boost::uint64_t current(9), target(2000000), result(0);
  std::vector<boost::uint64_t> prime_terms;
  SetupPrimeVector(&prime_terms);
  bool done(false);
  while (!done) {
    bool b(true);
    for (size_t n = 0; n < prime_terms.size(); ++n) {
      if (current % prime_terms.at(n) == 0) {
        n = prime_terms.size();
        b = false;
      }
    }
    if (current > target)
      done = true;
    if (b) {
      prime_terms.push_back(current);
    }
    if (prime_terms.size()%1000 == 0)
      std::cout << prime_terms.size() << "\t";
    current+=2;
  }

  std::cout << "\nPrime: " << prime_terms[prime_terms.size()-1] << std::endl;
  for (size_t n = 0; n < prime_terms.size(); ++n)
    result += prime_terms[n];

  std::cout << "\nPrime addition: " << result << std::endl;
  return 0;
}
