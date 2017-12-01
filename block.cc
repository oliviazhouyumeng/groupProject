#include "block.h"
using namespace std;

Block::Block(size_t x, size_t y, int level, string type, bool heavy): x{x}, y{y}, level{level}, type{type}, heavy{heavy}, cells{}{}


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

