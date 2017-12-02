#include "block.h"
using namespace std;

Block::Block(int level, std::string type, bool heavy): level{level}, type{type}, heavy{heavy}, pos{}{}


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

vector<Posn>& Block::getPos() {
    return pos;
}

int Block::getBlockLevel() const {
    return level;
}
