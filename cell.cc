#include "cell.h"
#include "state.h"
#include "subject.h"
#include "observer.h"
#include "info.h"
#include <cstddef>
#include "grid.h"

Cell::~Cell() {}

Cell::Cell(size_t r, size_t c, int l):r{r}, c{c}, level{l}, colour{Colour::White} {
    State s{StateType::NA};
    setState(s);
}



void Cell::setColour(Colour colour, Grid &g){ // Modifies colour of the cell
    State old_S = State{StateType::NA};
    State new_S = State{StateType::AC};
    if(colour == Colour::White){
        g.gSetState(r, c, old_S);
    }
    else{
        g.gSetState(r, c, new_S);
    }
    this->colour = colour;
    notifyObservers();
}

void Cell::addScore(Grid &g, int score) { //modify the score field in Grid
    g.updateScore(score);
}
void Cell::notify(Subject<Info, State> &whoFrom) {
    if(getInfo().colour == Colour::White) return;
    if(getState().stype == StateType::AC) return;
    
}
Info Cell::getInfo() const {
    Info rt{r, c, colour};
    return rt;
}
