#include <cstdlib>
#include <memory>
#include <fstream>
#include <string>
#include "level.h"
#include "level0.h"
#include "block.h"
#include "iblock.h"
#include "jblock.h"
#include "lblock.h"
#include "oblock.h"
#include "sblock.h"
#include "zblock.h"
#include "tblock.h"

#include "starblock.h"
#include "hintblock.h"

using namespace std;

const unsigned seedNum = 1;
const bool isRand = false;
const int lNum = 0;

Level0::Level0(string filename):
  Level{seedNum, isRand, lNum}, filename{filename} {}

shared_ptr<Block> Level0::createBlock() {
  ifstream f{filename};
  string bType;
  shared_ptr<Block> b;
  while (f >> bType) {
    if (bType == "I") {
      b = dynamic_pointer_cast<IBlock>(b);
      b = make_shared<IBlock>(...);  // need to know how IBlock is constructed for ... (block's ctor)
    } else if (bType == "J") {
      b = dynamic_pointer_cast<JBlock>(b);
      b = make_shared<JBlock>(...);
    } else if (bType == "L") {
      b = dynamic_pointer_cast<LBlock>(b);
      b = make_shared<LBlock>(...);
    } else if (bType == "O") {
      b = dynamic_pointer_cast<OBlock>(b);
      b = make_shared<OBlock>(...);
    } else if (bType == "S") {
      b = dynamic_pointer_cast<SBlock>(b);
      b = make_shared<SBlock>(...);
    } else if (bType == "Z") {
      b = dynamic_pointer_cast<ZBlock>(b);
      b = make_shared<ZBlock>(...);
    } else if (bType == "T") {
      b = dynamic_pointer_cast<JBlock>(b);
      b = make_shared<JBlock>(...);
    }
  }
  return b;
}