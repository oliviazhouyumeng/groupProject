#include <cstdlib>
#include <ctime>
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

const long seedNum2 = time(0);
const bool isRand2 = true;
const int lNum2 = 2;

Level2::Level2(): Level{lNum2, isRand2, seedNum2, false} {}

int Level2::genRand() {
  int gen;
  srand(seed);
  gen = rand() % 7;
  if (!(gen == 0 || gen == 1)) seed = gen;
  else seed = 3 * gen / 2 + 3;
  return gen;
}

string Level2::createBlock() {
  int gen = genRand();
  if (gen == 0) return "I";
  else if (gen == 1) return "J";
  else if (gen == 2) return "L";
  else if (gen == 3) return "O";
  else if (gen == 4) return "S";
  else if (gen == 5) return "Z";
  else return "T";
}

void Level2::setSeq(std::string sfile) {}
