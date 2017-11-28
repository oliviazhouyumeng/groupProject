#include "block.h"
using namespace std;

bool Block::isHeavy() const{
    return heavy;
}

void Block::cwtype() {
    switch(string(type)) {
        case "A": type = "B";
        case "B": type = "C";
        case "C": type = "D";
        case "D": type = "A";
    }
}
void Block::ccwtype() {
    switch(string(type)) {
        case"A": type = "D";
        case"B": type = "A";
        case"C": type = "B";
        case"D": type = "C";
    }
}
