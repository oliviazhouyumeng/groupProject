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
    
public:
    
    ~Cell();
    
    Cell(size_t r, size_t c);
    
    void setColour(Colour colour, Grid &g); // Modifies colour of the cell, change state
    
    void changeColour(Colour colour, Grid &g); // Modifies colour of the cell, does not change state
    
    Info getInfo() const override; 
};
#endif
