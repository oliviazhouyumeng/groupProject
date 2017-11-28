#ifndef CELLIMPL_H
#define CELLIMPL_H
#include "info.h"

struct CellImpl{
    const size_t r, c;
    Colour colour = Colour::White;
    int level;
};

#endif
