#include "block.h"
#include "sblock.h"
#include "grid.h"
#include "state.h"
#include "info.h"
#include <vector>
using namespace std;

SBlock::SBlock(Grid &g, int level): Block{level, "A", false} {
    if (level > 2) {heavy = true;}
    Posn p0{4, 0};
    Posn p1{4, 1};
    Posn p2{3, 1};
    Posn p3{3, 2};
    pos.emplace_back(p0);
    pos.emplace_back(p1);
    pos.emplace_back(p2);
    pos.emplace_back(p3);
    for (auto p : pos) {
        if (!g.checkWhite(p.x, p.y)) {g.endGame();}
    }
    for (auto p : pos) g.setColour(p.x, p.y, Colour::Yellow);
}

void SBlock::left(Grid &g) {
    for (auto p : pos) {
        if (p.y == 0) return;
        if ((!g.checkWhite(p.x, p.y-1))&&g.getCell(p.x, p.y-1).getState().stype==StateType::NA) return;
    }
    for (auto p : pos) g.setColour(p.x, p.y, Colour::White);
    for (auto p : pos) p.y--;
    for (auto p : pos) g.setColour(p.x, p.y, Colour::Yellow);
    if (heavy) down(g);
}

void SBlock::right(Grid &g) {
    for (auto p : pos) {
        if (p.y == 10) return;
        if (!g.checkWhite(p.x, p.y+1)&&g.getCell(p.x, p.y+1).getState().stype==StateType::NA) return;
    }
    for (auto p : pos) g.setColour(p.x, p.y, Colour::White);
    for (auto p : pos) p.y++;
    for (auto p : pos) g.setColour(p.x, p.y, Colour::Yellow);
    if (heavy) down(g);
}

void SBlock::down(Grid &g) {
    for (auto p : pos) {
        if (p.x == 17) return;
        if (g.getCell(p.x+1, p.y).getInfo().colour != Colour::White) return;
    }
    for (auto p : pos) g.setColour(p.x, p.y, Colour::White);
    for (auto p : pos) p.x++;
    for (auto p : pos) g.setColour(p.x, p.y, Colour::Yellow);
}

void SBlock::clockwise(Grid &g) {
    if (type == "A" || type == "C") {
        if (g.checkWhite(pos[0].x-1, pos[0].y) && g.checkWhite(pos[0].x-2, pos[0].y)) {
            cwtype();
            for (auto p : pos) g.setColour(p.x, p.y, Colour::White);
            pos[0].x-=2;
            pos[1].x--;
            pos[1].y--;
            pos[3].x++;
            pos[3].y--;
            for (auto p : pos) g.setColour(p.x, p.y, Colour::Yellow);
            if (heavy) down(g);
        }
    } else if (type == "B" || type == "D") {
        if (pos[2].y != 10 && g.checkWhite(pos[1].x+1, pos[1].y) && g.checkWhite(pos[2].x, pos[2].y+1)) {
            cwtype();
            for (auto p : pos) g.setColour(p.x, p.y, Colour::White);
            pos[0].x+=2;
            pos[0].x++;
            pos[1].y++;
            pos[3].x--;
            pos[3].y++;
            for (auto p : pos) g.setColour(p.x, p.y, Colour::Yellow);
            if (heavy) down(g);
        }
    }
}

void SBlock::counterclockwise(Grid &g) {
    if (type == "A" || type == "C") {
        if (g.checkWhite(pos[0].x-1, pos[0].y) && g.checkWhite(pos[0].x-2, pos[0].y)) {
            ccwtype();
            for (auto p : pos) g.setColour(p.x, p.y, Colour::White);
            pos[0].x -= 2;
            pos[1].x--;
            pos[1].y--;
            pos[3].x++;
            pos[3].y--;
            for (auto p : pos) g.setColour(p.x, p.y, Colour::Yellow);
            if (heavy) down(g);
        }
    } else if (type == "B" || type == "D") {
        if (pos[2].y != 10 && g.checkWhite(pos[1].x+1, pos[1].y) && g.checkWhite(pos[2].x, pos[2].y+1)) {
            ccwtype();
            for (auto p : pos) g.setColour(p.x, p.y, Colour::White);
            pos[0].x+=2;
            pos[1].x++;
            pos[1].y++;
            pos[3].x--;
            pos[3].y++;
            for (auto p : pos) g.setColour(p.x, p.y, Colour::Yellow);
            if (heavy) down(g);
        }
    }
}

void SBlock::drop(Grid &g) {
    size_t start = pos[2].x+1;
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


void SBlock::giveHint(Grid &g){
}

void SBlock::cancelHint(Grid &g){
}

