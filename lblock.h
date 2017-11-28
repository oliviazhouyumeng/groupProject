#ifndef LBLOCK_H
#define LBLOCK_H
#include "block.h"

class LBlock : public Block {
public:
    void left() override;
    void right() override;
    void down() override;
    void clockwise() override;
    void counterclockwise() override;
    void drop() override;
};

#endif
