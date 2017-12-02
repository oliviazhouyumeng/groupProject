#include <cstdlib>
#include <string>
#include <fstream>
#include <sstream>
#include "level.h"
#include "level4.h"
#include "Block.h"
#include "IBlock.h"
#include "JBlock.h"
#include "LBlock.h"
#include "OBlock.h"
#include "SBlock.h"
#include "ZBlock.h"
#include "TBlock.h"

#include "StarBlock.h"

using namespace std;

string seq = "";
unsigned seedNum = 1;
bool isRand = true;
const int lNum = 4;

Level4::Level4(): 
  seqFile{seq}, Level{seedNum, isRand, lNum} {}

void Level4::setSeq(std::string sfile) {
  seqFile = sfile;
}

string Level4::createBlock() const {
  if (isRandom) {
    srand(seed);
    int gen = rand() % 9;
    if (gen == 0) return "I";  // need to know how IBlock is constructed
    else if (gen == 1) return "J";
    else if (gen == 2) return "L";
    else if (gen == 3) return "O";
    else if (gen == 4 || gen == 5) return "S";
    else if (gen == 6 || gen == 7) return "Z";
    else if (gen == 8) return "T";
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
