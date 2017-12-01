#include "block.h"
#include "iblock.h"
using namespace std;

const string startType = "A";
const bool isHeavy = false;

IBlock::Iblock(Grid &g, int level): Block{level, startType, isHeavy} {
  if (level > 2) heavy = true;
  Posn p1{3, 0};
  Posn p2{3, 1};
  Posn p3{3, 2};
  Posn p4{3, 3};
  pos.emplace_back(p1);
  pos.emplace_back(p2);
  pos.emplace_back(p3);
  pos.emplace_back(p4);
}
  
void IBlock::left();
void IBlock::right();
void IBlock::down();
void IBlock::clockwise();
void IBlock::counterclockwise();
void IBlock::drop();
