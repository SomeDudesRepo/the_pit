#include <iostream>
#include <limits>

#include "fibonacci.h"

int main() {
  char top_of_stack;
  g_top_of_stack = &top_of_stack;
  for (int n(0); n < 10; ++n) {
    try {
      std::cout << "Fibo element #" << n << ": " << RecursiveFibonacci<int>().NthNumber(n) << std::endl;
    }
    catch(const std::exception& e) { 
      std::cout << "Exception: Round #" << n << ", " << e.what() << std::endl;
    }
  }

  std::cout << std::endl;
  
  for (int n(0); n < 50; ++n) {
    try {
      std::cout << "Fibo element #" << n << ": " << IterativeFibonacci<int>().NthNumber(n) << std::endl;
    }
    catch(const std::exception& e) { 
      std::cout << "Exception: Round #" << n << ", " << e.what() << std::endl;
    }
  }

  return 0;
}