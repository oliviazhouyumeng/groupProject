#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <ctime>

class Level {
 protected:
  int levelNum;
  bool isRandom;
  long seed;
  bool isSeed;
 
 public:
  Level(int levelNum, bool isRandom, long seed, bool isSeed);
  int getLevel() const;
  bool getRandom() const;
  void setRandom(bool isR);
  unsigned getSeed() const;
  void setSeed(long seedNum);
  void setIsSeed(bool isseed);
  virtual void setSeq(std::string sfile) = 0;
  virtual std::string createBlock() = 0;
  virtual ~Level() = 0;
};

#endif
