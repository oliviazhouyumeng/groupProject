#ifndef LEVEL3_H
#define LEVEL3_H

#include <string>

class Level3: public Level {
	std::string seqFile;
 public:
  Level3();
  void setSeq(std::string sfile) override;
  std::string createBlock() const override;
};

#endif
