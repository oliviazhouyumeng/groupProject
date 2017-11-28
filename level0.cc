#include <cstdlib>
#include <memory>
#include <fstream>
#include <string>
#include "level.h"
#include "level0.h"
#include "Block.h"
#include "IBlock.h"
#include "JBlock.h"
#include "LBlock.h"
#include "OBlock.h"
#include "SBlock.h"
#include "ZBlock.h"
#include "TBlock.h"

#include "StarBlock.h"
#include "HintBlock.h"

using namespace std;

const unsigned seedNum = 1;
const bool isRand = false;
const int lNum = 0;

Level0::Level0(string filename):
  Level{seedNum, isRand, lNum}, filename{filename} {}

unique_ptr<Block> Level0::createBlock() {
  ifstream f{filename};
  string bType;
  while (f >> bType) {
    if (bType == "I") auto b = make_unique<IBlock>(...);  // need to know how IBlock is constructed (block's ctor)
    else if (bType == "J") auto b = make_unique<JBlock>(...);
    else if (bType == "L") auto b = make_unique<LBlock>(...);
    else if (bType == "O") auto b = make_unique<OBlock>(...);
    else if (bType == "S") auto b = make_unique<SBlock>(...);
    else if (bType == "Z") auto b = make_unique<ZBlock>(...);
    else if (bType == "T") auto b = make_unique<TBlock>(...);
  }
  return b;
}