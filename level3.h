#ifndef LEVEL3_H
#define LEVEL3_H

#include <string>

class Level3: public Level {
	std::string seqFile;
 public:
  Level3();
  void setSeq(std::string sfile);
  std::string createBlock() override;
};

#endif