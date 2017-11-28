#ifndef OBLOCK_H
#define OBLOCK_H
#include "block.h"

class OBlock : public Block {
public:
    void left() override;
    void right() override;
    void down() override;
    void clockwise() override;
    void counterclockwise() override;
    void drop() override;
};

#endif
