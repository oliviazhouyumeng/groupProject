#include "grid.h"
using namespace std;




Grid::Grid() {
    
}

Grid::~Grid(){ // default?
    //delete td;
    //delete gd;
}

void Grid::setObserver(unique_ptr<Observer<Info, State>> ob) {
    this->ob = ob;
}



bool Grid::endGame() const {
    //end the game
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
            Cell c{i, j, currlevel->levelNum};
            rArr.push_back(c);
        }
        theGrid.push_back(rArr);
    }
    for (size_t i = 0; i < totr; i++) {
        for (size_t j = 0; j < totc; j++) {
            //(theGrid[i])[j].attach(&theGrid[i][j]);
            if (j > 0) theGrid[i][j].attach(&theGrid[i][j-1]);
            if (i > 0) theGrid[i][j].attach(&theGrid[i-1][j]);
            if (i < totr-1) theGrid[i][j].attach(&theGrid[i+1][j]);
            if (j < totc-1) theGrid[i][j].attach(&theGrid[i][j+1]);
        }
    }
    for (size_t i = 0; i < totr; i++) {
        for (size_t j = 0; j < totc; j++) {
            theGrid[i][j].attach(td);
            theGrid[i][j].attach(gd);
        }
    }
    
    // generate blocks
    
}
void Grid::setNew(size_t r, size_t c, Colour colour) {
    curr->setNew(*this);
}
void Grid::levelUp() {
    
}
void Grid::levelDown() {
    
}
void Grid::moveDown(){
// check all lines, not only the very bottom one
}
void Grid::getNextBlock(){
    // update current
    next = level->createBlock();
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


