#include "exprexception.h"
#include <string>

using namespace std;

EndException::EndException(): s{"EndOfGame"} {}

string ExprException::getErrorMessage(){
  return s;
}
