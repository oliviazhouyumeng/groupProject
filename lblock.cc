#include "block.h"
#include "lblock.h"
#include "grid.h"
using namespace std;

LBlock(Grid &g, int level): Llock{level, "A", false} {
    if (level > 2) {heavy = true;}
    Posn p0{3, 2};
    Posn p1{4, 2};
    Posn p2{4, 1};
    Posn p3{4, 0};
    pos.emplace_back(p0);
    pos.emplace_back(p1);
    pos.emplace_back(p2);
    pos.emplace_back(p3);
    for (auto p : pos) {
        if (!g.checkWhite(p.x, p.y)) {g.endGame();}
    }
    for (auto p : pos) g.setColour(p.x, p.y, Colour::Blue);
        }

void LBlock::left(Grid &g) {
    for (auto p : pos) {
        if (p.y == 0) return;
        if ((!g.checkWhite(p.x, p.y-1))&&g.getCell(p.x, p.y-1).getState().stype==StateType::NA) return;
    }
    for (auto p : pos) g.setColour(p.x, p.y, Colour::White);
    for (auto p : pos) p.y--;
    for (auto p : pos) g.setColour(p.x, p.y, Colour::Blue);
    if (heavy) down(g);
}

void LBlock::right(Grid &g) {
    for (auto p : pos) {
        if (p.y == 10) return;
        if (!g.checkWhite(p.x, p.y+1)&&g.getCell(p.x, p.y+1).getState().stype==StateType::NA) return;
    }
    for (auto p : pos) g.setColour(p.x, p.y, Colour::White);
    for (auto p : pos) p.y++;
    for (auto p : pos) g.setColour(p.x, p.y, Colour::Blue);
    if (heavy) down(g);
}

void LBlock::down(Grid &g) {
    for (auto p : pos) {
        if (p.x == 17) return;
        if (g.getCell(p.x+1, p.y).getInfo().colour != Colour::White) return;
    }
    for (auto p : pos) g.setColour(p.x, p.y, Colour::White);
    for (auto p : pos) p.x++;
    for (auto p : pos) g.setColour(p.x, p.y, Colour::Blue);
}

void LBlock::clockwise(Grid &g) {
    if (type == "A") {
        if (g.checkWhite(pos[3].x-1, pos[3].y) && g.checkWhite(pos[3].x-2, pos[3].y)) {
            cwtype();
            for (auto p : pos) g.setColour(p.x, p.y, Colour::White);
            pos[0].x++;
            pos[0].y--;
            pos[1].y-=2;
            pos[2].x--;
            pos[2].y--;
            pos[3].x-=2;
            for (auto p : pos) g.setColour(p.x, p.y, Colour::Blue);
            if (heavy) down(g);
        }
    } else if (type == "B") {
        if (pos[0].y != 10 && g.checkWhite(pos[2].x, pos[2].y+1) &&
            g.checkWhite(pos[2].x, pos[2].y+2)) {
            cwtype();
            for (auto p : pos) g.setColour(p.x, p.y, Colour::White);
            pos[0].y--;
            pos[1].x--;
            pos[2].y++;
            pos[3].x++;
            pos[3].y+=2;
            for (auto p : pos) g.setColour(p.x, p.y, Colour::Blue);
            if (heavy) down(g);
        }
    } else if (type == "C") {
        if (g.checkWhite(pos[1].x-1, pos[1].y) && g.checkWhite(pos[2].x-1, pos[2].y) && g.checkWhite(pos[2].x+1, pos[2].y)) {
            cwtype();
            for (auto p : pos) g.setColour(p.x, p.y, Colour::White);
            pos[0].x-=2;
            pos[1].x--;
            pos[1].y++;
            pos[3].x++;
            pos[3].y--;
            for (auto p : pos) g.setColour(p.x, p.y, Colour::Blue);
            if (heavy) down(g);
        }
    } else if (type == "D") {
        if (pos[1].y != 10 && g.checkWhite(pos[2].x, pos[2].y+1) &&
            g.checkWhite(pos[3].x, pos[3].y+1) && g.checkWhite(pos[3].x, pos[3].y-1) {
            cwtype();
            for (auto p : pos) g.setColour(p.x, p.y, Colour::White);
            pos[0].x++;
            pos[0].y+=2;
            pos[1].x+=2;
            pos[1].y++;
            pos[2].x++;
            pos[3].y--;
            for (auto p : pos) g.setColour(p.x, p.y, Colour::Blue);
            if (heavy) down(g);
        }
    }
}

void LBlock::counterclockwise(Grid &g) {
    if (type == "A") {
        if (g.checkWhite(pos[3].x-2, pos[3].y) && g.checkWhite(pos[2].x-2, pos[2].y)
            && g.checkWhite(pos[2].x-1, pos[2].y)) {
            ccwtype();
            for (auto p : pos) g.setColour(p.x, p.y, Colour::White);
            pos[0].x--;
            pos[0].y-=2;
            pos[1].x-=2;
            pos[1].y--;
            pos[2].x--;
            pos[3].y++;
            for (auto p : pos) g.setColour(p.x, p.y, Colour::Blue);
            if (heavy) down(g);
        }
    } else if (type == "B") {
        if (pos[0] != 10 && g.checkWhite(pos[0].x, pos[0].y+1) &&
            g.checkWhite(pos[0].x-1, pos[0].y+1)) {
            ccwtype();
            for (auto p : pos) g.setColour(p.x, p.y, Colour::White);
            pos[0].x--;
            pos[0].y++;
            pos[1].y+=2;
            pos[2].x++;
            pos[2].y++;
            pos[3].x+=2;
            for (auto p : pos) g.setColour(p.x, p.y, Colour::Blue);
            if (heavy) down(g);
        }
    } else if (type == "C") {
        if (g.checkWhite(pos[1].x-1, pos[1].y) && g.checkWhite(pos[2].x+1, pos[2].y)) {
            ccwtype();
            for (auto p : pos) g.setColour(p.x, p.y, Colour::White);
            pos[0].y++;
            pos[1].x++;
            pos[2].y--;
            pos[3].x--;
            pos[3].y-=2;
            for (auto p : pos) g.setColour(p.x, p.y, Colour::Blue);
            if (heavy) down(g);
        }
    } else if (type == "D") {
        if (pos[1].y != 10 && g.checkWhite(pos[0].x+1, pos[0].y) &&
            g.checkWhite(pos[0].x+2, pos[1].y) && g.checkWhite(pos[2].x, pos[2].y+1)) {
            ccwtype();
            for (auto p : pos) g.setColour(p.x, p.y, Colour::White);
            pos[0].x+=2;
            pos[1].x++;
            pos[1].y--;
            pos[3].x--;
            pos[3].y++;
            for (auto p : pos) g.setColour(p.x, p.y, Colour::Blue);
            if (heavy) down(g);
        }
    }
}

void LBlock::drop(Grid &g) {
    size_t start = pos[2].x;
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

void LBlock::giveHint(Grid &g) {}

void LBlock::cancelHint(Grid &g) {};
