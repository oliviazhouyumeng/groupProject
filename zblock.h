#ifndef ZBLOCK_H
#define ZBLOCK_H
#include "block.h"

class Grid;

class ZBlock : public Block {
public:
    ZBlock(Grid &g, int level);
    void left(Grid &g) override;
    void right(Grid &g) override;
    void down(Grid &g) override;
    void clockwise(Grid &g) override;
    void counterclockwise(Grid &g) override;
    void drop(Grid &g) override;
    void giveHint(Grid &g) override;
    void cancelHint(Grid &g) override;
};

#endif
