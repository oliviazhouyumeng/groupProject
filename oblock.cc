#include "block.h"
#include "oblock.h"
#include "grid.h"
#include "state.h"
#include "info.h"
#include <vector>
using namespace std;

OBlock::OBlock(Grid &g, int level): Block{level, "A"} {
    Posn p0{3, 0};
    Posn p1{4, 0};
    Posn p2{4, 1};
    Posn p3{3, 1};
    pos.emplace_back(p0);
    pos.emplace_back(p1);
    pos.emplace_back(p2);
    pos.emplace_back(p3);
    for (auto p : pos) {
        if (!g.checkWhite(p.x, p.y)) {g.endGame();}
    }
    for (auto p : pos) g.setColour(p.x, p.y, Colour::Cyan);
}

void OBlock::left(Grid &g) {
    for (auto p : pos) {
        if (p.y == 0) return;
        if (!g.checkWhite(p.x, p.y-1)&&g.getState(p.x, p.y-1).stype==StateType::NA) return;
    }
    for (auto p : pos) g.setColour(p.x, p.y, Colour::White);
    pos[0].y--;
    pos[1].y--;
    pos[2].y--;
    pos[3].y--;
    for (auto p : pos) g.setColour(p.x, p.y, Colour::Cyan);
    if (g.getLevel()>2) down(g);
}

void OBlock::right(Grid &g) {
    for (auto p : pos) {
        if (p.y == 10) return;
        if (!g.checkWhite(p.x, p.y+1)&&g.getState(p.x, p.y+1).stype==StateType::NA) return;
    }
    for (auto p : pos) g.setColour(p.x, p.y, Colour::White);
    pos[0].y++;
    pos[1].y++;
    pos[2].y++;
    pos[3].y++;
    for (auto p : pos) g.setColour(p.x, p.y, Colour::Cyan);
    if (g.getLevel()>2) down(g);
}

void OBlock::down(Grid &g) {
    for (auto p : pos) {
        if (p.x == 17) return;
        if (!g.checkWhite(p.x+1, p.y) && g.getState(p.x+1, p.y).stype==StateType::NA) return;
    }
    for (auto p : pos) g.setColour(p.x, p.y, Colour::White);
    pos[0].x++;
    pos[1].x++;
    pos[2].x++;
    pos[3].x++;
    for (auto p : pos) g.setColour(p.x, p.y, Colour::Cyan);
}

void OBlock::clockwise(Grid &g) {
    if (g.getLevel()>2) down(g);
}

void OBlock::counterclockwise(Grid &g) {
    if (g.getLevel()>2) down(g);
}

void OBlock::drop(Grid &g) {
    size_t start = pos[2].x+1;
    for (size_t i = start; i < 18; i++) {
        down(g);
    }
    State s{StateType::NA};
    for (auto p : pos) {
        g.gSetState(p.x, p.y, s);
    }
    unsigned temp = 0;
    while (temp < 4 && temp < pos.size()) {
        while (g.isFull(pos[temp].x)) g.clearRow(pos[temp].x);
        temp++;
    }
    g.moveDown(1);
}

void OBlock::giveHint(Grid &g) {
    size_t lc = pos[0].y;
    size_t rc = pos[3].y;
    size_t bot = pos[1].x;
    for(size_t i = bot; i < 18; i++){
        if(bot == 17){
            Posn first = pos[0];
            Posn second = pos[1];
            Posn third = pos[2];
            Posn forth = pos[3];
            h_pos.push_back(first);
            h_pos.push_back(second);
            h_pos.push_back(third);
            h_pos.push_back(forth);
            for(auto hp : h_pos){
                g.changeColour(hp.x, hp.y, Colour::Black);
            }
            return;
        }
        else if(g.getCell(i, lc).getInfo().colour != Colour::White || g.getCell(i, rc).getInfo().colour != Colour::White){
            if(g.getCell(i-1, lc).getInfo().colour == Colour::White && g.getCell(i-1, rc).getInfo().colour == Colour::White
               && g.getCell(i-2, lc).getInfo().colour == Colour::White && g.getCell(i-2, rc).getInfo().colour == Colour::White){
                Posn first{i-1, lc};
                Posn second{i-1, rc};
                Posn third{i-2, lc};
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
        }
        else if(g.getCell(i, lc).getInfo().colour == Colour::White && g.getCell(i, rc).getInfo().colour == Colour::White){
            if(i == 17 && g.getCell(i-1, lc).getInfo().colour == Colour::White && g.getCell(i-1, rc).getInfo().colour == Colour::White){
                Posn first{i, lc};
                Posn second{i, rc};
                Posn third{i-1, lc};
                Posn forth{i-1, rc};
                h_pos.push_back(first);
                h_pos.push_back(second);
                h_pos.push_back(third);
                h_pos.push_back(forth);
                for(auto hp : h_pos){
                    g.changeColour(hp.x, hp.y, Colour::Black);
                }
                return;
            }
            else if(g.getCell(i+1, lc).getInfo().colour != Colour::White && g.getCell(i+1, rc).getInfo().colour != Colour::White
                    && g.getCell(i-1, lc).getInfo().colour == Colour::White && g.getCell(i-1, rc).getInfo().colour == Colour::White){
                Posn first{i, lc};
                Posn second{i, rc};
                Posn third{i-1, lc};
                Posn forth{i-1, rc};
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
}

void OBlock::cancelHint(Grid &g) {
    for(auto hp : h_pos){
        if (g.checkActive(hp.x, hp.y)) g.changeColour(hp.x, hp.y, Colour::Yellow);
        else g.changeColour(hp.x, hp.y, Colour::White);
    }
    h_pos.clear();
}
