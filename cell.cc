#include "cell.h"
#include "state.h"
#include "subject.h"
#include "info.h"
#include <cstddef>
#include "grid.h"
#include "observer.h"

using namespace std;

Cell::~Cell() {}

Cell::Cell(size_t r, size_t c):r{r}, c{c}, colour{Colour::White} {
    State s{StateType::NA};
    setState(s);
}

void Cell::setColour(Colour colour, Grid &g){ // Modifies colour of the cell, change state
    State old_S = State{StateType::NA};
    State new_S = State{StateType::AC};
    if(colour == Colour::White){
        g.gSetState(r, c, old_S);
    }
    else{
        g.gSetState(r, c, new_S);
    }
    this->colour = colour;
    notifyObservers(g);
}

void Cell::changeColour(Colour colour, Grid &g){ // Modifies colour of the cell, donot change state
    this->colour = colour;
    notifyObservers(g);
}

Info Cell::getInfo() const {
    Info rt{r, c, colour};
    return rt;
}
