#ifndef JBLOCK_H
#define JBLOCK_H
#include "abstractblock.h"

class JBlock : public AbstractBlock {
public:
    void left() override;
    void right() override;
    void down() override;
    void clockwise() override;
    void counterclockwise() override;
    void drop() override;
};

#endif
