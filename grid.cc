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
#include "graphicsdisplay.h"
#include "window.h"
#include "textdisplay.h"
using namespace std;

Grid::Grid(int hi_score, int curr_score, bool graphicsOn, bool redraw, bool isNoRand, int currlevel):
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

void Grid::endGame() const {
    throw EndException{};
}

void Grid::init() {
    if (theGrid.size() != 0) theGrid.clear();
    if (liveBlocks.size() != 0) liveBlocks.clear();
    
    curr_score = 0;
    currlevel = startLevel;
    const size_t totr = 18; // total rows
    const size_t totc = 11; // total columns
    
    td = make_shared<TextDisplay>(totc, totr);
    if (graphicsOn) gd = make_shared<GraphicsDisplay>();
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
            if (graphicsOn) theGrid[i][j].attach(gd);
        }
    }

    starCount = 5;
    updateNext();
    setCurrtoGrid();
    updateNext();
}

void Grid::setGraphics(bool b) {
    graphicsOn = b;
}

bool Grid::isGraphics() const {
    return graphicsOn;
}

void Grid::levelUp() {
    redraw = true;
    if (currlevel < 4) ++currlevel;
    getCell(0, 0).notifyObservers(*this);
}

void Grid::levelDown() {
    redraw = true;
    if (currlevel > 0) --currlevel;
    getCell(0, 0).notifyObservers(*this);
}

vector<shared_ptr<Level>> &Grid::getLevels() {
    return levels;
}

int Grid::getLevel() const {
    return currlevel;
}

void Grid::setCurrL(int l) {
  currlevel = l;
}

void Grid::setStartLevel(int l) {
    startLevel = l;
}

void Grid::clearRow(size_t r) {
    redraw = true;
    unsigned btemp = liveBlocks.size();
    int i = btemp-1;
    while (i >= 0) {
        unsigned ptemp = liveBlocks[i]->getPos().size();
        int j = ptemp-1;
        while (j >= 0) {
            if (liveBlocks[i]->getPos()[j].x == r) {
                changeColour(r, liveBlocks[i]->getPos()[j].y, Colour::White);
                liveBlocks[i]->getPos().erase(liveBlocks[i]->getPos().begin()+j);
            }
            j--;
        }
        i--;
    }
    i = btemp-1;
    while (i >= 0) {
        if (liveBlocks[i]->getPos().size() == 0) {
            updateScore((liveBlocks[i]->getBlockLevel()+1)*(liveBlocks[i]->getBlockLevel()+1));
            liveBlocks.erase(liveBlocks.begin()+i);
        }
        i--;
    }
    starCount = 5;
}

void Grid::moveDown(int br) {
    redraw = true;
    size_t firstCellRow = 18;
    int count = 0;
    for (size_t currRow= 3; currRow < 18; currRow++) {
        if (!isEmpty(currRow) && firstCellRow == 18) firstCellRow = currRow;
        if (isEmpty(currRow) && firstCellRow != 18) {
            unsigned btemp = liveBlocks.size();
            int i = btemp-1;
            while (i >= 0) {
                unsigned ptemp = liveBlocks[i]->getPos().size();
                int j = ptemp-1;
                while (j >= 0) {
                    if (liveBlocks[i]->getPos()[j].x < currRow) {
                        liveBlocks[i]->getPos()[j].x++;
                    }
                    --j;
                }
                --i;
            }
            for (size_t rBack = currRow; rBack >= firstCellRow; rBack--) {
                for (size_t lBack = 0; lBack < 11; lBack++) {
                    Colour newcolour = getCell(rBack-1, lBack).getInfo().colour;
                    changeColour(rBack, lBack, newcolour);
                }
            }
            firstCellRow++;
            count++;
        }
    }
    if (count!=0) updateScore((count+currlevel)*(count+currlevel));
    else if (br != 0 && firstCellRow == 18) updateScore((br+currlevel)*(br+currlevel));
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
    if (starCount == 0 && currlevel >= 4) {
        curr = make_shared<StarBlock>(*this, currlevel);
        liveBlocks.emplace_back(curr);
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
    redraw = true;
    if (currlevel == 0 || (currlevel >= 3 && isNoRand)) {
        if (blockSeq == "" || blockSeq == " ") {
            blockSeq = levels[currlevel]->createBlock();
            seqCount = 0;
        }
        stringstream ss{blockSeq};
        ss >> next;
        seqCount += 2;
        blockSeq = blockSeq.substr(2);
    }
    else next = levels[currlevel]->createBlock();
    nextlevel = currlevel;
    getCell(0, 0).notifyObservers(*this);
}

string Grid::getNextType() const {
    return next;
}

void Grid::changeCurr(string cmd) {
    for (auto p : liveBlocks.back()->getPos()) {
        setColour(p.x, p.y, Colour::White);
    }
    liveBlocks.erase(liveBlocks.end()-1);
    if (cmd == "I") curr = make_shared<IBlock>(*this, currlevel);
    else if (cmd == "J") curr = make_shared<JBlock>(*this, currlevel);
    else if (cmd == "L") curr = make_shared<LBlock>(*this, currlevel);
    else if (cmd == "S") curr = make_shared<SBlock>(*this, currlevel);
    else if (cmd == "Z") curr = make_shared<ZBlock>(*this, currlevel);
    else if (cmd == "T") curr = make_shared<TBlock>(*this, currlevel);
    else if (cmd == "O") curr = make_shared<OBlock>(*this, currlevel);
    liveBlocks.emplace_back(curr);
}

void Grid::setColour(size_t row, size_t col, Colour colour) {
    getCell(row, col).setColour(colour, *this);
}

void Grid::changeColour(size_t row, size_t col, Colour colour) {
    getCell(row, col).changeColour(colour, *this);
}

bool Grid::checkActive(size_t row, size_t col) {
    return getCell(row, col).getState().stype == StateType::AC;
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

bool Grid::getRedraw() const {
    return redraw;
}

void Grid::setRedraw(bool rd) {
    redraw = rd;
}

void Grid::setNoRand(bool nr) {
    isNoRand = nr;
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
    s = "Level:       "; // score board
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
    
    out << *(g.td);  // game board
    
    out << s << endl;
    s = "Next:";  // next block
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
