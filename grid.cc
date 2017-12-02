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

Grid::Grid(currlevel): currlevel{currlevel} {}

Grid::~Grid() {}

void Grid::setObserver(shared_ptr<Observer<Info, State>> ob) {
    this->ob = ob;
}

bool Grid::endGame() const {
    throw EndException{};
}

void Grid::init() {
    theGrid.clear();
    liveBlocks.clear();
    
    curr_score = 0;
    
    const size_t totr = 18; // total rows
    const size_t totc = 11; // total columns
    
    td = new TextDisplay{};
    if (graphicsOn) gd = new GraphicsDisplay{};
    
    for (size_t i = 0; i < totr; i++) {
        vector<Cell> rArr;
        for(size_t j = 0; j < totc; j++) {
            Cell c{i, j, currlevel};
            rArr.emplace_back(c);
        }
        theGrid.emplace_back(rArr);
    }
    updateNext();
    setCurrtoGrid();
    updateNext();
}

void Grid::setGraphics(bool b) {
    graphicsOn = b;
}

void Grid::levelUp() {
    if (currlevel < 4) ++currlevel;
}

void Grid::levelDown() {
    if (currlevel > 0) --currlevel;
}

int Grid::getLevel() const {
    return currlevel;
}

void Grid::setLevel(int l) {
    currlevel = l;
}

void Grid::clearRow(size_t r) {
}

void Grid::moveDown() {
    size_t firstCellRow = 18;
    for (size_t currRow= 3; currRow < 18; currRow++) {
        if (!isEmpty(currRow) && firstCellRow == 18) firstCellRow = currRow;
        if (isEmpty(currRow) && firstCellRow != 18) {
            for (auto b : liveBlocks) {
                for (auto p : b->getPos()) {
                    if (p.x < currRow) {p.x++;}
                }
            }
            firstCellRow++;
            for (size_t rBack = currRow; rBack >= firstCellRow; rBack--) {
                for (size_t lBack = 0; lBack < 11; lBack++) {
                    Colour newcolour = getCell(rBack-1, lBack).getInfo().colour;
                    getCell(rBack, lBack).setColour(newcolour, *this);
                }
            }
        }
    }
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
            break;
        case "J":
            curr = JBlock(*this, nextlevel);
            break;
        case "L":
            curr = LBlock(*this, nextlevel);
            break;
        case "S":
            curr = SBlock(*this, nextlevel);
            break;
        case "Z":
            curr = ZBlock(*this, nextlevel);
            break;
        case "T":
            curr = TBlock(*this, nextlevel);
            break;
        case "O":
            curr = OBlock(*this, nextlevel);
            break;
        case "Hint":
            curr = HintBlock(*this, nextlevel);
            break;
        case "Star":
            curr = StarBlock(*this, nextlevel);
            break;
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

string Grid::getNextType() const {
    return next;
}

voig Grid::setNext(string nextcmd) {
    next = nextcmd;
    nextlevel = currlevel;
}

void Grid::setColour(size_t row, size_t col, Colour colour) {
    getCell(row, col).setColour(colour, *this);
}

//void setPiece(size_t row, size_t col, Colour colour) {
//    getCell(row,col).setPiece(colour, *this);
//}

bool Grid::checkWhite(size_t row, size_t col) {
    return getCell(row, col).getInfo().colour == Colour::White;
}

void Grid::gSetState(size_t row, size_t col, State s) const {
    getCell(row, col).setState(s);
}

State Grid::getState(size_t row, size_t col) const {
    return getCell(row, col).getState();
}

void Grid::updateScore(int point) {
    curr_score += point;
    if (hi_score < curr_score) hi_score = curr_score;
}

int Grid::getScore() const {
    return curr_score;
}

int Grid::getHiScore() const {
    return hi_score;
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
