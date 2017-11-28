#ifndef LEVEL1_H
#define LEVEL1_H

#include <memory>
#include <string>
#include "level.h"

extern const unsigned seedNum;
extern const bool isRand;
extern const int lNum;

class Level1: public Level {
 public:
  Level1();
  std::string createBlock() const override;
};

#endif