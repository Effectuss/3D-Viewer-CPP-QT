#ifndef SRC_VIEWER_EXCEPTION_H_
#define SRC_VIEWER_EXCEPTION_H_

#include <exception>

class ViewerException : public std::exception {
 private:
  char const *message_;

 public:
  explicit ViewerException(char const *msg) { message_ = msg; }
  using std::exception::what;
  char const *what() { return message_; }
};

#endif  // SRC_VIEWER_EXCEPTION_H_
