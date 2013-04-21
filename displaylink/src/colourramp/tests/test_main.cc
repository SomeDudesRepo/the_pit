#include <gtest/gtest.h>

int main(int argc, char **argv) {
  testing::FLAGS_gtest_catch_exceptions = false;
  testing::InitGoogleTest(&argc, argv);
  int result(RUN_ALL_TESTS());
  int test_count = testing::UnitTest::GetInstance()->test_to_run_count();
  return (test_count == 0) ? -1 : result;
}
