#ifndef LEVEL3_H
#define LEVEL3_H

#include <memory>
#include <string>

extern std::string seq;
extern unsigned seedNum;
extern bool isRand;
extern const int lNum;

class Level3: public Level {
	std::string seqFile;
 public:
  Level3();
  void setSeq(std::string sfile);
  std::string createBlock() override;
};

#endif