#include <stdio.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <boost/cstdint.hpp>
#include <boost/lexical_cast.hpp>

boost::uint64_t GetSubsets(const std::string &number) {
  boost::uint64_t each, temp, result(0);
  std::set<std::string> fivers;
  for (size_t n = 0; n < number.length()-5; ++n) {
    temp = 1;
    std::multiset<char> chset;
    chset.insert(number[n]);
    chset.insert(number[n+1]);
    chset.insert(number[n+2]);
    chset.insert(number[n+3]);
    chset.insert(number[n+4]);

    if (chset.size() != 5) {
      continue;
    }
    std::set<char>::iterator it = chset.find('0');
    if (it != chset.end()) {
      continue; 
    }

    for (it = chset.begin(); it != chset.end(); ++it) {
      each = boost::lexical_cast<boost::uint64_t>(*it); 
      if (each > 0 && each < 10) 
        temp *= each;
    }
    std::string t;
/*
    for (std::set<char>::reverse_iterator it = chset.rbegin(); it != chset.rend(); ++it) {
      t += *it;
    }
    std::pair<std::set<std::string>::iterator, bool> p = fivers.insert(t);
    if (p.second)
      std::cout << t << "\t" << temp << std::endl;
*/
    if (temp > result)
     result = temp;
  }
  return result;
}

int main() {
  std::string number("73167176531330624919225119674426574742355349194934"
                     "96983520312774506326239578318016984801869478851843"
                     "85861560789112949495459501737958331952853208805511"
                     "12540698747158523863050715693290963295227443043557"
                     "66896648950445244523161731856403098711121722383113"
                     "62229893423380308135336276614282806444486645238749"
                     "30358907296290491560440772390713810515859307960866"
                     "70172427121883998797908792274921901699720888093776"
                     "65727333001053367881220235421809751254540594752243"
                     "52584907711670556013604839586446706324415722155397"
                     "53697817977846174064955149290862569321978468622482"
                     "83972241375657056057490261407972968652414535100474"
                     "82166370484403199890008895243450658541227588666881"
                     "16427171479924442928230863465674813919123162824586"
                     "17866458359124566529476545682848912883142607690042"
                     "24219022671055626321111109370544217506941658960408"
                     "07198403850962455444362981230987879927244284909188"
                     "84580156166097919133875499200524063689912560717606"
                     "05886116467109405077541002256983155200055935729725"
                     "71636269561882670428252483600823257530420752963450");
  boost::uint64_t result = GetSubsets(number);
  std::cout << "Largest product: " << result << std::endl;
  return 0;
}
