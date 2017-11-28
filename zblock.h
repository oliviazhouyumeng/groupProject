#ifndef ZBLOCK_H
#define ZBLOCK_H
#include "abstractblock.h"

class ZBlock : public AbstractBlock {
public:
    void left() override;
    void right() override;
    void down() override;
    void clockwise() override;
    void counterclockwise() override;
    void drop() override;
};

#endif
