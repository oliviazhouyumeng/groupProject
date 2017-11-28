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

class Cell : public Subject<Info, State>, public Observer<Info, State> {
    const size_t r, c;
    int level;
    Colour colour;
    // Add other private members if necessary
    
public:
    
    ~Cell();

    Cell(size_t r, size_t c, int l);
    
    void setPiece(Colour colour, Grid &g);    // Place a piece of given colour here.
    
    void addScore(Grid &g, int score); //modify the score field in Grid
    
    void notify(Subject<Info, State> &whoFrom) override;// My neighbours will call this
    // when they've changed state
    Info getInfo() const override;
    
    
    
};
#endif
