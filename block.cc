#include "block.h"
using namespace std;


unique_ptr<BlockImpl> Block::&getPImpl() {
    return pImpl;
}

bool Block::isHeavy() const {
    return heavy;
}
