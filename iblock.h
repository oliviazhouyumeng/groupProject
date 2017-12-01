#ifndef IBLOCK_H
#define IBLOCK_H
#include "block.h"

class IBlock : public Block {
public:
    IBlock(int level, bool heavy = false);
    void left() override;
    void right() override;
    void down() override;
    void clockwise() override;
    void counterclockwise() override;
    void drop() override;
};

#endif
