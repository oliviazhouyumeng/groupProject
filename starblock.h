#ifndef STARBLOCK_H
#define STARBLOCK_H
#include "block.h"
#include "grid.h"
class StarBlock : public Block {
public:
    StarBlock(Grid &g, int level);
    void left(Grid &g) override;
    void right(Grid &g) override;
    void down(Grid &g) override;
    void clockwise(Grid &g) override;
    void counterclockwise(Grid &g) override;
    void drop(Grid &g) override;
    Posn rightLandPos(Grid &g) override;
    void giveHint(Grid &g) override;
    void cancelHint(Grid &g) override;
};

#endif
