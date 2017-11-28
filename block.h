#ifndef BLOCK_H
#define BLOCK_H
#include <string>
#include <vector>

class Block {
protected:
    std::unique_ptr<Cell> lowerleft;
    std::string type; // type: "N"(default), "E", "S", "W"
    std::vector<std::unique_ptr<Cell>> cells; // a Block originally contains four Cell
    bool heavy; // default: false
public:
    virtual void left() = 0;
    virtual void right() = 0;
    virtual void down() = 0;
    virtual void clockwise() = 0;
    virtual void counterclockwise() = 0;
    virtual void drop() = 0;
    bool isHeavy() const;
};
#endif
