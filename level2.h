#ifndef LEVEL2_H
#define LEVEL2_H

#include <string>

class Level2: public Level {
 public:
  Level2();
  std::string createBlock() const override;
};

#endif