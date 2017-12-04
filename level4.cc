#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>
#include <sstream>
#include "level.h"
#include "level4.h"
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

string seq4 = "";
const unsigned seedNum4 = time(0);
bool isRand4 = true;
const int lNum4 = 4;

Level4::Level4(): 
  Level{lNum4, isRand4, seedNum4, false}, seqFile{seq4} {}

void Level4::setSeq(std::string sfile) {
  seqFile = sfile;
}

int Level4::genRand() {
  int gen;
  if (isSeed) {
    srand(seed);
  }
  gen = rand() % 9;
  if (!(gen == 0 || gen == 1)) seed = gen;
  else seed = 3 * gen / 2 + 3;
  return gen;
}

string Level4::createBlock() {
  string blocks;
  if (isRandom) {
    int gen = genRand();
    if (gen == 0) return "I"; 
    else if (gen == 1) return "J";
    else if (gen == 2) return "L";
    else if (gen == 3) return "O";
    else if (gen == 4 || gen == 5) return "S";
    else if (gen == 6 || gen == 7) return "Z";
    else return "T";
  } else {
    ifstream f{seqFile};
    ostringstream oss;
    while (f >> blocks) {
      oss << blocks << " ";
    }
    blocks = oss.str();
    return blocks;
  }
}
