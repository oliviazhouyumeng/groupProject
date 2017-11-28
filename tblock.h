#ifndef TBLOCK_H
#define TBLOCK_H
#include "abstractblock.h"

class TBlock : public AbstractBlock {
public:
    void left() override;
    void right() override;
    void down() override;
    void clockwise() override;
    void counterclockwise() override;
    void drop() override;
};

#endif
