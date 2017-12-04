#include "block.h"
#include "zblock.h"
#include "grid.h"
#include "info.h"
#include "state.h"
#include <vector>
using namespace std;

ZBlock::ZBlock(Grid &g, int level): Block{level, "A"} {
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
    unsigned temp = 0;
    while (temp < 4 && temp < pos.size()) {
        while (g.isFull(pos[temp].x)) g.clearRow(pos[temp].x);
        temp++;
    }
    if (type == "A" || type == "C") g.moveDown(2);
    else if (type == "B" || type == "D") g.moveDown(3);
}

void ZBlock::giveHint(Grid &g){
    size_t lc = 19;
    size_t mc = 19;
    size_t rc = 19;
    size_t br = 19;
    
    if (type == "A" || type == "C") {
        lc = pos[0].y;
        mc = pos[1].y;
        rc = pos[3].y;
        br = pos[3].x;
    } else if (type == "B" || type == "D") {
        if (pos[1].y == 10){
            lc = pos[3].y-1;
            mc = pos[3].y;
            rc = pos[0].y;
            br = pos[3].x;
        } else {
            lc = pos[3].y;
            mc = pos[0].y;
            rc = pos[0].y+1;
            br = pos[3].x;
        }
    }
    while (true) {
        if (br != 18 && ((g.checkWhite(br, lc) || g.checkActive(br, lc)) &&
                         (g.checkWhite(br, mc) || g.checkActive(br, mc)) &&
                         (g.checkWhite(br, rc) || g.checkActive(br, rc)))) {
            br++;
        } else if (br == 18 || ((!g.checkWhite(br, lc) && !g.checkActive(br, lc)) &&
                                (!g.checkWhite(br, mc) && !g.checkActive(br, mc)) &&
                                (!g.checkWhite(br, rc) && !g.checkActive(br, rc)))) {
            // 1 xxx
            Posn hp0{br-2, lc};
            Posn hp1{br-2, mc};
            Posn hp2{br-1, mc};
            Posn hp3{br-1, rc};
            h_pos.emplace_back(hp0);
            h_pos.emplace_back(hp1);
            h_pos.emplace_back(hp2);
            h_pos.emplace_back(hp3);
            break;
        } else if ((!g.checkWhite(br, lc) && !g.checkActive(br, lc)) &&
                   (g.checkWhite(br, mc) || g.checkActive(br, mc)) &&
                   (g.checkWhite(br, rc) || g.checkActive(br, rc))) {
            // 2 x--
            Posn hp0{br-1, lc};
            Posn hp1{br-1, mc};
            Posn hp2{br, mc};
            Posn hp3{br, rc};
            h_pos.emplace_back(hp0);
            h_pos.emplace_back(hp1);
            h_pos.emplace_back(hp2);
            h_pos.emplace_back(hp3);
            break;
        } else if ((g.checkWhite(br, lc) || g.checkActive(br, lc)) &&
                   (!g.checkWhite(br, mc) && !g.checkActive(br, mc)) &&
                   (g.checkWhite(br, rc) || g.checkActive(br, rc))) {
            // 3 -x-
            Posn hp0{br-2, mc};
            Posn hp1{br-1, mc};
            Posn hp2{br-1, lc};
            Posn hp3{br, lc};
            h_pos.emplace_back(hp0);
            h_pos.emplace_back(hp1);
            h_pos.emplace_back(hp2);
            h_pos.emplace_back(hp3);
            break;
        } else if ((g.checkWhite(br, lc) || g.checkActive(br, lc)) &&
                   (g.checkWhite(br, mc) || g.checkActive(br, mc)) &&
                   (!g.checkWhite(br, rc) && !g.checkActive(br, rc))) {
            // 4 --x
            Posn hp0{br-2, rc};
            Posn hp1{br-1, rc};
            Posn hp2{br-1, mc};
            Posn hp3{br, mc};
            h_pos.emplace_back(hp0);
            h_pos.emplace_back(hp1);
            h_pos.emplace_back(hp2);
            h_pos.emplace_back(hp3);
            break;
        } else if ((!g.checkWhite(br, lc) && !g.checkActive(br, lc)) &&
                   (!g.checkWhite(br, mc) && !g.checkActive(br, mc)) &&
                   (g.checkWhite(br, rc) || g.checkActive(br, rc))) {
            // 5 xx-
            if (lc != 0 && (g.checkWhite(br-2, lc-1) || g.checkActive(br-2, lc-1))) {
                Posn hp0{br-2, lc-1};
                Posn hp1{br-2, lc};
                Posn hp2{br-1,lc};
                Posn hp3{br-1, mc};
                h_pos.emplace_back(hp0);
                h_pos.emplace_back(hp1);
                h_pos.emplace_back(hp2);
                h_pos.emplace_back(hp3);
                break;
            } else {
                Posn hp0{br-3, rc};
                Posn hp1{br-2, rc};
                Posn hp2{br-2, mc};
                Posn hp3{br-1, mc};
                h_pos.emplace_back(hp0);
                h_pos.emplace_back(hp1);
                h_pos.emplace_back(hp2);
                h_pos.emplace_back(hp3);
                break;
            }
        } else if ((g.checkWhite(br, lc) || g.checkActive(br, lc)) &&
                   (!g.checkWhite(br, mc) && !g.checkActive(br, mc)) &&
                   (!g.checkWhite(br, rc) && !g.checkActive(br, rc))) {
            // 6 -xx
            Posn hp0{br-2, mc};
            Posn hp1{br-1, mc};
            Posn hp2{br-1, lc};
            Posn hp3{br, lc};
            h_pos.emplace_back(hp0);
            h_pos.emplace_back(hp1);
            h_pos.emplace_back(hp2);
            h_pos.emplace_back(hp3);
            break;
        } else if ((!g.checkWhite(br, lc) && !g.checkActive(br, lc)) &&
                   (g.checkWhite(br, mc) || g.checkActive(br, mc)) &&
                   (!g.checkWhite(br, rc) && !g.checkActive(br, rc))) {
            // 7 x-x
            Posn hp0{br-2, rc};
            Posn hp1{br-1, rc};
            Posn hp2{br-1, mc};
            Posn hp3{br, mc};
            h_pos.emplace_back(hp0);
            h_pos.emplace_back(hp1);
            h_pos.emplace_back(hp2);
            h_pos.emplace_back(hp3);
            break;
        }
    }
    for(auto hp : h_pos){
        g.changeColour(hp.x, hp.y, Colour::Black);
    }
}

void ZBlock::cancelHint(Grid &g){
    for(auto hp : h_pos){
        if (g.checkActive(hp.x, hp.y)) g.changeColour(hp.x, hp.y, Colour::Magenta);
        else g.changeColour(hp.x, hp.y, Colour::White);
    }
    h_pos.clear();
}
