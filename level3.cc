#include <cstdlib>
#include <memory>
#include "level.h"
#include "level0.h"
#include "LevelImpl.h"
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

Level2::Level2(int levelNum, bool isRandom): pimpl{make_unique<LevelImpl>(levelNum, isRandom)} {}

unique_ptr<Block> Level2::createBlock() {}