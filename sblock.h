#ifndef SBLOCK_H
#define SBLOCK_H
#include "abstractblock.h"

class SBlock : public AbstractBlock {
public:
    void left() override;
    void right() override;
    void down() override;
    void clockwise() override;
    void counterclockwise() override;
    void drop() override;
};

#endif
