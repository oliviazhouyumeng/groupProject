#ifndef HINTBLOCK_H
#define HINTBLOCK_H
#include "block.h"

class HintBlock : public Block {
public:
    void left() override;
    void right() override;
    void down() override;
    void clockwise() override;
    void counterclockwise() override;
    void drop() override;
};

#endif
