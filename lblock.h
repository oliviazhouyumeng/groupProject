#ifndef LBLOCK_H
#define LBLOCK_H
#include "abstractblock.h"

class LBlock : public AbstractBlock {
public:
    void left() override;
    void right() override;
    void down() override;
    void clockwise() override;
    void counterclockwise() override;
    void drop() override;
};

#endif
