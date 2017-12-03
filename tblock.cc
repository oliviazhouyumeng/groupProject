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
    unsigned temp = 0;
    while (temp < 4 && temp < pos.size()) {
        while (g.isFull(pos[temp].x)) g.clearRow(pos[temp].x);
        temp++;
    }
    g.moveDown();
}


void TBlock::giveHint(Grid &g){
        size_t lc;
        size_t mc;
        size_t rc;
        size_t bot;
        if(type == "A"){
            lc = pos[0].y;
            mc = pos[1].y;
            rc = pos[2].y;
            bot = pos[3].x;
        }
        if(type == "C"){
            lc = pos[2].y;
            mc = pos[1].y;
            rc = pos[0].y;
            bot = pos[2].x;
        }
        if(type == "B"){
            lc = pos[3].y;
            mc = pos[0].y;
            rc = mc+1;
            bot = pos[2].x;
        }
        else{
            lc = pos[0].y;
            mc = pos[3].y;
            rc = mc+1;
            bot = pos[0].x;
        }
        for(size_t i = bot; i < 18; i++){
            
            if(rc!=11 && g.getCell(i, lc).getInfo().colour != Colour::White && g.getCell(i, mc).getInfo().colour == Colour::White
               && g.getCell(i, rc).getInfo().colour != Colour::White){
                if(g.getCell(i-1, lc).getInfo().colour == Colour::White && g.getCell(i-1, mc).getInfo().colour == Colour::White
                   && g.getCell(i-1, rc).getInfo().colour == Colour::White){
                    Posn first = Posn{i-1, lc};
                    Posn second = Posn{i-1, mc};
                    Posn third = Posn{i-1, rc};
                    Posn forth = Posn{i, mc};
                    h_pos.push_back(first);
                    h_pos.push_back(second);
                    h_pos.push_back(third);
                    h_pos.push_back(forth);
                    for(auto hp : h_pos){
                        g.changeColour(hp.x, hp.y, Colour::Black);
                    }
                    return;
                }
            }
            else if(rc!=11 && g.getCell(i, lc).getInfo().colour == Colour::White && g.getCell(i, mc).getInfo().colour == Colour::White
               && g.getCell(i, rc).getInfo().colour == Colour::White){
                if(i == 17 && g.getCell(i-1, mc).getInfo().colour == Colour::White){
                    Posn first = Posn{i, rc};
                    Posn second = Posn{i, mc};
                    Posn third = Posn{i, lc};
                    Posn forth = Posn{i-1, mc};
                    h_pos.push_back(first);
                    h_pos.push_back(second);
                    h_pos.push_back(third);
                    h_pos.push_back(forth);
                    for(auto hp : h_pos){
                        g.changeColour(hp.x, hp.y, Colour::Black);
                    }
                    return;
                }
                else if(g.getCell(i+1, lc).getInfo().colour != Colour::White && g.getCell(i+1, mc).getInfo().colour != Colour::White
                        && g.getCell(i+1, rc).getInfo().colour != Colour::White){
                    Posn first = Posn{i, rc};
                    Posn second = Posn{i, mc};
                    Posn third = Posn{i, lc};
                    Posn forth = Posn{i-1, mc};
                    h_pos.push_back(first);
                    h_pos.push_back(second);
                    h_pos.push_back(third);
                    h_pos.push_back(forth);
                    for(auto hp : h_pos){
                        g.changeColour(hp.x, hp.y, Colour::Black);
                    }
                    return;
                }
            }
            else if(g.getCell(i, lc).getInfo().colour != Colour::White && g.getCell(i, mc).getInfo().colour == Colour::White
                    && g.getCell(i-1, lc).getInfo().colour == Colour::White && g.getCell(i-1, mc).getInfo().colour == Colour::White
                    && g.getCell(i-2, mc).getInfo().colour == Colour::White){
                Posn first{i-2, mc};
                Posn second{i-1, mc};
                Posn third{i, mc};
                Posn forth{i-1, lc};
                h_pos.push_back(first);
                h_pos.push_back(second);
                h_pos.push_back(third);
                h_pos.push_back(forth);
                for(auto hp : h_pos){
                    g.changeColour(hp.x, hp.y, Colour::Black);
                }
                return;
            }
            else if(rc!=11 && g.getCell(i, mc).getInfo().colour != Colour::White && g.getCell(i, rc).getInfo().colour == Colour::White
                    && g.getCell(i-1, mc).getInfo().colour == Colour::White && g.getCell(i-1, rc).getInfo().colour == Colour::White
                    && g.getCell(i-2, rc).getInfo().colour == Colour::White){
                Posn first{i-2, rc};
                Posn second{i-1, rc};
                Posn third{i, rc};
                Posn forth{i-1, mc};
                h_pos.push_back(first);
                h_pos.push_back(second);
                h_pos.push_back(third);
                h_pos.push_back(forth);
                for(auto hp : h_pos){
                    g.changeColour(hp.x, hp.y, Colour::Black);
                }
                return;
            }
            else if(rc!=11 && g.getCell(i, rc).getInfo().colour != Colour::White && g.getCell(i, mc).getInfo().colour == Colour::White
                    && g.getCell(i-1, rc).getInfo().colour == Colour::White && g.getCell(i-1, mc).getInfo().colour == Colour::White
                    && g.getCell(i-2, mc).getInfo().colour == Colour::White){
                Posn first{i,mc};
                Posn second{i-1, mc};
                Posn third{i-2, mc};
                Posn forth{i-2, rc};
                h_pos.push_back(first);
                h_pos.push_back(second);
                h_pos.push_back(third);
                h_pos.push_back(forth);
                for(auto hp : h_pos){
                    g.changeColour(hp.x, hp.y, Colour::Black);
                }
                return;
            }
            else if(g.getCell(i, mc).getInfo().colour != Colour::White && g.getCell(i, lc).getInfo().colour == Colour::White
                    && g.getCell(i-1, lc).getInfo().colour == Colour::White && g.getCell(i-1, mc).getInfo().colour == Colour::White
                    && g.getCell(i-2, lc).getInfo().colour == Colour::White){
                Posn first{i,lc};
                Posn second{i-1, lc};
                Posn third{i-2, lc};
                Posn forth{i-1, mc};
                h_pos.push_back(first);
                h_pos.push_back(second);
                h_pos.push_back(third);
                h_pos.push_back(forth);
                for(auto hp : h_pos){
                    g.changeColour(hp.x, hp.y, Colour::Black);
                }
                return;
            }
        }
}



void TBlock::cancelHint(Grid &g){
    for(auto hp : h_pos){
        g.changeColour(hp.x, hp.y, Colour::White);
    }
    h_pos.clear();
}
