#ifndef GRID_H
#define GRID_H
#include <iostream>
#include <vector>
#include <cstddef>
#include "cell.h"
#include "state.h"
#include "info.h"
#include "subject.h"
#include "textdisplay.h"
#include "graphicsdisplay.h"
#include "level.h"

class TextDisplay;
class GraphicsDisplay;
template <typename InfoType, typename StateType> class Observer;
class InvalidMove{};
class GridImpl;
class Grid {
    GridImpl *pImpl;
    // Add private members, if necessary.
    
    
public:
    Grid();
    ~Grid();
    void setObserver(Observer<Info, State> *ob);
    bool isReached() const;  // Is the game over
    void init(size_t r, size_t c, int win_size); // Sets up an n x n grid.  Clears old grid, if necessary.
    void setPiece(size_t r, size_t c, Colour colour);  // Plays piece at row r, col c.
    void levelUp();
    void levelDown();
    
    friend std::ostream &operator<<(std::ostream &out, const Grid &g);
};

#endif
