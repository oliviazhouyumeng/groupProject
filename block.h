#ifndef BLOCK_H
#define BLOCK_H
#include <string>
#include <vector>
#include "cell.h"
#include "posn.h"

class Block {
protected:
    int level;
    bool heavy; // default: false
    std::vector<Posn> pos; // Storing default cells coordinates
    std::string type; // type: "A"(default), "B", "C", "D" clockwise:A->B->C->D
public:
    Block(int level, bool heavy);
    virtual void left(Grid &g) = 0;
    virtual void right(Grid &g) = 0;
    virtual void down(Grid &g) = 0;
    virtual void clockwise(Grid &g) = 0;
    virtual void counterclockwise(Grid &g) = 0;
    virtual void drop(Grid &g) = 0;
    bool isHeavy() const;
    void cwtype(); // change type clockwise
    void ccwtype(); // change type counterclockwise
};
#endif
