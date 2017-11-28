#include "cell.h"
#include "state.h"
#include "subject.h"
#include "observer.h"
#include "info.h"
#include <cstddef>
#include "grid.h"

Cell::Cell() { // default colour:white
}
Cell::~Cell() {}

void Cell::setPiece(Colour colour) {    // Place a piece of given colour here.
    
}
void Cell::addScore(Grid &g, int score) { //modify the score field in Grid

}
void Cell::notify(Subject<Info, State> &whoFrom) {
    // My neighbours will call this
    // when they've changed state
}
Info Cell::getInfo() const {
    
}

