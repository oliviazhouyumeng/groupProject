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

std::string Level0::createBlock() const {
  return filename;
}