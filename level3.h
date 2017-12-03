#ifndef LEVEL3_H
#define LEVEL3_H

#include "level.h"
#include <string>

class Level3: public Level {
	std::string seqFile;
	int genRand();
 public:
  Level3();
  void setSeq(std::string sfile) override;
  std::string createBlock() override;
};

#endif
