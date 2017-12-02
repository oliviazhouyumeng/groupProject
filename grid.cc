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
#include <vector>
#include <memory>
using namespace std;

Grid::Grid(int currlevel, int hi_score = 100, int curr_score = 0): 
currlevel{currlevel}, hi_score{hi_score}, curr_score{curr_score} {}

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

vector<std::unique_ptr<Level>> &getLevels() {
    return levels;
}

int Grid::getLevel() const {
    return currlevel;
}

void Grid::setLevel(int l) {
    currlevel = l;
}

void Grid::clearRow(size_t r) {
    int btemp = (int)liveBlocks.size();
    for (int i = btemp-1; i >= 0; i--) {
        int ptemp = (int)liveBlocks[i]->getPos().size();
        for (int j = ptemp-1; j >= 0; j--) {
            if (liveBlocks[i]->getPos()[i].x == r) {
                changeColour(r, liveBlocks[i]->getPos()[j].y, Colour::White);
                liveBlocks[i]->getPos().erase(liveBlocks[i]->getPos().begin()+j);
            }
        }
        if (liveBlocks[i]->getPos().size() == 0) liveBlocks.erase(liveBlocks.begin()+btemp);
    }
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
                    getCell(rBack, lBack).changeColour(newcolour, *this);
                    getCell(rBack, lBack).setCellLevel(getLevel(rBack-1, lBack), *this);
                }
            }
        }
    }
}

bool Grid::isFull(size_t r) {
    for (size_t c = 0; c < 11; ++c) {
        if (checkWhite(r, c)) return false;
    }
    return false;
}

bool Grid::isEmpty(size_t r) {
    for (size_t c = 0; c < 11; ++c) {
        if (!checkWhite(r, c)) return false;
    }
    return true;
}

void Grid::setCurrtoGrid() {
    if (next == "I") curr = IBlock(*this, nextlevel);
    else if (next == "J") curr = JBlock(*this, nextlevel);
    else if (next == "L") curr = LBlock(*this, nextlevel);
    else if (next == "S") curr = SBlock(*this, nextlevel);
    else if (next == "Z") curr = ZBlock(*this, nextlevel);
    else if (next == "T") curr = TBlock(*this, nextlevel);
    else if (next == "O") curr = OBlock(*this, nextlevel);
    else if (next == "Hint") curr = HintBlock(*this, nextlevel);
    else if (next == "Star") curr = StarBlock(*this, nextlevel);
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

void Grid::setHint() {}

void Grid::clearHint() {}

string Grid::getNextType() const {
    return next;
}

void Grid::setNext(string nextcmd) {
    next = nextcmd;
    nextlevel = currlevel;
}

void Grid::setColour(size_t row, size_t col, Colour colour) {
    getCell(row, col).setColour(colour, *this);
}

void Grid::changeColour(size_t row, size_t col, Colour colour) {
    getCell(row, col).changeColour(colour, *this);
}

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

void setCellLevel(size_t row, size_t col, int lev) {
    getCell(row, col).setLevel(lev);
}

int getLevel(size_t row, size_t col) {
    return getCell(row, col).getInfo().level;
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
