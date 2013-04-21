#include <array>
#include <string>
#include <vector>

typedef unsigned short RgbNumber;

RgbNumber GetRedComponent(RgbNumber number);

RgbNumber GetGreenComponent(RgbNumber number);

RgbNumber GetBlueComponent(RgbNumber number);

std::array<RgbNumber, 3> GetRgbComponents(RgbNumber number);

RgbNumber CheckSixteenBitSize(int number);

RgbNumber CheckForHexNumber(const std::string& s);

RgbNumber CheckForDecimalNumber(const std::string& s);

RgbNumber GetIntFromConsoleArgument(const char* argument);

void PrintMaskedValues(RgbNumber number);
