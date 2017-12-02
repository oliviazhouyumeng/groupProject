#include <cstdlib>
#include <string>
#include "level.h"
#include "level2.h"
#include "block.h"
#include "iblock.h"
#include "jblock.h"
#include "lblock.h"
#include "oblock.h"
#include "sblock.h"
#include "zblock.h"
#include "tblock.h"

#include "starblock.h"

using namespace std;

const unsigned seedNum = 1;
const bool isRand = true;
const int lNum = 2;

Level2::Level2(): Level{seedNum, isRand, lNum} {}

string Level2::createBlock() const {
	int gen = srand(seed) % 7;
  if (gen == 0) return "I";
  else if (gen == 1) return "J";
  else if (gen == 2) return "L";
  else if (gen == 3) return "O";
  else if (gen == 4) return "S";
  else if (gen == 5) return "Z";
  else if (gen == 6) return "T";
}