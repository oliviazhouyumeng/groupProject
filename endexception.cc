#include "endexception.h"
#include <string>

using namespace std;

EndException::EndException(): s{"EndOfGame"} {}

string EndException::getErrorMessage(){
  return s;
}
