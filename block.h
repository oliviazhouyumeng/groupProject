#ifndef BLOCK_H
#define BLOCK_H
#include <string>
#include <vector>
#include "cell.h"
class Block {
protected:
    size_t x, y;
    int level;
    std::string type; // type: "A"(default), "B", "C", "D" clockwise:A->B->C->D
    bool heavy; // default: false
    std::vector<std::shared_ptr<Cell>> cells; // a Block originally contains four Cell
public:
    Block(size_t x, size_t y, int level, std::string type, bool heavy);
    virtual void left() = 0;
    virtual void right() = 0;
    virtual void down() = 0;
    virtual void clockwise() = 0;
    virtual void counterclockwise() = 0;
    virtual void drop() = 0;
    virtual void setNew(Grid &g) = 0; // set cells of the block
    bool isHeavy() const;
    void cwtype(); // change type clockwise
    void ccwtype(); // change type counterclockwise
};
#endif

