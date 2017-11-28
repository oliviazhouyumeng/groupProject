#ifndef CELLIMPL_H
#define CELLIMPL_H
#include "info.h"
#include <memory>

struct CellImpl{
    size_t r, c;
    int level;
    Colour colour = Colour::White;
    CellImpl(size_t r, size_t c, int level): r{r}, c{c}, level{level} {}
};

#endif
