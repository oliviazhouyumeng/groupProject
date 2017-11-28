#ifndef IBLOCK_H
#define IBLOCK_H
#include "abstractblock.h"

class IBlock : public AbstractBlock {
public:
    void left() override;
    void right() override;
    void down() override;
    void clockwise() override;
    void counterclockwise() override;
    void drop() override;
};

#endif
