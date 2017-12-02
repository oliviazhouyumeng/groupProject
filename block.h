#ifndef BLOCK_H
#define BLOCK_H
#include <string>
#include <vector>
#include "posn.h"
class Block {
protected:
    int level;
    std::string type; // type: "A"(default), "B", "C", "D" clockwise:A->B->C->D
    bool heavy; // default: false
    std::vector<Posn> pos; // a Block originally contains four Cell
    std::vector<Posn> h_pos;
public:
    Block(int level, std::string type, bool heavy);
    virtual void left(Grid &g) = 0;
    virtual void right(Grid &g) = 0;
    virtual void down(Grid &g) = 0;
    virtual void clockwise(Grid &g) = 0;
    virtual void counterclockwise(Grid &g) = 0;
    virtual void drop(Grid &g) = 0;
    virtual void giveHint(Grid &g) = 0;
    virtual void cancelHint(Grid &g) = 0;
    std::vector<Posn>& getPos();
    bool isHeavy() const;
    void cwtype(); // change type clockwise
    void ccwtype(); // change type counterclockwise
    int getBlockLevel() const;
};
#endif
