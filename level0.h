#ifndef LEVEL0_H
#define LEVEL0_H

#include <memory>

class LevelImpl;
class Block;

class Level0: public Level {
  std::string filename = "sequence.txt";
 public:
  Level(int levelNum = 0, bool isRandom = false);
  std::unique_ptr<Block> createBlock();
}

#endif
