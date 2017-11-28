#ifndef LEVEL_H
#define LEVEL_H

#include <memory>

class LevelImpl;
class Block;

class Level {
  std::unique_ptr<LevelImpl> pImpl;
 public:
  Level(int levelNum, bool isRandom);
  std::unique_ptr<LevelImpl> &getPImpl();
  virtual std::unique_ptr<Block> createBlock() = 0;
  virtual ~Level() = 0;
}

#endif