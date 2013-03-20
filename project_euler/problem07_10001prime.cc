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
  boost::uint64_t current(9);  
  std::vector<boost::uint64_t> prime_terms;
  size_t target_size(10001);
  SetupPrimeVector(&prime_terms);
  size_t vec_size(prime_terms.size());
  while (vec_size <= target_size) {
    bool b(true);
    for (size_t n = 0; n < vec_size; ++n) {
      if (current % prime_terms.at(n) == 0) {
        n = vec_size;
        b = false;
      }
    }
    if (b)
      prime_terms.push_back(current);
    current+=2;
    vec_size = prime_terms.size();
  }

  std::cout << "Prime " << prime_terms.size()-1 << ": " << prime_terms[prime_terms.size()-2] << std::endl;
  std::cout << "Prime " << prime_terms.size() << ": " << prime_terms[prime_terms.size()-1] << std::endl;
  return 0;
}
