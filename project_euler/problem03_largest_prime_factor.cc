#include <stdio.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <set>
#include <boost/cstdint.hpp>

std::vector<boost::uint64_t> CheckForPrimeFactors(const boost::uint64_t target,
                                                  const std::vector<boost::uint64_t> &primes) {
  std::vector<boost::uint64_t> result;
  for (size_t n = 0; n < primes.size(); ++n) {
    if (target % primes[n] == 0)
      result.push_back(primes[n]);
  }
  return result;
}

void GetPrimes(const boost::uint64_t target,
               std::vector<boost::uint64_t> *primes) {
  boost::uint64_t square_root(sqrt(target)), current(9);
  while (current < square_root) {
    size_t vec_size(primes->size());
    bool b(true); 
    for (size_t n = 0; n < vec_size; ++n) {
      if (current % primes->at(n) == 0) { 
        n = primes->size();
        b = false;
      }       
    }
    if (b)
      primes->push_back(current);
    current+=2;
  }
}

void SetupPrimeVector(std::vector<boost::uint64_t> *vec) {
  vec->clear();
  vec->push_back(2);
  vec->push_back(3);
  vec->push_back(5);
  vec->push_back(7);
}

int main() {
  boost::uint64_t target(600851475143), current(9);  
  std::vector<boost::uint64_t> prime_terms;
  SetupPrimeVector(&prime_terms);
  GetPrimes(target, &prime_terms); 
  std::cout << "Primes relevant: " << prime_terms.size() << std::endl;

  std::vector<boost::uint64_t> suspects = CheckForPrimeFactors(target, prime_terms);
  std::cout << "Largest prime factor: " << suspects[suspects.size()-1] << std::endl;
  return 0;
}
