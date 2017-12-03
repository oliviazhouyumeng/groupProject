#ifndef LEVEL1_H
#define LEVEL1_H

#include <string>
#include "level.h"

class Level1: public Level {
	int genRand();
 public:
  Level1();
  std::string createBlock() override;
  void setSeq(std::string sfile) override;
};

#endif
