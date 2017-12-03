#include "block.h"
#include "zblock.h"
#include "grid.h"
#include "info.h"
#include "state.h"
#include <vector>
using namespace std;

ZBlock::ZBlock(Grid &g, int level): Block{level, "A", false} {
    Posn p0{3, 0};
    Posn p1{3, 1};
    Posn p2{4, 1};
    Posn p3{4, 2};
    pos.emplace_back(p0);
    pos.emplace_back(p1);
    pos.emplace_back(p2);
    pos.emplace_back(p3);
    for (auto p : pos) {
        if (!g.checkWhite(p.x, p.y)) {g.endGame();}
    }
    for (auto p : pos) g.setColour(p.x, p.y, Colour::Magenta);
}

void ZBlock::left(Grid &g) {
    for (auto p : pos) {
        if (p.y == 0) return;
        if (!g.checkWhite(p.x, p.y-1)&&g.getState(p.x, p.y-1).stype==StateType::NA) return;
    }
    for (auto p : pos) g.setColour(p.x, p.y, Colour::White);
    pos[0].y--;
    pos[1].y--;
    pos[2].y--;
    pos[3].y--;
    for (auto p : pos) g.setColour(p.x, p.y, Colour::Magenta);
    if (g.getLevel()>2) down(g);
}

void ZBlock::right(Grid &g) {
    for (auto p : pos) {
        if (p.y == 10) return;
        if (!g.checkWhite(p.x, p.y+1)&&g.getState(p.x, p.y+1).stype==StateType::NA) return;
    }
    for (auto p : pos) g.setColour(p.x, p.y, Colour::White);
    pos[0].y++;
    pos[1].y++;
    pos[2].y++;
    pos[3].y++;
    for (auto p : pos) g.setColour(p.x, p.y, Colour::Magenta);
    if (g.getLevel()>2) down(g);
}

void ZBlock::down(Grid &g) {
    for (auto p : pos) {
        if (p.x == 17) return;
        if (!g.checkWhite(p.x+1, p.y) && g.getState(p.x+1, p.y).stype==StateType::NA) return;
    }
    for (auto p : pos) g.setColour(p.x, p.y, Colour::White);
    pos[0].x++;
    pos[1].x++;
    pos[2].x++;
    pos[3].x++;
    for (auto p : pos) g.setColour(p.x, p.y, Colour::Magenta);
}

void ZBlock::clockwise(Grid &g) {
    if (type == "A" || type == "C") {
        if (g.checkWhite(pos[0].x+1, pos[0].y) && g.checkWhite(pos[1].x-1, pos[1].y)) {
            cwtype();
            for (auto p : pos)  g.setColour(p.x, p.y, Colour::White);
            pos[0].x--;
            pos[0].y++;
            pos[2].x--;
            pos[2].y--;
            pos[3].y-=2;
            for (auto p : pos) g.setColour(p.x, p.y, Colour::Magenta);
            if (g.getLevel()>2) down(g);
        }
    } else if (type == "B" || type == "D") {
        if (pos[1].y!=10 && g.checkWhite(pos[3].x, pos[3].y+1) &&
            g.checkWhite(pos[3].x, pos[3].y+2)) {
            cwtype();
            for (auto p : pos) g.setColour(p.x, p.y, Colour::White);
            pos[0].x++;
            pos[0].y--;
            pos[2].x++;
            pos[2].y++;
            pos[3].y+=2;
            for (auto p : pos) g.setColour(p.x, p.y, Colour::Magenta);
            if (g.getLevel()>2) down(g);
        }
    }
}

void ZBlock::counterclockwise(Grid &g) {
    if (type == "A" || type == "C") {
        if (g.checkWhite(pos[0].x+1, pos[0].y) && g.checkWhite(pos[1].x-1, pos[1].y)) {
            ccwtype();
            for (auto p : pos) g.setColour(p.x, p.y, Colour::White);
            pos[0].x--;
            pos[0].y++;
            pos[2].x--;
            pos[2].y--;
            pos[3].y-=2;
            for (auto p : pos) g.setColour(p.x, p.y, Colour::Magenta);
            if (g.getLevel()>2) down(g);
        }
    } else if (type == "B" || type == "D") {
        if (pos[1].y!=10 && g.checkWhite(pos[3].x, pos[3].y+1) &&
            g.checkWhite(pos[3].x, pos[3].y+2)) {
            ccwtype();
            for (auto p : pos) g.setColour(p.x, p.y, Colour::White);
            pos[0].x++;
            pos[0].y--;
            pos[2].x++;
            pos[2].y++;
            pos[3].y+=2;
            for (auto p : pos) g.setColour(p.x, p.y, Colour::Magenta);
            if (g.getLevel()>2) down(g);
        }
    }
}

void ZBlock::drop(Grid &g) {
    size_t start = pos[1].x+1;
    for (size_t i = start; i < 18; i++) {
        down(g);
    }
    State s{StateType::NA};
    for (auto p : pos) {
        g.gSetState(p.x, p.y, s);
    }
    for (auto p : pos) {
        if (g.isFull(p.x)) g.clearRow(p.x);
    }
    g.moveDown();
}


void ZBlock::giveHint(Grid &g){
}

void ZBlock::cancelHint(Grid &g){
}



