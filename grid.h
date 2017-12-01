#ifndef GRID_H
#define GRID_H
#include <iostream>
#include <vector>
#include <cstddef>
#include "cell.h"
#include "level.h" // forward declare?
#include <memory>
#include <sstream>
struct State;
class TextDisplay;
class GraphicsDisplay;
class Block;
template <typename InfoType, typename StateType> class Observer;
class InvalidMove{};
class Grid {
    std::vector<std::vector<Cell>> theGrid; //the actual grid
    std::vector<std::shared_ptr<Block>> liveBlocks;
    int hi_score; //the highest score in game
    int curr_score; // the current score in game
    int currlevel;//the current level
    std::unique_ptr<std::vector<Level>> levels = nullptr; //[level0,level1,level2,...]
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
    void setObserver(std::unique_ptr<Observer<Info, State>> ob);
    bool endGame() const;  // end the game
    void init(); // Sets up an n x n grid.  Clears old grid, if necessary.
    void setGraphics(bool b);
    void levelUp();
    void levelDown();
    void setLevel(int l);
    void clearRow(size_t r);
    void moveDown(size_t r); // clear empty lines
    bool isFull(size_t r);
    bool isEmpty(size_t r); // return true if rth row is empty
    void setCurrtoGrid();
    void updateNext();
    void setNext(std::string nextcmd); // set next, modify next level
    void setColour(size_t row, size_t col, Colour colour);
    //void setPiece(size_t row, size_t col, Colour colour);
    bool checkWhite(size_t row, size_t col); // return true if cell is white
    void gSetState(size_t row, size_t col, State s);
    State getState(size_t row, size_t col);
    void updateScore(int point); // update curr_score & hi_score
    Cell &getCell(size_t x, size_t y);
    Block &currBlock();
    
    friend std::ostream &operator<<(std::ostream &out, const Grid &g);
};

#endif
