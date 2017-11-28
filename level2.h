#ifndef LEVEL2_H
#define LEVEL2_H

#include <memory>
#include <string>

extern const unsigned seedNum;
extern const bool isRand;
extern const int lNum;

class Level2: public Level {
 public:
  Level2();
  std::string createBlock() const override;
};

#endif