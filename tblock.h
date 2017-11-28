#ifndef TBLOCK_H
#define TBLOCK_H
#include "block.h"

class TBlock : public Block {
public:
    void left() override;
    void right() override;
    void down() override;
    void clockwise() override;
    void counterclockwise() override;
    void drop() override;
};

#endif
