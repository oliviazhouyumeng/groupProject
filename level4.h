#ifndef LEVEL4_H
#define LEVEL4_H

#include <memory>

class LevelImpl;
class Block;

class Level4: public Level {
 public:
  Level(int levelNum = 4, bool isRandom = true);
  std::unique_ptr<Block> createBlock();
}

#endif
