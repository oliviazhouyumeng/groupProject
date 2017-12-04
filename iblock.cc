#include "block.h"
#include "iblock.h"
#include "grid.h"
using namespace std;

const string startType = "A";
const bool is_Heavy = false;

IBlock::IBlock(Grid &g, int level):Block{level, startType}{
    
    Posn first = Posn{3,0};
    Posn second = Posn{3,1};
    Posn third = Posn{3, 2};
    Posn forth = Posn{3,3};
    if(!g.checkWhite(first.x, first.y)) {
        g.endGame();
    }
    if(!g.checkWhite(second.x, second.y)) {
        g.endGame();
    }
    if(!g.checkWhite(third.x, third.y)) {
        g.endGame();
    }
    if(!g.checkWhite(forth.x, forth.y)) {
        g.endGame();
    }
    
    pos.push_back(first);
    pos.push_back(second);
    pos.push_back(third);
    pos.push_back(forth);
    for(auto p : pos){
        g.setColour(p.x, p.y, Colour::Red);
    }
    
}



void IBlock::left(Grid &g){
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
        g.setColour(p.x, p.y, Colour::Red);
    }
    if (g.getLevel() > 2) down(g);
}


void IBlock::right(Grid &g){
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
        g.setColour(p.x, p.y, Colour::Red);
    }
    if (g.getLevel() > 2) down(g);
}

void IBlock::down(Grid &g){
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
        g.setColour(p.x, p.y, Colour::Red);
    }
}


void IBlock::clockwise(Grid &g){
    if(type == "A" || type == "C"){
        if(g.checkWhite(pos[0].x-1, pos[0].y) && g.checkWhite(pos[0].x-2, pos[0].y) &&
           g.checkWhite(pos[0].x-3, pos[0].y)){
            for(auto p : pos){
                g.setColour(p.x, p.y, Colour::White);
            }
            pos[0].x-=3;
            pos[1].x-=2;
            pos[1].y--;
            pos[2].x--;
            pos[2].y-=2;
            pos[3].y-=3;
            for(auto p : pos){
                g.setColour(p.x, p.y, Colour::Red);
            }
            cwtype();
            if (g.getLevel() > 2) down(g);
        }
    }
    else if(type == "B" || type == "D"){
        if(pos[0].y == 8) return;
        if(g.checkWhite(pos[3].x, pos[3].y+1) && g.checkWhite(pos[3].x, pos[3].y+2) &&
           g.checkWhite(pos[3].x, pos[3].y+3)){
            for(auto p : pos){
                g.setColour(p.x, p.y, Colour::White);
            }
            pos[0].x+=3;
            pos[1].x+=2;
            pos[1].y++;
            pos[2].x++;
            pos[2].y+=2;
            pos[3].y+=3;
            for(auto p : pos){
                g.setColour(p.x, p.y, Colour::Red);
            }
            cwtype();
            if (g.getLevel() > 2) down(g);
        }
    }
}


void IBlock::counterclockwise(Grid &g){
    if(type == "A" || type == "C"){
        if(g.checkWhite(pos[0].x-1, pos[0].y) && g.checkWhite(pos[0].x-2, pos[0].y) &&
           g.checkWhite(pos[0].x-3, pos[0].y)){
            for(auto p : pos){
                g.setColour(p.x, p.y, Colour::White);
            }
            pos[0].x-=3;
            pos[1].x-=2;
            pos[1].y--;
            pos[2].x--;
            pos[2].y-=2;
            pos[3].y-=3;
            for(auto p : pos){
                g.setColour(p.x, p.y, Colour::Red);
            }
            ccwtype();
            if (g.getLevel() > 2) down(g);
        }
    }
    else if(type == "B" || type == "D"){
        if(pos[0].y == 8) return;
        if(g.checkWhite(pos[3].x, pos[3].y+1) && g.checkWhite(pos[3].x, pos[3].y+2) &&
           g.checkWhite(pos[3].x, pos[3].y+3)){
            for(auto p : pos){
                g.setColour(p.x, p.y, Colour::White);
            }
            pos[0].x+=3;
            pos[1].x+=2;
            pos[1].y++;
            pos[2].x++;
            pos[2].y+=2;
            pos[3].y+=3;
            for(auto p : pos){
                g.setColour(p.x, p.y, Colour::Red);
            }
            ccwtype();
            if (g.getLevel() > 2) down(g);
        }
    }
}


void IBlock::drop(Grid &g){
    size_t lowest = pos[3].x;
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
    if (type == "A" || type == "C") g.moveDown(1);
    else if (type == "B" || type == "D") g.moveDown(4);
}




