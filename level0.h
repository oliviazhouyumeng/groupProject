#ifndef LEVEL0_H
#define LEVEL0_H

#include <memory>
#include <string>
#include "level.h"

extern const unsigned seedNum;
extern const bool isRand;
extern const int lNum;

class Block;

class Level0: public Level {
  std::string filename;
 public:
  Level0(std::string filename = "sequence.txt");
  std::string createBlock() override;
};

#endif