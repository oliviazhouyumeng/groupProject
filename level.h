#ifndef LEVEL_H
#define LEVEL_H

#include <string>

class Level {
 protected:
  int levelNum;
  bool isRandom;
  unsigned seed;
 public:
  Level(unsigned seed, bool isRandom, int levelNum);
  int getLevel() const;
  bool getRandom() const;
  void setRandom(bool isR);
  unsigned getSeed() const;
  void setSeed(unsigned seedNum);
  virtual std::string createBlock() const = 0;
  virtual ~Level() = 0;
};

#endif