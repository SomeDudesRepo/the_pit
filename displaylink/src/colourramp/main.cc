#include <array>
#include <bitset>
#include <cstdlib>
#include <iostream>
#include <locale>
#include <sstream>
#include <string>
#include <vector>

#include "colourramp/colour_ramp.h"

int main(int argc, char *argv[]) {
  try {
    ProcessArguments(argc, argv);
  }
  catch(const std::exception& e) {
    std::cout << "Error: " << e.what() << std::endl;
    return 1;
  }
  
  return 0;
}
