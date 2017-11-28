#ifndef LEVEL0_H
#define LEVEL0_H

#include <memory>
#include <string>

extern const unsigned seed;
extern const bool isRandom;
extern const int levelNum;

class Block;

class Level0: public Level {
  std::string filename;
 public:
  Level0(std::string filename = "sequence.txt");
  std::unique_ptr<Block> createBlock() override;
};

#endif