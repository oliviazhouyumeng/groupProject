#ifndef LBLOCK_H
#define LBLOCK_H
#include "block.h"

class LBlock : public Block {
public:
    void left(Grid &g) override;
    void right(Grid &g) override;
    void down(Grid &g) override;
    void clockwise(Grid &g) override;
    void counterclockwise(Grid &g) override;
    void drop(Grid &g) override;
};

#endif
