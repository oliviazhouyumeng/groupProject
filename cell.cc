#include "cell.h"
#include "state.h"
#include "subject.h"
#include "observer.h"
#include "info.h"
#include <cstddef>
#include "grid.h"

Cell::~Cell() {}#include "cell.h"
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

void Cell::setPiece(Colour colour, Grid &g) { // Place a new cell here.
    if (this->colour != Colour::White) {
        g.endGame();
    }
    this->colour = colour;
    State s{StateType::AC};
    setState(s);
    notifyObservers();
}
void Cell::addScore(Grid &g, int score) { //modify the score field in Grid
    g.updateScore(score);
}
void Cell::notify(Subject<Info, State> &whoFrom) {
    // My neighbours will call this
    // when they've changed state
}
Info Cell::getInfo() const {
    Info rt{r, c, colour};
    return rt;
}


Cell::Cell(size_t r, size_t c, int l):r{r}, c{c}, level{l}, colour{Colour::White} {}

void Cell::setPiece(Colour colour) { // Place a new cell here.

}
void Cell::addScore(Grid &g, int score) { //modify the score field in Grid
    g.updateScore(score);
}
void Cell::notify(Subject<Info, State> &whoFrom) {
    // My neighbours will call this
    // when they've changed state
}
Info Cell::getInfo() const {
    Info rt{r, c, colour};
    return rt;
}
