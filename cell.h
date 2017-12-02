#ifndef CELL_H
#define CELL_H
#include <cstddef>
#include <vector>
#include "state.h"
#include "subject.h"
#include "observer.h"
#include "info.h"
#include <memory>

class Grid;

class Cell : public Subject<Info, State> {
    const size_t r, c;
    int level;
    Colour colour;
    // Add other private members if necessary
    
public:
    
    ~Cell();
    
    Cell(size_t r, size_t c, int l);
    
    void setPiece(Colour colour, Grid &g);    // Place a piece of given colour here.
    
    void setColour(Colour colour, Grid &g); // Modifies colour of the cell, change state
    
    void changeColour(Colour colour, Grid &g); // Modifies colour of the cell, does not change state
    
    void addScore(Grid &g, int score); //modify the score field in Grid
    
    Info getInfo() const override;
    
    
    
};
#endif
