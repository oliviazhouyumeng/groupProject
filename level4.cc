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
const long seedNum4 = time(0);
bool isRand4 = true;
const int lNum4 = 3;

Level4::Level4(): 
  Level{lNum4, isRand4, seedNum4, false}, seqFile{seq4} {}

void Level4::setSeq(string sfile) {
  seqFile = sfile;
}

string Level4::createBlock() {
  if (isRandom) {
    int gen = rand() % 7;
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
    string blocks;
    while (f >> blocks) {
      oss << blocks << " ";
    }
    blocks = oss.str();
    return blocks;
  }
}
