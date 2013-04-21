#ifndef STACK_CHECK_H_
#define STACK_CHECK_H_

static char* g_top_of_stack;
static const int g_max_allowed_stack_usage(2048);

// http://stackoverflow.com/questions/1578878/catching-stack-overflow-exceptions-in-recursive-c-functions
int GetCurrentStackSize() {
  char local;
  return std::abs((&local) - g_top_of_stack);
}


void CheckStackOverflowFromRecursion() {
  if (GetCurrentStackSize() >= g_max_allowed_stack_usage)
    throw GeneralException("Recursion has reached the maximum stack usage of " +
                           std::to_string(g_max_allowed_stack_usage));
}

#endif  // STACK_CHECK_H_
