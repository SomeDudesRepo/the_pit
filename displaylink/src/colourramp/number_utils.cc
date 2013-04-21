#include <bitset>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <locale>
#include <sstream>

#include "colourramp/exception.h"
#include "colourramp/number_utils.h"

int g_max_value(1 << 16);

RgbNumber GetRedComponent(RgbNumber number) {
  static RgbNumber red_mask(31);
  return (number >> 11) & red_mask;
}

RgbNumber GetGreenComponent(RgbNumber number) {
  static RgbNumber green_mask(63);
  return (number >> 5) & green_mask;
}

RgbNumber GetBlueComponent(RgbNumber number) {
  static RgbNumber blue_mask(31);
  return (number) & blue_mask;
}

std::array<RgbNumber, 3> GetRgbComponents(RgbNumber number) {
  std::array<RgbNumber, 3> rgb;
  rgb[0] = GetBlueComponent(number);
  rgb[1] = GetGreenComponent(number);
  rgb[2] = GetRedComponent(number);
  return rgb;
}

RgbNumber CheckSixteenBitSize(int number) {
  if (number >= g_max_value || number < 0)
    throw GeneralException("Number outside the allowed limits 0-65535.");
  return static_cast<RgbNumber>(number);
}

RgbNumber CheckForHexNumber(const std::string& s) {
  std::string message(s + " is not a hex char.");
  std::locale loc;
  size_t pos(s.find("0x"));
  if (pos == std::string::npos)
    throw GeneralException(message);

  std::string temp(s.substr(pos + 2));
  for (const auto& c : temp) {
    if (!std::isxdigit(c, loc))
      throw GeneralException(message);
  }

  int number;
  std::stringstream(s) >> std::hex >> number;
  return CheckSixteenBitSize(number);
}

RgbNumber CheckForDecimalNumber(const std::string& s) {
  std::locale loc;
  for (const auto& c : s) {
    if (!std::isdigit(c, loc)) {
      std::string message(std::string(1, c) + " is not a decimal char.");
      throw GeneralException(message);
    }
  }

  int number;
  std::stringstream(s) >> number;
  return CheckSixteenBitSize(number);
}

RgbNumber GetIntFromConsoleArgument(const char* argument) {
  std::string s(argument);
  try {
    RgbNumber potential(CheckForHexNumber(s));
    return potential;
  }
  catch(...) {
    return CheckForDecimalNumber(s);
  }
}

void PrintMaskedValues(RgbNumber number) {
  std::cout << "Number: " << std::bitset<16>(number) << std::endl;
  std::cout << "Red mask: " << std::bitset<5>(GetRedComponent(number));
  std::cout << "\tGreen mask: " << std::bitset<6>(GetGreenComponent(number));
  std::cout << "\tBlue mask: " << std::bitset<5>(GetBlueComponent(number)) << std::endl;
}
