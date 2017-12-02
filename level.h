#ifndef LEVEL_H
#define LEVEL_H

#include <string>

class Level {
 protected:
  int levelNum;
  bool isRandom;
  unsigned seed;
 public:
  Level(int levelNum, bool isRandom, unsigned seed);
  int getLevel() const;
  bool getRandom() const;
  void setRandom(bool isR);
  unsigned getSeed() const;
  void setSeed(unsigned seedNum);
  virtual void setSeq(std::string sfile) = 0;
  virtual std::string createBlock() const = 0;
  virtual ~Level() = 0;
};

#endif