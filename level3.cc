#include <cstdlib>
#include <string>
#include <fstream>
#include <sstream>
#include "level.h"
#include "level3.h"
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

string seq3 = "";
const unsigned seedNum3 = time(0);
bool isRand3 = true;
const int lNum3 = 3;

Level3::Level3(): 
  Level{lNum3, isRand3, seedNum3, false}, seqFile{seq3} {}

void Level3::setSeq(string sfile) {
  seqFile = sfile;
}

int Level3::genRand() {
  if (isSeed) {
    srand(seed);
    int gen = rand() % 12;
    seed = gen;
  } else {
    srand(seed);
  }
  return gen;
}

string Level3::createBlock() const {
  if (isRandom) {
    int gen = genRand();
    if (gen == 0) return "I";  // need to know how IBlock is constructed
    else if (gen == 1) return "J";
    else if (gen == 2) return "L";
    else if (gen == 3) return "O";
    else if (gen == 4 || gen == 5) return "S";
    else if (gen == 6 || gen == 7) return "Z";
    else return "T";
  } else {
    ifstream f{seqFile};
    ostringstream oss;
    string blocks;
    while (f >> blocks) {
      oss << blocks << " ";
    }
    blocks = oss.str();
    return blocks;
  }
}
