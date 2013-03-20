#include <stdio.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <set>
#include <boost/cstdint.hpp>
#include <boost/lexical_cast.hpp>

bool CheckPalindromy(boost::uint64_t number) {
  std::string check(boost::lexical_cast<std::string>(number));
  std::string reverse;
  std::string::reverse_iterator rit;
  for (rit = check.rbegin(); rit < check.rend(); rit++)
    reverse += (*rit);
  // std::cout << check << " - " << reverse << std::endl;
  return check == reverse;
}

boost::uint64_t FindLargestPalindrome(boost::uint64_t lowest, boost::uint64_t highest) {
  boost::uint64_t result(0), a(highest), temp(0); 
  while (a >= lowest) {  
    for (boost::uint64_t n = a; n >= lowest; --n) {
      temp = n * a;
      if (CheckPalindromy(temp) && temp > result)
        result = temp;
    }
    --a;
  }
  return result;
}

int main() {
  boost::uint64_t lowest(100), highest(999);  
  std::cout << "Largest palindrome: " << FindLargestPalindrome(lowest, highest) << std::endl;
  return 0;
}
