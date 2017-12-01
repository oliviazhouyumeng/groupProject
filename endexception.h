#ifndef ENDEXCEPTION_H
#define ENDEXCEPTION_H
#include <string>

class EndException {
  std::string s;

 public:
  EndException();
  std::string getErrorMessage();
};

#endif
