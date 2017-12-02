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
  
void IBlock::left() {
  for (auto p : pos) {
    if (p.y == 0) return;
  }
  for (auto p : pos) {
    
    p.y -= 1;
    
    // change colour
  }
}
  
void IBlock::right() {
  for (auto p : pos) {
    if (p.y == 0) return;
  }
  for (auto p : pos) {
    p.y += 1;  // change colour
  }
}

void IBlock::down() {
  for (auto p : pos) {
    if (p.y == 0) return;
  }
  for (auto p : pos) {
    p.x += 1;  // change colour
  }
}

void IBlock::clockwise() {
  if (type == "A") {
    for (auto p : pos) {
    }
    type = "B";
  } else if (type == "B") {
    for (auto p : pos) {
      
      
void IBlock::counterclockwise();
void IBlock::drop();
