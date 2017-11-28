#include <memory>
#include "level.h"
#include "LevelImpl.h"
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

Level::Level(int levelNum, bool isRandom): pimpl{make_unique<LevelImpl>(levelNum, isRandom)} {}

unique_ptr<LevelImpl> &Level::getPImpl() {
  return pimpl;
}

Level::~Level() = default;
