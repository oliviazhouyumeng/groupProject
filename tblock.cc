#include "block.h"
#include "tblock.h"
#include "state.h"
#include "info.h"
#include "grid.h"
#include <vector>
using namespace std;
TBlock::TBlock(Grid &g, int level): Block{level, "A"}{
    
    Posn ul = Posn{3,0};
    Posn um = Posn{3, 1};
    Posn ur = Posn{3, 2};
    Posn lm = Posn{4, 1};
    if(!g.checkWhite(ul.x, ul.y)) {
        g.endGame();
    }
    if(!g.checkWhite(um.x, um.y)) {
        g.endGame();
    }
    if(!g.checkWhite(ur.x, ur.y)) {
        g.endGame();
    }
    if(!g.checkWhite(lm.x, lm.y)) {
        g.endGame();
    }
    
    
    pos.push_back(ul);
    pos.push_back(um);
    pos.push_back(ur);
    pos.push_back(lm);
    
    for(auto p : pos){
        g.setColour(p.x, p.y, Colour::Orange);
    }
}


//size_t x, y;
//int level;
//std::string type; // type: "A"(default), "B", "C", "D" clockwise:A->B->C->D
//bool heavy; // default: false
//std::vector<Posn> pos; // a Block originally contains four Cell

void TBlock::left(Grid &g){
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
        g.setColour(p.x, p.y, Colour::Orange);
    }
    if (g.getLevel() > 2) down(g);
}




void TBlock::right(Grid &g){
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
        g.setColour(p.x, p.y, Colour::Orange);
    }
    if (g.getLevel() > 2) down(g);
}




void TBlock::down(Grid &g){
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
        g.setColour(p.x, p.y, Colour::Orange);
    }
}




void TBlock::clockwise(Grid &g){
    if (type == "A") {
        if(g.checkWhite(pos[1].x-1, pos[1].y)){
            for(auto p : pos){
                g.setColour(p.x, p.y, Colour::White);
            }
            pos[0].x--;
            pos[0].y++;
            pos[2].x++;
            pos[2].y--;
            pos[3].x--;
            pos[3].y--;
            for(auto p : pos){
                g.setColour(p.x, p.y, Colour::Orange);
            }
            cwtype();
            if (g.getLevel() > 2) down(g);
        }
    }
    else if(type == "B"){
        Posn edge = pos.at(0);
        if(edge.y == 10) return;
        if(g.checkWhite(pos[2].x, pos[2].y-1) && g.checkWhite(pos[2].x, pos[2].y+1)){
            for (auto p : pos){
                g.setColour(p.x, p.y, Colour::White);
            }
            pos[0].x+=2;
            pos[0].y++;
            pos[1].x++;
            pos[2].y--;
            pos[3].y++;
            for(auto p : pos){
                g.setColour(p.x, p.y, Colour::Orange);
            }
            cwtype();
            if (g.getLevel() > 2) down(g);
        }
    }
    else if(type == "C"){
        if(g.checkWhite(pos[2].x-1, pos[2].y) && g.checkWhite(pos[2].x-2, pos[2].y)){
            for (auto p : pos){
                g.setColour(p.x, p.y, Colour::White);
            }
            pos[0].y-=2;
            pos[1].x--;
            pos[1].y--;
            pos[2].x-=2;
            for(auto p : pos){
                g.setColour(p.x, p.y, Colour::Orange);
            }
            cwtype();
            if (g.getLevel() > 2) down(g);
        }
    }
    else { // type "D"
        Posn edge = pos.at(3);
        if(edge.y == 10) return;
        if(g.checkWhite(pos[3].x, pos[3].y+1) && g.checkWhite(pos[3].x+1, pos[3].y)){
            for (auto p : pos) {
                g.setColour(p.x, p.y, Colour::White);
            }
            pos[0].x--;
            pos[1].y++;
            pos[2].x++;
            pos[2].y+=2;
            pos[3].x++;
            for(auto p : pos){
                g.setColour(p.x, p.y, Colour::Orange);
            }
            cwtype();
            if (g.getLevel() > 2) down(g);
        }
    }
}



