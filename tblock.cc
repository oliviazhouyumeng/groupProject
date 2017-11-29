#include "block.hpp"
#include "tblock.hpp"

using namespace std;


TBlock::TBlock(Grid &g): Block{3, 0, level, "A", false}{
    shared_ptr<Cell> a(&g.getCell(2, 0));
    cells.push_back(a);
    shared_ptr<Cell> b(&g.getCell(2, 1));
    cells.push_back(b);
    shared_ptr<Cell> c(&g.getCell(2, 2));
    cells.push_back(c);
    shared_ptr<Cell> d(&g.getCell(3, 1));
    cells.push_back(d);
}
    


void TBlock::left(Grid &g){///////////not done
    shared_ptr<Cell> ur(cells.at(2)); //upper right cell
    int ur_x = ur->getInfo().row;
    int ur_y = ur->getInfo().col;
    //shared_ptr<Cell> new_ur(&g.getCell(size_t x, <#size_t y#>))
    
    
    
    
    
    
    shared_ptr<Cell> ur(cells.at(2)); //upper right cell
    State news{StateType::ML};
    ur->setState(news);
    ur->notifyObservers();
}



void TBlock::right(Grid &g){
    shared_ptr<Cell> origin(&g.getCell(x, y));
    origin->notifyObservers();
}



void TBlock::down(Grid &g){
    shared_ptr<Cell> origin(&g.getCell(x, y));
    origin->notifyObservers();
}


void TBlock::clockwise(Grid &g){
    shared_ptr<Cell> origin(&g.getCell(x, y));
    origin->notifyObservers();
}
void TBlock::counterclockwise(Grid &g){
    shared_ptr<Cell> origin(&g.getCell(x, y));
    origin->notifyObservers();
}


void TBlock::drop(Grid &g){
    for(int i = 0; i < 18; i++){ //for 21 rows
        down(g);
    }
}

