void IBlock::giveHint(Grid &g){
    size_t c1;
    size_t c2;
    size_t c3;
    size_t c4;
    size_t bot;
    if(type == "A" || type == "C"){
        c1 = pos[0].y;
        c2 = pos[1].y;
        c3 = pos[2].y;
        c4 = pos[3].y;
        bot = pos[0].x;
    }
    else{
        c1 = pos[0].y;
        c2 = c1 + 1;
        c3 = c2 + 1;
        c4 = c3 + 1;
        bot = pos[3].x;
    }
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
        if(c2 < 9 && g.getCell(i, c1).getInfo().colour == Colour::White && g.getCell(i, c2).getInfo().colour == Colour::White
           && g.getCell(i, c3).getInfo().colour == Colour::White && g.getCell(i, c4).getInfo().colour == Colour::White){
            if(i==17){
                Posn first{i, c1};
                Posn second{i, c2};
                Posn third{i, c3};
                Posn forth{i, c4};
                h_pos.push_back(first);
                h_pos.push_back(second);
                h_pos.push_back(third);
                h_pos.push_back(forth);
                for(auto hp : h_pos){
                    g.changeColour(hp.x, hp.y, Colour::Black);
                }
                return;
            }
            else if(g.getCell(i+1, c1).getInfo().colour != Colour::White && g.getCell(i+1, c2).getInfo().colour != Colour::White
                    && g.getCell(i+1, c3).getInfo().colour != Colour::White && g.getCell(i+1, c4).getInfo().colour != Colour::White){
                Posn first{i, c1};
                Posn second{i, c2};
                Posn third{i, c3};
                Posn forth{i, c4};
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
        else if((type == "B" || type == "D") && c1 >=3 && g.getCell(i, c1).getInfo().colour == Colour::White &&
           g.getCell(i, c1-1).getInfo().colour == Colour::White && g.getCell(i, c1-2).getInfo().colour == Colour::White
           && g.getCell(i, c1-3).getInfo().colour == Colour::White){
            if(i==17){
                Posn first{i, c1-3};
                Posn second{i, c1-2};
                Posn third{i, c1-1};
                Posn forth{i, c1};
                h_pos.push_back(first);
                h_pos.push_back(second);
                h_pos.push_back(third);
                h_pos.push_back(forth);
                for(auto hp : h_pos){
                    g.changeColour(hp.x, hp.y, Colour::Black);
                }
                return;
            }
            else if(g.getCell(i+1, c1-1).getInfo().colour != Colour::White && g.getCell(i+1, c1-2).getInfo().colour != Colour::White
                    && g.getCell(i+1, c1-3).getInfo().colour != Colour::White && g.getCell(i+1, c1).getInfo().colour != Colour::White){
                Posn first{i, c1-3};
                Posn second{i, c1-2};
                Posn third{i, c1-1};
                Posn forth{i, c1};
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
        else if(g.getCell(i, c1).getInfo().colour != Colour::White){
            if(g.getCell(i-1, c1).getInfo().colour == Colour::White && g.getCell(i-2, c1).getInfo().colour == Colour::White
               && g.getCell(i-3, c1).getInfo().colour == Colour::White && g.getCell(i-4, c1).getInfo().colour == Colour::White){
                Posn first{i-1, c1};
                Posn second{i-2, c1};
                Posn third{i-3, c1};
                Posn forth{i-4, c1};
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
        else if(c2 < 9 && g.getCell(i, c2).getInfo().colour != Colour::White){
            if(g.getCell(i-1, c2).getInfo().colour == Colour::White && g.getCell(i-2, c2).getInfo().colour == Colour::White
               && g.getCell(i-3, c2).getInfo().colour == Colour::White && g.getCell(i-4, c2).getInfo().colour == Colour::White){
                Posn first{i-1, c2};
                Posn second{i-2, c2};
                Posn third{i-3, c2};
                Posn forth{i-4, c2};
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
        else if(c2 < 9 && g.getCell(i, c3).getInfo().colour != Colour::White){
            if(g.getCell(i-1, c3).getInfo().colour == Colour::White && g.getCell(i-2, c3).getInfo().colour == Colour::White
               && g.getCell(i-3, c3).getInfo().colour == Colour::White && g.getCell(i-4, c3).getInfo().colour == Colour::White){
                Posn first{i-1, c3};
                Posn second{i-2, c3};
                Posn third{i-3, c3};
                Posn forth{i-4, c3};
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
        else if(c2 < 9 && g.getCell(i, c4).getInfo().colour != Colour::White){
            if(g.getCell(i-1, c4).getInfo().colour == Colour::White && g.getCell(i-2, c4).getInfo().colour == Colour::White
               && g.getCell(i-3, c4).getInfo().colour == Colour::White && g.getCell(i-4, c4).getInfo().colour == Colour::White){
                Posn first{i-1, c4};
                Posn second{i-2, c4};
                Posn third{i-3, c4};
                Posn forth{i-4, c4};
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
    if(c2 >= 9){
        Posn first{14, 10};
        Posn second{15, 10};
        Posn third{16,10};
        Posn forth{17,10};
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

void IBlock::cancelHint(Grid &g){
    for(auto hp : h_pos){
        g.changeColour(hp.x, hp.y, Colour::White);
    }
    h_pos.clear();
}