void TBlock::counterclockwise(Grid &g){
    if(type == "A"){
        if (g.checkWhite(pos[0].x-1, pos[0].y) && g.checkWhite(pos[0].x+1, pos[0].y)) {
            for (auto p : pos){
                g.setColour(p.x, p.y, Colour::White);
            }
            pos[0].x++;
            pos[1].y--;
            pos[2].x--;
            pos[2].y-=2;
            pos[3].x--;
            for(auto p : pos){
                g.setColour(p.x, p.y, Colour::Orange);
            }
            ccwtype();
            if (g.getLevel() > 2) down(g);
        }
    }
    else if(type == "B"){
        Posn edge = pos.at(0);
        if(edge.y == 10) return;
        if(g.checkWhite(pos[1].x, pos[1].y+1)){
            for (auto p : pos){
                g.setColour(p.x, p.y, Colour::White);
            }
            pos[0].x++;
            pos[0].y--;
            pos[2].x--;
            pos[2].y++;
            pos[3].x++;
            pos[3].y++;
            for(auto p : pos){
                g.setColour(p.x, p.y, Colour::Orange);
            }
            ccwtype();
            if (g.getLevel() > 2) down(g);
        }
    }
    else if (type == "C") {
        if(g.checkWhite(pos[3].x, pos[3].y-1) && g.checkWhite(pos[3].x-1, pos[3].y)){
            for (auto p : pos){
                g.setColour(p.x, p.y, Colour::White);
            }
            pos[0].x-=2;
            pos[0].y--;
            pos[1].x--;
            pos[2].y++;
            pos[3].y--;
            for(auto p : pos){
                g.setColour(p.x, p.y, Colour::Orange);
            }
            ccwtype();
            if (g.getLevel() > 2) down(g);
        }
    }
    else {
        Posn edge = pos.at(3);
        if(edge.y == 10) return;
        if(g.checkWhite(pos[0].x, pos[0].y+2) && g.checkWhite(pos[0].x, pos[0].y+1)){
            for (auto p : pos){
                g.setColour(p.x, p.y, Colour::White);
            }
            pos[0].y+=2;
            pos[1].x++;
            pos[1].y++;
            pos[2].x+=2;
            for(auto p : pos){
                g.setColour(p.x, p.y, Colour::Orange);
            }
            ccwtype();
            if (g.getLevel() > 2) down(g);
        }
    }
}


void TBlock::drop(Grid &g){
    size_t lowest = 19;
    for(auto p : pos){
        if(p.x < lowest) lowest = p.x;
    }
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

Posn TBlock::rightLandPos(Grid &g){
    for(size_t j = 10; j>=0; j--){
        for(size_t i = 3 ; i < 18; i++){
            if((g.getCell(i, j).getInfo().colour != Colour::White) &&
               (i >= 6)&&(g.getCell(i-1, j).getInfo().colour == Colour::White) &&
               (g.getCell(i-2, j).getInfo().colour == Colour::White)&&
               (g.getCell(i-3, j).getInfo().colour == Colour::White)&&
               (g.getCell(i-2, j-1).getInfo().colour == Colour::White)){
                Posn p = Posn{i-1, j};
                return p;
            }
        }
    }
    return Posn{4,1};
}

void TBlock::giveHint(Grid &g){
    Posn lr = rightLandPos(g);
    Posn ur = Posn{lr.x-2,lr.y};
    Posn mr = Posn{lr.x-1, lr.y};
    Posn ml = Posn{lr.x-1, lr.y-1};
    h_pos.push_back(ur);
    h_pos.push_back(mr);
    h_pos.push_back(lr);
    h_pos.push_back(ml);
    for(auto hp : h_pos){
        g.changeColour(hp.x, hp.y, Colour::Black);
    }
}

void TBlock::cancelHint(Grid &g){
    for(auto hp : h_pos){
        g.changeColour(hp.x, hp.y, Colour::White);
    }
    h_pos.clear();
}
