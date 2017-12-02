#include "block.h"
#include "oblock.h"
#include "grid.h"
using namespace std;

OBlock(Grid &g, int level): Block{level, "A", false} {
    if (level > 2) {heavy = true;}
    Posn p0{3, 0};
    Posn p1{4, 0};
    Posn p2{4, 1};
    Posn p3{3, 1};
    for (auto p : pos) {
        if (!g.checkWhite(p.x, p.y)) {g.endGame();}
    }
    g.setColour(3, 0, Colour::Yellow);
    g.setColour(4, 0, Colour::Yellow);
    g.setColour(4, 1, Colour::Yellow);
    g.setColour(3, 1, Colour::Yellow);
    pos.emplace_back(p0);
    pos.emplace_back(p1);
    pos.emplace_back(p2);
    pos.emplace_back(p3);
}

void OBlock::left(Grid &g) {
    for (auto p : pos) {
        if (p.y == 0) return;
        if ((!g.checkWhite(p.x, p.y-1))&&g.getCell(p.x, p.y-1).getState().stype==StateType::NA) return;
    }
    for (auto p : pos) g.setColour(p.x, p.y, Colour::White);
    for (auto p : pos) p.y--;
    for (auto p : pos) g.setColour(p.x, p.y, Colour::Cyan);
    if (heavy) down(g);
}

void OBlock::right(Grid &g) {
    for (auto p : pos) {
        if (p.y == 10) return;
        if (!g.checkWhite(p.x, p.y+1)&&g.getCell(p.x, p.y+1).getState().stype==StateType::NA) return;
    }
    for (auto p : pos) g.setColour(p.x, p.y, Colour::White);
    for (auto p : pos) p.y++;
    for (auto p : pos) g.setColour(p.x, p.y, Colour::Cyan);
    if (heavy) down(g);
}

void OBlock::down(Grid &g) {
    for (auto p : pos) {
        if (p.x == 17) return;
        if (g.getCell(p.x+1, p.y).getInfo().colour != Colour::White) return;
    }
    for (auto p : pos) g.setColour(p.x, p.y, Colour::White);
    for (auto p : pos) p.x++;
    for (auto p : pos) g.setColour(p.x, p.y, Colour::Cyan);
}

void OBlock::clockwise(Grid &g) {
    if (heavy) down(g);
}

void OBlock::counterclockwise(Grid &g) {
    if (heavy) down(g);
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
    for (auto p : pos) {
        if (g.isFull(p.x)) g.clearRow(p.x);
    }
    g.moveDown();
}
