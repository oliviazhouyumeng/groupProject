#include "block.h"
using namespace std;


unique_ptr<BlockImpl> Block::&getPImpl() {
}
bool Block::isHeavy() const {
    return heavy;
}
