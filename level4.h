#ifndef LEVEL4_H
#define LEVEL4_H

#include <memory>
#include <string>

extern std::string seq;
extern unsigned seedNum;
extern bool isRand;
extern const int lNum;

class Level4: public Level {
	std::string seqFile;
 public:
  Level4();
  void setSeq(std::string sfile);
  std::string createBlock() override;
};

#endif