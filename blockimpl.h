#ifndef BLOCKIMPL_H
#define BLOCKIMPL_H
#include <vector>
#include <string>
#include <memory>

struct BlockImpl {
    std::unique_ptr<Cell> lowerleft;
    std::string type; // type: "N", "E", "S", "W"
    std::vector<std::unique_ptr<Cell>> cells; // a Block originally contains four Cell
    bool heavy;
};

#endif
