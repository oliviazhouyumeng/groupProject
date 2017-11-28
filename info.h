#ifndef info_h
#define info_h
#include "state.h"
#include <cstddef>
enum class Colour {White=0, Black, Red, Green, Blue, Cyan, Yellow, Magenta, Orange, Brown};
struct Info{
    size_t row, col;
    Colour colour;
    int level;
};


#endif /* info_h */
