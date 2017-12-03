#include "block.h"
#include "iblock.h"
#include "grid.h"
using namespace std;

const string startType = "A";
const bool is_Heavy = false;

IBlock::IBlock(Grid &g, int level):Block{level, startType, is_Heavy}{
    if(level > 2) {
        heavy = true;
    }
    Posn first = Posn{3,0};
    Posn second = Posn{3,1};
    Posn third = Posn{3, 2};
    Posn forth = Posn{3,3};
    if(!g.checkWhite(first.x, first.y)) {
        g.endGame();
    }
    if(!g.checkWhite(second.x, second.y)) {
        g.endGame();
    }
    if(!g.checkWhite(third.x, third.y)) {
        g.endGame();
    }
    if(!g.checkWhite(forth.x, forth.y)) {
        g.endGame();
    }
    
    pos.push_back(first);
    pos.push_back(second);
    pos.push_back(third);
    pos.push_back(forth);
    for(auto p : pos){
        g.setColour(p.x, p.y, Colour::Red);
    }
    
}



void IBlock::left(Grid &g){
    for (auto p : pos) {
        if (p.y == 0) return;
        if ((!g.checkWhite(p.x, p.y-1))&&g.getCell(p.x, p.y-1).getState().stype==StateType::NA) return;
    }
    for (auto p : pos) {
        g.setColour(p.x, p.y, Colour::White);
    }
    pos[0].y--;
    pos[1].y--;
    pos[2].y--;
    pos[3].y--;
    for (auto p : pos){
        g.setColour(p.x, p.y, Colour::Red);
    }
    if (heavy) down(g);
}


void IBlock::right(Grid &g){
    for(auto p : pos) {
        if(p.y == 10)  return;
        if((!g.checkWhite(p.x, p.y+1)) && g.getCell(p.x, p.y+1).getState().stype == StateType::NA) return;
    }
    for(auto p : pos){
        g.setColour(p.x, p.y, Colour::White);
    }
    pos[0].y++;
    pos[1].y++;
    pos[2].y++;
    pos[3].y++;
    for(auto p : pos){
        g.setColour(p.x, p.y, Colour::Red);
    }
    if(heavy) down(g);
}

void IBlock::down(Grid &g){
    for(auto p : pos) {
        if(p.x == 17) return;
        if(!g.checkWhite(p.x+1, p.y) && g.getCell(p.x+1, p.y).getState().stype == StateType::NA) return;
    }
    for(auto p : pos){
        g.setColour(p.x, p.y, Colour::White);
    }
    pos[0].x++;
    pos[1].x++;
    pos[2].x++;
    pos[3].x++;
    for(auto p : pos){
        g.setColour(p.x, p.y, Colour::Red);
    }
}


void IBlock::clockwise(Grid &g){
    if(type == "A" || type == "C"){
        if(g.checkWhite(pos[0].x-1, pos[0].y) && g.checkWhite(pos[0].x-2, pos[0].y) &&
           g.checkWhite(pos[0].x-3, pos[0].y)){
            for(auto p : pos){
                g.setColour(p.x, p.y, Colour::White);
            }
            pos[0].x-=3;
            pos[1].x-=2;
            pos[1].y--;
            pos[2].x--;
            pos[2].y-=2;
            pos[3].y-=3;
            for(auto p : pos){
                g.setColour(p.x, p.y, Colour::Red);
            }
            cwtype();
            if(heavy) down(g);
        }
    }
    else if(type == "B" || type == "D"){
        if(pos[0].y == 8) return;
        if(g.checkWhite(pos[3].x, pos[3].y+1) && g.checkWhite(pos[3].x, pos[3].y+2) &&
           g.checkWhite(pos[3].x, pos[3].y+3)){
            for(auto p : pos){
                g.setColour(p.x, p.y, Colour::White);
            }
            pos[0].x+=3;
            pos[1].x+=2;
            pos[1].y++;
            pos[2].x++;
            pos[2].y+=2;
            pos[3].y+=3;
            for(auto p : pos){
                g.setColour(p.x, p.y, Colour::Red);
            }
            cwtype();
            if(heavy) down(g);
        }
    }
}


void IBlock::counterclockwise(Grid &g){
    if(type == "A" || type == "C"){
        if(g.checkWhite(pos[0].x-1, pos[0].y) && g.checkWhite(pos[0].x-2, pos[0].y) &&
           g.checkWhite(pos[0].x-3, pos[0].y)){
            for(auto p : pos){
                g.setColour(p.x, p.y, Colour::White);
            }
            pos[0].x-=3;
            pos[1].x-=2;
            pos[1].y--;
            pos[2].x--;
            pos[2].y-=2;
            pos[3].y-=3;
            for(auto p : pos){
                g.setColour(p.x, p.y, Colour::Red);
            }
            ccwtype();
            if(heavy) down(g);
        }
    }
    else if(type == "B" || type == "D"){
        if(pos[0].y == 8) return;
        if(g.checkWhite(pos[3].x, pos[3].y+1) && g.checkWhite(pos[3].x, pos[3].y+2) &&
           g.checkWhite(pos[3].x, pos[3].y+3)){
            for(auto p : pos){
                g.setColour(p.x, p.y, Colour::White);
            }
            pos[0].x+=3;
            pos[1].x+=2;
            pos[1].y++;
            pos[2].x++;
            pos[2].y+=2;
            pos[3].y+=3;
            for(auto p : pos){
                g.setColour(p.x, p.y, Colour::Red);
            }
            ccwtype();
            if(heavy) down(g);
        }
    }
}


void IBlock::drop(Grid &g){
    size_t lowest = pos[3].x;
    for(size_t i = lowest; i < 18; i++){
        down(g);
    }
    State s = State{StateType::NA};
    for(auto p : pos){
        g.gSetState(p.x, p.y, s);
    }
    for (auto p : pos){
        if(g.isFull(p.x)) g.clearRow(p.x);
    }
    g.moveDown();
}



void IBlock::giveHint(Grid &g){
    
}

void IBlock::cancelHint(Grid &g){
    
}

















