#ifndef GRID_H
#define GRID_H
#include <iostream>
#include <vector>
#include <cstddef>
#include "cell.h"
#include "state.h"
#include "info.h"
#include "subject.h"
#include "textdisplay.h"
#include "graphicsdisplay.h"
#include "level.h"
#include <memory>
class TextDisplay;
class GraphicsDisplay;
template <typename InfoType, typename StateType> class Observer;
class InvalidMove{};
class Grid {
    std::vector<std::vector<cell>> theGrid; //the actual grid
    std::vector<shared_ptr<Block>> liveBlocks;
    int hi_score; //the highest score in game
    int curr_score; // the current score in game
    int currlevel;//the current level
    std::unique_ptr<vector<Level>> levels = nullptr; //[level0,level1,level2,...]
    std::istringstream iss; // return from level
    std::shared_ptr<Block> curr = nullptr; // the current block on the board
    std::string next; // the next block will appear on the board
    int nextlevel; // the level of next block
    bool gdavailable; // default = true = gd available, false = textonly
    std::unique_ptr<TextDisplay> td = nullptr; // the text display
    std::unique_ptr<GraphicsDisplay> gd = nullptr; // the graphics diaplay
    
    std::unique_ptr<Observer<Info, State>> ob = nullptr; //Another observer
    // Add private members, if necessary.
    
    
public:
    Grid();
    ~Grid();
    void setObserver(unique_ptr<Observer<Info, State>> ob);
    bool endGame() const;  // end the game
    void init(int hi); // Sets up an n x n grid.  Clears old grid, if necessary. //hi: high score
    void setGraphics(bool b);
    void levelUp();
    void levelDown();
    void setLevel(int l);
    void clearRow(size_t r);
    void moveDown(); // clear empty lines
    void isFull(size_t r);
    void isEmpty(size_t r); // return true if rth row is empty
    void setCurrtoGrid();
    void Grid::updateNext();
    void setNext(std::string nextcmd); // set next, modify next level
    void setColour(size_t row, size_t col, Colour col);
    void setPiece(size_t row, size_t col, Colour colour);
    void gSetState(size_t row, size_t col, State s);
    void updateScore(int point); // update curr_score & hi_score
    Cell &getCell(size_t x, size_t y);
    
    friend std::ostream &operator<<(std::ostream &out, const Grid &g);
};

#endif
