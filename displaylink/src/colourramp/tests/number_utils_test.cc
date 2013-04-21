#include <gtest/gtest.h>

#include "colourramp/exception.h"
#include "colourramp/number_utils.h"

TEST(NumberUtilsTest, GetRgbComponents) {
  RgbNumber only_red(31 << 11), only_green(63 << 5), only_blue(31);
  std::array<RgbNumber, 3> rgb(GetRgbComponents(only_red));
  ASSERT_EQ(0, rgb[0]);
  ASSERT_EQ(0, rgb[1]);
  ASSERT_EQ(31, rgb[2]);
  rgb = GetRgbComponents(only_green);
  ASSERT_EQ(0, rgb[0]);
  ASSERT_EQ(63, rgb[1]);
  ASSERT_EQ(0, rgb[2]);
  rgb = GetRgbComponents(only_blue);
  ASSERT_EQ(31, rgb[0]);
  ASSERT_EQ(0, rgb[1]);
  ASSERT_EQ(0, rgb[2]);
}

TEST(NumberUtilsTest, CheckSixteenBitSize) {
  ASSERT_THROW(CheckSixteenBitSize(-1), GeneralException);
  ASSERT_THROW(CheckSixteenBitSize(std::numeric_limits<int>::max()), GeneralException);
  ASSERT_EQ(static_cast<RgbNumber>(0), CheckSixteenBitSize(0));
  ASSERT_EQ(static_cast<RgbNumber>(std::numeric_limits<unsigned short>::max()),
            CheckSixteenBitSize(std::numeric_limits<unsigned short>::max()));
}

TEST(NumberUtilsTest, CheckForHexNumber) {
  ASSERT_THROW(CheckForHexNumber("aa"), GeneralException);
  ASSERT_THROW(CheckForHexNumber("1234"), GeneralException);
  ASSERT_THROW(CheckForHexNumber("0xzzz"), GeneralException);
  ASSERT_THROW(CheckForHexNumber("0x123z"), GeneralException);
  ASSERT_THROW(CheckForHexNumber("0x10000"), GeneralException);
  ASSERT_EQ(RgbNumber(0), CheckForHexNumber("0x0000"));
  ASSERT_EQ(RgbNumber(0), CheckForHexNumber("0x0"));
  ASSERT_EQ(RgbNumber(std::numeric_limits<unsigned short>::max()), CheckForHexNumber("0xffff"));
}

TEST(NumberUtilsTest, CheckForDecimalNumber) {
  ASSERT_THROW(CheckForDecimalNumber("-1"), GeneralException);
  ASSERT_THROW(CheckForDecimalNumber("65536"), GeneralException);
  ASSERT_THROW(CheckForDecimalNumber("aa"), GeneralException);
  ASSERT_THROW(CheckForDecimalNumber("0x1234"), GeneralException);
  ASSERT_THROW(CheckForDecimalNumber("0x1234"), GeneralException);
  ASSERT_EQ(RgbNumber(0), CheckForDecimalNumber("0"));
  ASSERT_EQ(RgbNumber(std::numeric_limits<unsigned short>::max()), CheckForDecimalNumber("65535"));
}
