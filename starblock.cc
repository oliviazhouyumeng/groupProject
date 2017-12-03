#include "block.h"
#include "starblock.h"
using namespace std;

const string startType = "A";
const bool is_Heavy = false;

StarBlock::StarBlock(Grid &g, int level):Block{level, startType}{
    if(level <=2 ) return;
    Posn single = Posn{3, 5};
    if(!g.checkWhite(single.x, single.y)) {
        g.endGame();
    }
    g.setColour(single.x, single.y, Colour::Brown);
    pos.push_back(single);
    drop(g);
}


void StarBlock::left(Grid &g) {} // cannot move to left
void StarBlock::right(Grid &g) {} // cannot move to right
void StarBlock::down(Grid &g){
    for(auto p : pos) {
        if(p.x == 17) return;
        if(!g.checkWhite(p.x+1, p.y) && g.getCell(p.x+1, p.y).getState().stype == StateType::NA) return;
    }
    for(auto p : pos){
        g.setColour(p.x, p.y, Colour::White);
    }
    pos[0].x++;
    for(auto p : pos){
        g.setColour(p.x, p.y, Colour::Brown);
    }
}
void StarBlock::clockwise(Grid &g) {} // remains the same
void StarBlock::counterclockwise(Grid &g) {} // remains the same
void StarBlock::drop(Grid &g){
    for (size_t i = pos.at(0).x; i<18; i++) {
        down(g);
    }
    State s = State{StateType::NA};
    for(auto p : pos){
        g.gSetState(p.x, p.y, s);
    }
    for(auto p : pos){
        if(g.isFull(p.x)) g.clearRow(p.x);
    }
    g.moveDown();
}

void StarBlock::giveHint(Grid &g){
}

void StarBlock::cancelHint(Grid &g){
}








