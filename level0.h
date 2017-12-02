#ifndef LEVEL0_H
#define LEVEL0_H

#include <string>
#include "level.h"

class Level0: public Level {
  std::string filename;
 public:
  Level0(std::string filename = "sequence.txt");
  std::string createBlock() const override;
};

#endif