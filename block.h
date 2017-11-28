#ifndef BLOCK_H
#define BLOCK_H
#include <string>
#include <vector>
#include <memory>

class BlockImpl;
class Block {
    std::unique_ptr<BlockImpl> pImpl;
public:
    virtual void left() = 0;
    virtual void right() = 0;
    virtual void down() = 0;
    virtual void clockwise() = 0;
    virtual void counterclockwise() = 0;
    virtual void drop() = 0;
    std::unique_ptr<BlockImpl> &getPImpl();
    bool isHeavy() const;
};
#endif
