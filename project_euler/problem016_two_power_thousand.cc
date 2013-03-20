#include <stdio.h>
#include <math.h>
#include <iostream>
#include <list>
#include <boost/cstdint.hpp>
#include <boost/lexical_cast.hpp>

std::string ReverseString(std::string straight) {
  std::string reverse;
  std::string::reverse_iterator rit;
  for (rit = straight.rbegin(); rit < straight.rend(); ++rit)
    reverse += (*rit);
  return reverse;
}

int main() {
  std::string nul("0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
  std::string uno("3273390607896141870013189696827599152216642046043064789483291368096133796404674554883270092325904157150886684127560071009217256545885393053328527589376");
  std::string dos("6546781215792283740026379393655198304433284092086129578966582736192267592809349109766540184651808314301773368255120142018434513091770786106657055178752");
  std::string tre("9820171823688425610039569090482797456649926138129194368449874104288401389214023664649810276977712471452660052382680213027651769637656179159985582768128");
  std::string cua("13093562431584567480052758787310396608866568184172259157933165472384535185618698219533080369303616628603546736510240284036869026183541572213314110357504");
  std::string cin("16366953039480709350065948484137995761083210230215323947416456840480668982023372774416350461629520785754433420637800355046086282729426965266642637946880");
  std::string sei("19640343647376851220079138180965594913299852276258388736899748208576802778428047329299620553955424942905320104765360426055303539275312358319971165536256");
  std::string sie("22913734255272993090092327877793194065516494322301453526383039576672936574832721884182890646281329100056206788892920497064520795821197751373299693125632");
  std::string och("26187124863169134960105517574620793217733136368344518315866330944769070371237396439066160738607233257207093473020480568073738052367083144426628220715008");
  std::string nue("29460515471065276830118707271448392369949778414387583105349622312865204167642070993949430830933137414357980157148040639082955308912968537479956748304384");

  std::string s("3273390607896141870013189696827599152216642046043064789483291368096133796404674554883270092325904157150886684127560071009217256545885393053328527589376");
  
  std::string sarr[s.length()];

  for (int n = 0; n < s.length(); ++n) {
    int a = boost::lexical_cast<int>(s.at(s.length()-1-n));
    std::string ceros;
    for (int y = 0; y < n; ++y)
      ceros += "0";
    switch(a) {
      case 0: sarr[n] = nul + ceros; break;
      case 1: sarr[n] = uno + ceros; break;
      case 2: sarr[n] = dos + ceros; break;
      case 3: sarr[n] = tre + ceros; break;
      case 4: sarr[n] = cua + ceros; break;
      case 5: sarr[n] = cin + ceros; break;
      case 6: sarr[n] = sei + ceros; break;
      case 7: sarr[n] = sie + ceros; break;
      case 8: sarr[n] = och + ceros; break;
      case 9: sarr[n] = nue + ceros; break;
    }
  }
  size_t longest(0);
  for (int y = 0; y < s.length(); ++y) {
    // std::cout << sarr[y] << std::endl;
    if (sarr[y].length() > longest)
      longest = sarr[y].length();
    sarr[y] = ReverseString(sarr[y]);
  }
  std::cout << longest << std::endl;
 
  std::list<int> sum;
  int carry(0);
  for (int e = 0; e < longest-1; ++e) {
    std::cout << e << " ";
    int temp(carry);
    for (int l = 0; l < s.length(); ++l) {
      if (sarr[l].length()-1 >= e)
        temp += boost::lexical_cast<int>(sarr[l].at(e));
    }
    sum.push_front(temp%10);
    carry = temp/10;
  }

  std::cout << std::endl;
  boost::uint64_t result(0);
  for (std::list<int>::iterator it = sum.begin(); it != sum.end(); ++it) {
    std::cout << *it << " ";
    result += *it;
  }
  std::cout << std::endl;

  std::cout << "Number: " << result << std::endl;
  return 0;
}
