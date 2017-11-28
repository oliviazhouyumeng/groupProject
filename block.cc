#include "block.h"
using namespace std;

bool Block::isHeavy() const{
    return heavy;
}

void Block::cwtype() {
    if (type == "A") type = "B";
    else if (type == "B") type = "C";
    else if (type == "C") type = "D";
    else if (type == "D") type = "A";
}
void Block::ccwtype() {
    if (type == "A") type = "D";
    else if (type == "B") type = "A";
    else if (type == "C") type = "B";
    else if (type == "D") type = "C";
}
