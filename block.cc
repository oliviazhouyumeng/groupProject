#include "block.h"
using namespace std;

Block::Block():lowerleft{nullptr}, type{"A"}, cells{vector<nullptr>}, heavy{false} {}

bool Block::isHeavy() const{
    return heavy;
}

void Block::cwtype() {
    switch(type) {
        case("A") type = "B";
        case("B") type = "C";
        case("C") type = "D";
        case("D") type = "A";
    }
}
void Block::ccwtype() {
    switch(type) {
        case("A") type = "D";
        case("B") type = "A";
        case("C") type = "B";
        case("D") type = "C";
    }
}
