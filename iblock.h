#ifndef IBLOCK_H
#define IBLOCK_H
#include "block.h"

class IBlock : public Block {
public:
    void left(Grid &g) override;
    void right(Grid &g) override;
    void down(Grid &g) override;
    void clockwise(Grid &g) override;
    void counterclockwise(Grid &g) override;
    void drop(Grid &g) override;
};

#endif
