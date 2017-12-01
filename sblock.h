#ifndef SBLOCK_H
#define SBLOCK_H
#include "block.h"
#include "grid.h"

class SBlock : public Block {
public:
    SBlock(Grid &g, int level);
    void left(Grid &g) override;
    void right(Grid &g) override;
    void down(Grid &g) override;
    void clockwise(Grid &g) override;
    void counterclockwise(Grid &g) override;
    void drop(Grid &g) override;
};

#endif
