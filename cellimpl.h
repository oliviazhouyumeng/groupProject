#ifndef cellimpl_h
#define cellimpl_h
#include "info.h"

struct CellImpl{
    const size_t r, c;
    Colour colour = Colour::White;
    int level;
};

#endif
