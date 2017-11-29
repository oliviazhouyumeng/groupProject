#include "block.h"
#include "tblock.h"
using namespace std;


TBlock::TBlock(): Block{3, 0, level, "A", false}{
    auto a = std::make_shared<Cell>(2, 0, level);
    cells.push_back(a);
    auto b = std::make_shared<Cell>(2, 1, level);
    cells.push_back(b);
    auto c = std::make_shared<Cell>(2, 2, level);
    cells.push_back(c);
    auto d = std::make_shared<Cell>(3, 1, level);
    cells.push_back(d);
}
    


void TBlock::left(){
    
}
void TBlock::right();
void TBlock::down();
void TBlock::clockwise();
void TBlock::counterclockwise();
void TBlock::drop();
