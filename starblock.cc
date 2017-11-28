#include "abstractblock.h"
#include "starblock.h"
using namespace std;

void StarBlock::left() {} // cannot move to left
void StarBlock::right() {} // cannot move to right
void StarBlock::down();
void StarBlock::clockwise() {} // remains the same
void StarBlock::counterclockwise() {} // remains the same
void StarBlock::drop();
