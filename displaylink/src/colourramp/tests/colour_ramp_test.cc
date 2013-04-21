#include <gtest/gtest.h>

#include "colourramp/colour_ramp.h"
#include "colourramp/exception.h"
#include "colourramp/number_utils.h"

bool CheckIncrease(const std::vector<RgbNumber>& line, int jump) {
  for (size_t n(1); n < line.size() - 1; ++n) {
    if (line.at(n) != (RgbNumber(n) * jump))
      return false;
  }

  return true;
}

bool CheckDecrease(const std::vector<RgbNumber>& line, int jump) {
  for (size_t n(line.size() - 2); n > 0; --n) {
    if (line.at(line.size() - 1 - n) != (RgbNumber(n) * jump))
      return false;
  }

  return true;
}

bool OneColourTest(int width, RgbNumber left, RgbNumber right, int jump) {
  std::array<RgbNumber, 3> tl(GetRgbComponents(left)), tr(GetRgbComponents(right));
  std::vector<RgbNumber> line(CalculateLine(width, tl, tr));
  if (size_t(width) != line.size())
    return false;
  if (left != line.front())
    return false;
  if (right != line.back())
    return false;
  if (tr > tl)
    return CheckIncrease(line, jump);
  else
    return CheckDecrease(line, jump);
}

TEST(ColourMapLogicTest, TwoCorners) {
  ASSERT_TRUE(OneColourTest(16, 0, (1 << 4) - 1, 1));
  ASSERT_TRUE(OneColourTest(16, 0, (1 << 5) - 1, 2));
  ASSERT_TRUE(OneColourTest(16, (1 << 4) - 1, 0, 1));
  ASSERT_TRUE(OneColourTest(16, (1 << 5) - 1, 0, 2));
}

TEST(ColourMapLogicTest, FourCorners) {
  std::array<RgbNumber, 3> tl(GetRgbComponents(0)), tr(GetRgbComponents((1 << 4) - 1));
  std::vector<RgbNumber> two_line(CalculateLine(16, tl, tr));
  for (int y(0); y != 9; ++y)
    ASSERT_EQ(two_line, CalculateRow(tl, tr, tl, tr, 16, 9, y));

  two_line = CalculateLine(16, tr, tl);
  for (int y(0); y != 9; ++y)
    ASSERT_EQ(two_line, CalculateRow(tr, tl, tr, tl, 16, 9, y));
}

TEST(ColourMapLogicTest, GetDisplay) {
  int w(0), h(0);
  ASSERT_NO_THROW(GetDisplay("display", w, h));
  ASSERT_EQ(16, w);
  ASSERT_EQ(9, h);
}

TEST(ColourMapLogicTest, CheckArguments) {
  char  arg0[] = "programName";
  char  arg1[] = "display";
  char  arg2[] = "0";
  char  arg3[] = "1";
  char* argv1[] = {arg0, arg1, arg2, arg3};
  ASSERT_EQ("display", CheckArguments(4, argv1));
  char  arg4[] = "2";
  char  arg5[] = "3";
  char* argv2[] = {arg0, arg1, arg2, arg3, arg4, arg5};
  ASSERT_EQ("display", CheckArguments(4, argv2));

  ASSERT_THROW(CheckArguments(0, argv1), GeneralException);
  ASSERT_THROW(CheckArguments(1, argv1), GeneralException);
  ASSERT_THROW(CheckArguments(2, argv1), GeneralException);
  ASSERT_THROW(CheckArguments(3, argv1), GeneralException);
  ASSERT_THROW(CheckArguments(5, argv1), GeneralException);
  ASSERT_THROW(CheckArguments(7, argv1), GeneralException);
}
