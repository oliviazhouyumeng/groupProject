#ifndef JBLOCK_H
#define JBLOCK_H
#include "block.h"

class JBlock : public Block {
public:
    void left() override;
    void right() override;
    void down() override;
    void clockwise() override;
    void counterclockwise() override;
    void drop() override;
};

#endif
