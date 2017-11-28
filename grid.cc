#include "grid.hpp"
#include "gridimpl.h"
using namespace std;

Grid::Grid():pImpl{new GridImpl}{}


Grid::~Grid(){
    
}


void Grid::setObserver(unique_ptr<Observer<Info, State>> ob){
    
}



bool Grid::isReached() const {
    
}
void Grid::init(size_t r, size_t c, int win_size){
    
}
void Grid::setPiece(size_t r, size_t c, Colour colour){
    
}
void Grid::levelUp(){
    
}
void Grid::levelDown(){
    
}

std::ostream &operator<<(std::ostream &out, const Grid &g);



