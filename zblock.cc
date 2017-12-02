#include "block.h"
#include "zblock.h"
#include "grid.h"
using namespace std;

ZBlock(Grid &g, int level): Block{level, "A", false} {
    if (level > 2) {heavy = true;}
    Posn p1{3, 0};
    Posn p2{3, 1};
    Posn p3{4, 1};
    Posn p4{4, 2};
    for (auto p : pos) {
        if (!g.checkWhite(p.x, p.y)) {g.endGame();}
    }
    g.setColour(3, 0, Colour::Magenta);
    g.setColour(3, 1, Colour::Magenta);
    g.setColour(4, 1, Colour::Magenta);
    g.setColour(4, 2, Colour::Magenta);
    pos.emplace_back(p1);
    pos.emplace_back(p2);
    pos.emplace_back(p3);
    pos.emplace_back(p4);
}

void ZBlock::left(Grid &g) {
    for (auto p : pos) {
        if (p.y == 0) return;
        if ((!g.checkWhite(p.x, p.y-1))&&g.getCell(p.x, p.y-1).getState().stype==StateType::NA) return;
    }
    for (auto p : pos) g.setColour(p.x, p.y, Colour::White);
    for (auto p : pos) p.y--;
    for (auto p : pos) g.setColour(p.x, p.y, Colour::Magenta);
    if (heavy) down(g);
}

void ZBlock::right(Grid &g) {
    for (auto p : pos) {
        if (p.y == 0) return;
        if ((!g.checkWhite(p.x, p.y+1))&&g.getCell(p.x, p.y+1).getState().stype==StateType::NA) return;
    }
    for (auto p : pos) g.setColour(p.x, p.y, Colour::White);
    for (auto p : pos) p.y++;
    for (auto p : pos) g.setColour(p.x, p.y, Colour::Magenta);
    if (heavy) down(g);
}

void ZBlock::down(Grid &g) {
    for (auto p : pos) {
        if (p.x == 17) return;
        if (g.getCell(p.x+1, p.y).getInfo().colour != Colour::White) return;
    }
    for (auto p : pos) g.setColour(p.x, p.y, Colour::White);
    for (auto p : pos) p.x++;
    for (auto p : pos) g.setColour(p.x, p.y, Colour::Magenta);
}

void ZBlock::clockwise(Grid &g) {
    if (type == "A" || type == "C") {
        if (g.checkWhite(pos[1].x+1, pos[2].y) && g.checkWhite(pos[2].x-1, pos[3].y)) {
            cwtype();
            for (auto p : pos) g.setColour(p.x, p.y, Colour::White);
            pos[1].x--;
            pos[1].y++;
            pos[3].x++;
            pos[3].y--;
            pos[4].y-=2;
            for (auto p : pos) g.setColour(p.x, p.y, Colour::Yellow);
            if (heavy) down(g);
        }
    } else if (type == "B" || type == "D") {
        if (g.checkWhite(pos[4].x, pos[4].y+1) && g.checkWhite(pos[4].x, pos[4].y+2)
            && pos[2].y!=10) {
            cwtype();
            for (auto p : pos) g.setColour(p.x, p.y, Colour::White);
            pos[1].x++;
            pos[1].y--;
            pos[3].x--;
            pos[3].y++;
            pos[4].y+=2;
            for (auto p : pos) g.setColour(p.x, p.y, Colour::Yellow);
            if (heavy) down(g);
        }
    }
}

void ZBlock::counterclockwise(Grid &g) {
    if (type == "A" || type == "C") {
        if (g.checkWhite(pos[1].x+1, pos[2].y) && g.checkWhite(pos[2].x-1, pos[3].y)) {
            ccwtype();
            for (auto p : pos) g.setColour(p.x, p.y, Colour::White);
            pos[1].x--;
            pos[1].y++;
            pos[3].x++;
            pos[3].y--;
            pos[4].y-=2;
            for (auto p : pos) g.setColour(p.x, p.y, Colour::Yellow);
            if (heavy) down(g);
        }
    } else if (type == "B" || type == "D") {
        if (g.checkWhite(pos[4].x, pos[4].y+1) && g.checkWhite(pos[4].x, pos[4].y+2)
            && pos[2].y!=10) {
            ccwtype();
            for (auto p : pos) g.setColour(p.x, p.y, Colour::White);
            pos[1].x++;
            pos[1].y--;
            pos[3].x--;
            pos[3].y++;
            pos[4].y+=2;
            for (auto p : pos) g.setColour(p.x, p.y, Colour::Yellow);
            if (heavy) down(g);
        }
    }
}

void ZBlock::drop(Grid &g) {
    size_t start = pos[2].x+1;
    for (size_t i = start; i < 18; i++) {
        down(g);
    }
    State s{StateType::NA};
    for (auto p : pos) {
        g.gSetState(p.x, p.y, s);
    }
}
