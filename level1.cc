#include <cstdlib>
#include <string>
#include "level.h"
#include "level1.h"
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
const int lNum = 1;

Level1::Level1(): Level{lNum, isRand, seedNum} {}

std::string Level1::createBlock() const {
	srand(seed);
	int gen = rand() % 12;
  if (gen == 0 || gen == 1) return "I";
  else if (gen == 2 || gen == 3) return "J";
  else if (gen == 4 || gen == 5) return "L";
  else if (gen == 6 || gen == 7) return "O";
  else if (gen == 8) return "S";
  else if (gen == 9) return "Z";
  else return "T";
}