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



bool Grid::isReached() const {
    // check if there is still room at first position
}

void Grid::init(int hi) {
    theGrid.clear();
    //delete td;
    //delete gd;
    
    hi_score = hi;
    curr_score = 0;
    
    const int totr = 18; // total rows
    const int totc = 15; // total columns
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
            //if (i>0&&j>0) theGrid[i][j].attach(&theGrid[i-1][j-1]);
            if (j > 0) theGrid[i][j].attach(&theGrid[i][j-1]);
            //if (i<n-1&&j>0) theGrid[i][j].attach(&theGrid[i+1][j-1]);
            if (i > 0) theGrid[i][j].attach(&theGrid[i-1][j]);
            if (i < n-1) theGrid[i][j].attach(&theGrid[i+1][j]);
            //if (i>0&&j<n-1) theGrid[i][j].attach(&theGrid[i-1][j+1]);
            if (j < n-1) theGrid[i][j].attach(&theGrid[i][j+1]);
            //if (i<n-1&&j<n-1) theGrid[i][j].attach(&theGrid[i+1][j+1]);
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
void Grid::setPiece(size_t r, size_t c, Colour colour) {
    
}
void Grid::levelUp() {
    
}
void Grid::levelDown() {
    
}
void Grid::moveDown(){
// check all lines, not only the very bottom one
}
void Grid::getNextBlock(){
    curr = next;
    next = level->createBlock();
}
void Grid::updateScore(int point) {
    curr_score += point;
    if (hi_score < curr_score) hi_score = curr_score;
}
std::ostream &operator<<(std::ostream &out, const Grid &g) {

}


