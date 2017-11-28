#ifndef SBLOCK_H
#define SBLOCK_H
#include "block.h"

class SBlock : public Block {
public:
    void left() override;
    void right() override;
    void down() override;
    void clockwise() override;
    void counterclockwise() override;
    void drop() override;
};

#endif
