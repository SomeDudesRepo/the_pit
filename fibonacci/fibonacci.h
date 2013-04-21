#include <limits>

#include "exception.h"
#include "stack_check.h"

template <typename NumberType>
void CheckTypeOverflow(const NumberType& a, const NumberType& b, const NumberType& n) {
  static int max_by_two(std::numeric_limits<NumberType>::max() / 2);
  if (a >= max_by_two && b >= max_by_two)
    throw GeneralException("Exceeded int capacity when a=" + std::to_string(a) + 
                           ", b=" + std::to_string(b) + ", n=" + std::to_string(n));
}

template <typename NumberType>
class AbstractFibonacci {
 public: 
  AbstractFibonacci() {
    static_assert(std::is_integral<NumberType>(), "Type must evaulate true with std::is_integral");
  }
  
  virtual NumberType NthNumber(NumberType n) = 0;

 protected:
  static const NumberType one;
  static const NumberType two;
  
  virtual ~AbstractFibonacci() {}
};

template <typename NumberType>
const NumberType AbstractFibonacci<NumberType>::one(1);
template <typename NumberType>
const NumberType AbstractFibonacci<NumberType>::two(2);

template <typename NumberType>
class RecursiveFibonacci : public AbstractFibonacci<NumberType> {
 public:
  RecursiveFibonacci() : AbstractFibonacci<NumberType>() {}
  
  NumberType NthNumber(NumberType n) {
    if (n < AbstractFibonacci<NumberType>::one)
      throw GeneralException("n must be 1 or larger.");
    
    if (n == AbstractFibonacci<NumberType>::one || n == AbstractFibonacci<NumberType>::two)
      return AbstractFibonacci<NumberType>::one;

    return Runner(AbstractFibonacci<NumberType>::one, AbstractFibonacci<NumberType>::one, n);
  }
  
 private:
  NumberType Runner(NumberType a, NumberType b, NumberType n) {
    if (n == AbstractFibonacci<NumberType>::two)
      return b;
    
    CheckTypeOverflow(a, b, n);
    CheckStackOverflowFromRecursion();
      
    return Runner(b, a + b, --n);
  }  
};

template <typename NumberType>
class IterativeFibonacci : public AbstractFibonacci<NumberType> {
 public:
  IterativeFibonacci() : AbstractFibonacci<NumberType>() {}
  
  NumberType NthNumber(NumberType n) {
    if (n < AbstractFibonacci<NumberType>::one)
      throw GeneralException("n must be 1 or larger.");
    
    if (n == AbstractFibonacci<NumberType>::one || n == AbstractFibonacci<NumberType>::two)
      return AbstractFibonacci<NumberType>::one;

    NumberType a(AbstractFibonacci<NumberType>::one), b(AbstractFibonacci<NumberType>::one), temp;
    for (NumberType i(AbstractFibonacci<NumberType>::two); i != n; ++i) {
      CheckTypeOverflow(a, b, n);
      temp = a + b;
      std::swap(a, b);
      std::swap(b, temp);
    }
    
    return b;
  }
};


