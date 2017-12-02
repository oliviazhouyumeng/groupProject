#ifndef JBLOCK_H
#define JBLOCK_H
#include "block.h"
#include "grid.h"

class JBlock : public Block {
public:
    JBlock(Grid &g, int level);
    void left(Grid &g) override;
    void right(Grid &g) override;
    void down(Grid &g) override;
    void clockwise(Grid &g) override;
    void counterclockwise(Grid &g) override;
    void drop(Grid &g) override;
};

#endif
