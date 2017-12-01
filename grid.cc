#include "grid.h"
using namespace std;

Grid::Grid() {}

Grid::~Grid() {}

void Grid::setObserver(unique_ptr<Observer<Info, State>> ob) {
    this->ob = ob;
}

bool Grid::endGame() const {
    throw EndException{};
}

void Grid::init(int hi) {
    theGrid.clear();
    //delete td;
    //delete gd;
    
    hi_score = hi;
    curr_score = 0;
    
    const size_t totr = 18; // total rows
    const size_t totc = 11; // total columns
    
    td = new TextDisplay{};
    gd = new GraphicsDisplay{};
    
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
            theGrid[i][j].attach(gd);
        }
    }
    getNextBlock();
    getNextBlock();
}

void Grid::levelUp() {
    if (currlevel < 4) ++currlevel;
}

void Grid::levelDown() {
    if (currlevel > 0) --currlevel;
}

void setLevel(int l) {
    currlevel = l;
}
    
void Grid::clearRow(size_t r) {

}
    
void Grid::moveDown(size_t r) {
    if (isEmpty(r)) {
        int currRow = r;
        while (r >= 3) {
            for (auto b : liveBlocks) {
                for (auto c : b.cells) {
                    if (c.getInfo().row == r) {
                        Colour currColour = c.getInfo().colour;
                        c.setColour(Colour::White, *this);
                        auto c = make_shared<getCell(r+1, c.getInfo().col)>;
                        c.setColour(currColour, *this);
                    }
                }
            }
            --r;
        }
    }
}

void Grid::isEmpty(size_t r) {
    for (size_t c = 0; c < 11; ++c) {
        if (getCell(r, c).getInfo().colour != Colour::White) return false;
    }
    return true;
}

void Grid::getNextBlock(){
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

void Grid::updateScore(int point) {
    curr_score += point;
    if (hi_score < curr_score) hi_score = curr_score;
}

Cell &Grid::getCell(size_t x, size_t y) {
    return theGrid[x][y];
}

std::ostream &operator<<(std::ostream &out, const Grid &g) {
    out << *(g.td);
    return out;
}
