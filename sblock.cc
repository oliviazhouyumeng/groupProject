#include "block.h"
#include "sblock.h"
#include "grid.h"
using namespace std;

SBlock(Grid &g, int level): Block{level, "A", false} {
    if (level > 2) heavy = true;
    Posn p1{4, 0};
    Posn p2{4, 1};
    Posn p3{3, 1};
    Posn p4{3, 2};
    g.setPiece(4, 0, Colour::Yellow);
    g.setPiece(4, 1, Colour::Yellow);
    g.setPiece(3, 1, Colour::Yellow);
    g.setPiece(3, 2, Colour::Yellow);
    pos.emplace_back(p1);
    pos.emplace_back(p2);
    pos.emplace_back(p3);
    pos.emplace_back(p4);
}

void SBlock::left(Grid &g) {
    bool canMove = true;
    for (auto p : pos) {
        if (p.x == 0) return;
        if (g.getCell(p.x-1, p.y).getInfo().colour != Colour::White) canMove = false;
    }
    if (canMove) {
        for (auto p : pos) g.setColour(p.x, p.y, Colour::White);
        for (auto p : pos) p.x--;
        for (auto p : pos) g.setColour(p.x, p.y, Colour::Yellow);
    }
}

void SBlock::right(Grid &g) {
    bool canMove = true;
    for (auto p : pos) {
        if (p.y == 10) return;
        if (g.getCell(p.x, p.y+1).getInfo().colour != Colour::White) canMove = false;
    }
    if (canMove) {
        for (auto p : pos) g.setColour(p.x, p.y, Colour::White);
        for (auto p : pos) p.y++;
        for (auto p : pos) g.setColour(p.x, p.y, Colour::Yellow);
    }
}

void SBlock::down(Grid &g) {
    bool canMove = true;
    for (auto p : pos) {
        if (p.x == 17) return;
        if (g.getCell(p.x+1, p.y).getInfo().colour != Colour::White) canMove = false;
    }
    if (canMove) {
        for (auto p : pos) g.setColour(p.x, p.y, Colour::White);
        for (auto p : pos) p.x++;
        for (auto p : pos) g.setColour(p.x, p.y, Colour::Yellow);
    }
}

void SBlock::clockwise(Grid &g) {
    if (type == "A" || type == "C") {
        if (g.getCell(pos[1].x-1, pos[1].y).getInfo().colour == Colour::White &&
            g.getCell(pos[1].x-2, pos[1].y).getInfo().colour == Colour::White) {
            cwtype();
            for (auto p : pos) g.setColour(p.x, p.y, Colour::White);
            pos[1].x -= 2;
            pos[2].x--;
            pos[2].y--;
            pos[4].x++;
            pos[4].y--;
            for (auto p : pos) g.setColour(p.x, p.y, Colour::Yellow);
        }
    } else if (type == "B" || type == "D") {
        if (g.getCell(pos[2].x+1, pos[2].y).getInfo().colour == Colour::White &&
            g.getCell(pos[3].x, pos[3].y+1).getInfo().colour == Colour::White) {
            cwtype();
            for (auto p : pos) g.setColour(p.x, p.y, Colour::White);
            pos[1].x += 2;
            pos[2].x++;
            pos[2].y++;
            pos[4].x--;
            pos[4].y++;
            for (auto p : pos) g.setColour(p.x, p.y, Colour::Yellow);
        }
    }
}

void SBlock::counterclockwise(Grid &g) {
    if (type == "A" || type == "C") {
        if (g.getCell(pos[1].x-1, pos[1].y).getInfo().colour == Colour::White &&
            g.getCell(pos[1].x-2, pos[1].y).getInfo().colour == Colour::White) {
            ccwtype();
            for (auto p : pos) g.setColour(p.x, p.y, Colour::White);
            pos[1].x -= 2;
            pos[2].x--;
            pos[2].y--;
            pos[4].x++;
            pos[4].y--;
            for (auto p : pos) g.setColour(p.x, p.y, Colour::Yellow);
        }
    } else if (type == "B" || type == "D") {
        if (g.getCell(pos[2].x+1, pos[2].y).getInfo().colour == Colour::White &&
            g.getCell(pos[3].x, pos[3].y+1).getInfo().colour == Colour::White) {
            ccwtype();
            for (auto p : pos) g.setColour(p.x, p.y, Colour::White);
            pos[1].x += 2;
            pos[2].x++;
            pos[2].y++;
            pos[4].x--;
            pos[4].y++;
            for (auto p : pos) g.setColour(p.x, p.y, Colour::Yellow);
        }
    }
}

void SBlock::drop(Grid &g) {
    size_t start = pos[3].y+1;
    for (size_t i = start; i < 18; i++) {
        down(g);
    }
}
// notify observers?
