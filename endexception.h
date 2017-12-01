#ifndef ENDEXCEPTION_H
#define ENDREXCEPTION_H
#include <string>

class EndException {
  std::string s;

 public:
  EndException();
  std::string getErrorMessage();
};

#endif
