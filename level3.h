#ifndef LEVEL3_H
#define LEVEL3_H

#include <memory>

class LevelImpl;
class Block;

class Level {
 public:
  Level(int levelNum = 3, bool isRandom = true);
  std::unique_ptr<Block> createBlock();
}

#endif