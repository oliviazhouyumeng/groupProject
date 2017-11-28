#ifndef LEVEL1_H
#define LEVEL1_H

#include <memory>

class LevelImpl;
class Block;

class Level1: public Level {
 public:
  Level(int levelNum = 1, bool isRandom = true);
  std::unique_ptr<Block> createBlock();
}

#endif
