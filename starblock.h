#ifndef STARBLOCK_H
#define STARBLOCK_H
#include "block.h"

class StarBlock : public Block {
public:
    void left() override;
    void right() override;
    void down() override;
    void clockwise() override;
    void counterclockwise() override;
    void drop() override;
};

#endif
