#include "grid.h"
#include "info.h"
#include "state.h"
#include "endexception.h"
#include "block.h"
#include "iblock.h"
#include "jblock.h"
#include "lblock.h"
#include "sblock.h"
#include "zblock.h"
#include "oblock.h"
#include "tblock.h"
#include "hintblock.h"
#include "starblock.h"
using namespace std;

Grid::Grid() {}

Grid::~Grid() {}

void Grid::setObserver(shared_ptr<Observer<Info, State>> ob) {
    this->ob = ob;
}

bool Grid::endGame() const {
    throw EndException{};
}

void Grid::init() {
    theGrid.clear();
    
    curr_score = 0;
    
    const size_t totr = 18; // total rows
    const size_t totc = 11; // total columns
    
    td = new TextDisplay{};
    if (gdavailable) gd = new GraphicsDisplay{};
    
    for (size_t i = 0; i < totr; i++) {
        vector<Cell> rArr;
        for(size_t j = 0; j < totc; j++) {
            Cell c{i, j, currlevel};
            rArr.emplace_back(c);
        }
        theGrid.emplace_back(rArr);
    }
    for (size_t i = 0; i < totr; i++) {
        for (size_t j = 0; j < totc; j++) {
            //(theGrid[i])[j].attach(&theGrid[i][j]);
            if (j > 0) theGrid[i][j].attach(&theGrid[i][j-1]); // up
            if (i > 0) theGrid[i][j].attach(&theGrid[i-1][j]); // left
            if (i < totr-1) theGrid[i][j].attach(&theGrid[i+1][j]); // right
            if (j < totc-1) theGrid[i][j].attach(&theGrid[i][j+1]); // down
            theGrid[i][j].attach(td);
            if (gdavailable) theGrid[i][j].attach(gd);
        }
    }
    updateNext();
    setCurrtoGrid();
    updateNext();
}

void Grid::setGraphics(bool b) {
    gdavailable = b;
}

void Grid::levelUp() {
    if (currlevel < 4) ++currlevel;
}

void Grid::levelDown() {
    if (currlevel > 0) --currlevel;
}

void Grid::setLevel(int l) {
    currlevel = l;
}

void Grid::clearRow(size_t r) {
}

void Grid::moveDown(size_t r) {
}

bool Grid::isFull(size_t r) {
    for (size_t c = 0; c < 11; ++c) {
        if (getCell(r, c).getInfo().colour == Colour::White) return false;
    }
    return false;
}

bool Grid::isEmpty(size_t r) {
    for (size_t c = 0; c < 11; ++c) {
        if (getCell(r, c).getInfo().colour != Colour::White) return false;
    }
    return true;
}

void Grid::setCurrtoGrid() {
    switch(next) {
        case NULL:
            return;
        case "I":
            curr = IBlock(*this, nextlevel);
        case "J":
            curr = JBlock(*this, nextlevel);
        case "L":
            curr = LBlock(*this, nextlevel);
        case "S":
            curr = SBlock(*this, nextlevel);
        case "Z":
            curr = ZBlock(*this, nextlevel);
        case "T":
            curr = TBlock(*this, nextlevel);
        case "O":
            curr = OBlock(*this, nextlevel);
        case "Hint":
            curr = HintBlock(*this, nextlevel);
        case "Star":
            curr = StarBlock(*this, nextlevel);
    }
}

void Grid::updateNext() {
    if (currlevel == 0) {
        if (iss == NULL) {
            string newLevel = levels[currlevel].createBlock();
            iss{newLevel};
            iss >> next;
        }
        else iss >> next;
    }
    else next = levels[currlevel].createBlock();
    nextlevel = currlevel;
}

voig Grid::setNext(string nextcmd) {
    next = nextcmd;
    nextlevel = currlevel;
}

void Grid::setColour(size_t row, size_t col, Colour colour) {
    getCell(row, col).setColour(colour, *this);
}

void setPiece(size_t row, size_t col, Colour colour) {
    getCell(row,col).setPiece(colour, *this);
}

void Grid::gSetState(size_t row, size_t col, State s) {
    getCell(row, col).setState(s);
}

State Grid::getState(size_t row, size_t col) {
    return getCell(row, col).getState();
}

void Grid::updateScore(int point) {
    curr_score += point;
    if (hi_score < curr_score) hi_score = curr_score;
}

Cell &Grid::getCell(size_t x, size_t y) {
    return theGrid[x][y];
}

Block &Grid::currBlock() {
    return curr;
}

std::ostream &operator<<(std::ostream &out, const Grid &g) {
    out << *(g.td);
    return out;
}
