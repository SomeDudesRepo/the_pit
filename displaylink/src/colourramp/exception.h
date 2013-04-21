#ifndef EXCEPTION_H_
#define EXCEPTION_H_

#include <exception>

class GeneralException : public std::exception {
 public:
  GeneralException(const std::string& message) : message_(message) {}
  virtual const char* what() const throw() { return message_.c_str(); }

 private:
  std::string message_;
};

#endif // EXCEPTION_H_
