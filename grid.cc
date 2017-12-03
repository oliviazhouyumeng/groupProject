#include <sstream>
#include <vector>
#include <memory>
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
#include "starblock.h"
#include "level0.h"
#include "level1.h"
#include "level2.h"
#include "level3.h"
#include "level4.h"
#include "level.h"
#include "textdisplay.h"
using namespace std;

Grid::Grid(int hi_score, int curr_score, bool graphicsOn):
hi_score{hi_score}, curr_score{curr_score} {
    shared_ptr<Level> l0;
    shared_ptr<Level> l1;
    shared_ptr<Level> l2;
    shared_ptr<Level> l3;
    shared_ptr<Level> l4;
    l0 = dynamic_pointer_cast<Level0>(l0);
    l1 = dynamic_pointer_cast<Level1>(l1);
    l2 = dynamic_pointer_cast<Level2>(l2);
    l3 = dynamic_pointer_cast<Level3>(l3);
    l4 = dynamic_pointer_cast<Level4>(l4);
    l0 = make_shared<Level0>();
    l1 = make_shared<Level1>();
    l2 = make_shared<Level2>();
    l3 = make_shared<Level3>();
    l4 = make_shared<Level4>();
    levels.emplace_back(l0);
    levels.emplace_back(l1);
    levels.emplace_back(l2);
    levels.emplace_back(l3);
    levels.emplace_back(l4);
}

Grid::~Grid() {}

void Grid::setObserver(shared_ptr<Observer> ob) {
    this->ob = ob;
}

void Grid::endGame() const {
    throw EndException{};
}

void Grid::init() {
    theGrid.clear();
    liveBlocks.clear();
    
    curr_score = 0;
    
    const size_t totr = 18; // total rows
    const size_t totc = 11; // total columns
    
    td = make_shared<TextDisplay>(totc, totr);
    //if (graphicsOn) gd = make_shared<GraphicsDisplay>();
    
    for (size_t i = 0; i < totr; i++) {
        vector<Cell> rArr;
        for(size_t j = 0; j < totc; j++) {
            Cell c{i, j};
            rArr.emplace_back(c);
        }
        theGrid.emplace_back(rArr);
    }
    for (size_t i = 0; i < totr; i++) {
        for (size_t j = 0; j < totc; j++) {
            theGrid[i][j].attach(td);
            //if (graphicsOn) theGrid[i][j].attach(gd);
        }
    }
    updateNext();
    setCurrtoGrid();
    starCount = 5;
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

vector<shared_ptr<Level>> &Grid::getLevels() {
    return levels;
}

int Grid::getLevel() const {
    return currlevel;
}

void Grid::setLevel(int l) {
    currlevel = l;
}

void Grid::clearRow(size_t r) {
    int btemp = liveBlocks.size();
    for (int i = btemp-1; i >= 0; i--) {
        int ptemp = liveBlocks[i]->getPos().size();
        for (int j = ptemp-1; j >= 0; j--) {
            if (liveBlocks[i]->getPos()[i].x == r) {
                changeColour(r, liveBlocks[i]->getPos()[j].y, Colour::White);
                liveBlocks[i]->getPos().erase(liveBlocks[i]->getPos().begin()+j);
            }
        }
        if (liveBlocks[i]->getPos().size() == 0) {
            updateScore((liveBlocks[i]->getBlockLevel()+1)*(liveBlocks[i]->getBlockLevel()+1));
            liveBlocks.erase(liveBlocks.begin()+btemp);
        }
    }
    starCount = 5;
}

void Grid::moveDown() {
    size_t firstCellRow = 18;
    int count = 0;
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
                    changeColour(rBack, lBack, newcolour);
                }
            }
            count++;
        }
    }
    if (count!=0) updateScore((count+currlevel)*(count+currlevel));
}

bool Grid::isFull(size_t r) {
    for (size_t c = 0; c < 11; ++c) {
        if (checkWhite(r, c)) return false;
    }
    return true;
}

bool Grid::isEmpty(size_t r) {
    for (size_t c = 0; c < 11; ++c) {
        if (!checkWhite(r, c)) return false;
    }
    return true;
}

void Grid::setCurrtoGrid() {
    if (starCount == 0) {
        StarBlock(*this, currlevel);
        starCount = 5;
    }
    if (next == "I") curr = make_shared<IBlock>(*this, nextlevel);
    else if (next == "J") curr = make_shared<JBlock>(*this, nextlevel);
    else if (next == "L") curr = make_shared<LBlock>(*this, nextlevel);
    else if (next == "S") curr = make_shared<SBlock>(*this, nextlevel);
    else if (next == "Z") curr = make_shared<ZBlock>(*this, nextlevel);
    else if (next == "T") curr = make_shared<TBlock>(*this, nextlevel);
    else if (next == "O") curr = make_shared<OBlock>(*this, nextlevel);
    liveBlocks.emplace_back(curr);
    starCount--;
}

void Grid::updateNext() {
    if (currlevel == 0) {
        if (blockSeq == "" || blockSeq == " ") {
            blockSeq = levels[currlevel]->createBlock();
            seqCount = 0;
        }
        stringstream ss{blockSeq};
        ss >> next;
        seqCount += 2;
        blockSeq = blockSeq.substr(seqCount-1);
    }
    else next = levels[currlevel]->createBlock();
    nextlevel = currlevel;
    getCell(0, 0).notifyObservers(*this);
}

void Grid::setHint() {}

void Grid::clearHint() {}

string Grid::getNextType() const {
    return next;
}

void Grid::setNext(string nextcmd) {
    next = nextcmd;
    nextlevel = currlevel;
    getCell(0, 0).notifyObservers(*this);
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
    return *curr;
}

ostream &operator<<(std::ostream &out, const Grid &g) {
    string s;
    int i;
    s = "Level:       ";
    i = g.getLevel();
    out << s << i << endl;
    
    s = "Score:       ";
    i = g.getScore();
    out << s << i << endl;
    
    s = "HiScore:     ";
    i = g.getHiScore();
    out << s << i << endl;
    
    s = "------------";
    out << s << endl;
    
    out << *(g.td);
    
    out << s << endl;
    s = "Next:";
    out << s << endl;
    
    string next = g.getNextType();
    if (next == "I") {
        s = "IIII";
        out << s;
    } else if (next == "J") {
        s = "J";
        out << s << endl;
        s = "JJJ";
        out << s;
    } else if (next == "L") {
        s = "  L";
        out << s << endl;
        s = "LLL";
        out << s;
    } else if (next == "O") {
        s = "OO";
        out << s << endl;
        s = "OO";
        out << s;
    } else if (next == "S") {
        s = " SS";
        out << s << endl;
        s = "SS";
        out << s;
    } else if (next == "Z") {
        s = "ZZ";
        out << s << endl;
        s = " ZZ";
        out << s;
    } else if (next == "T") {
        s = "TTT";
        out << s << endl;
        s = " T";
        out << s;
    }
    return out;
}
