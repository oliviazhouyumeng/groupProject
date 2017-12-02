#ifndef CELL_H
#define CELL_H
#include <cstddef>
#include "state.h"
#include "subject.h"
#include "info.h"

class Grid;
class Observer;
class Cell : public Subject<Info, State> {
    const size_t r, c;
    Colour colour;
    // Add other private members if necessary
    
public:
    
    ~Cell();
    
    Cell(size_t r, size_t c);
    
    void setPiece(Colour colour, Grid &g);    // Place a piece of given colour here.
    
    void setColour(Colour colour, Grid &g); // Modifies colour of the cell, change state
    
    void changeColour(Colour colour, Grid &g); // Modifies colour of the cell, does not change state
    
    Info getInfo() const override; 
};
#endif
