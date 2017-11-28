#ifndef LEVEL2_H
#define LEVEL2_H

#include <memory>

class LevelImpl;
class Block;

class Level2: public Level {
 public:
  Level(int levelNum = 2, bool isRandom = true);
  std::unique_ptr<Block> createBlock();
}

#endif
