#ifndef LEVELIMPL_H
#define LEVELIMPL_H

struct LevelImpl {
  int levelNum;
  bool isRandom;
  LevelImpl(int levelNum, bool isRandom): levelNum{levelNum}, isRandom{isRandom} {}
};

#endif