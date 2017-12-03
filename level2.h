#ifndef LEVEL2_H
#define LEVEL2_H

#include <string>
#include "level.h"

class Level2: public Level {
	int genRand();
 public:
  Level2();
  std::string createBlock() const override;
  void setSeq(std::string sfile);
};

#endif
