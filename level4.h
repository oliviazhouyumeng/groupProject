#ifndef LEVEL4_H
#define LEVEL4_H

#include "level.h"
#include <string>

class Level4: public Level {
	std::string seqFile;
	int genRand();
 public:
  Level4();
  void setSeq(std::string sfile) override;
  std::string createBlock() const override;
};

#endif
