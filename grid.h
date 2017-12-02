#ifndef GRID_H
#define GRID_H
#include <iostream>
#include <vector>
#include <cstddef>
#include "cell.h"
#include <memory>
#include <sstream>

struct State;
class TextDisplay;
class GraphicsDisplay;
class Block;
class Level;
template <typename InfoType, typename StateType> class Observer;
class InvalidMove{};

class Grid {
    std::vector<std::vector<Cell>> theGrid; //the actual grid
    std::vector<std::shared_ptr<Block>> liveBlocks;
    int hi_score; //the highest score in game
    int curr_score; // the current score in game
    int currlevel; //the current level
    std::vector<std::shared_ptr<Level>> levels;
    std::istringstream iss; // for block types reading if Level returns a seq file name
    std::shared_ptr<Block> curr; // the current block on the board
    std::string next; // the next block will appear on the board
    int nextlevel; // the level of next block
    bool graphicsOn; // default = true, false = textonly
    int starCount;
    std::shared_ptr<TextDisplay> td; // the text display
    std::shared_ptr<GraphicsDisplay> gd; // the graphics diaplay
    
    std::shared_ptr<Observer> ob; //Another observer
    // Add private members, if necessary.
    
public:
    Grid(int hi_score = 0, int curr_score = 0, bool graphicsOn = true);
    ~Grid();
    void setObserver(std::shared_ptr<Observer> ob);
    void endGame() const;  // end the game
    void init(); // Sets up an n x n grid.  Clears old grid, if necessary.
    void setGraphics(bool b);
    void levelUp();
    void levelDown();
    std::vector<std::shared_ptr<Level>> &getLevels();
    int getLevel() const;
    void setLevel(int l);
    void clearRow(size_t r);
    void moveDown(); // clear empty lines
    bool isFull(size_t r);
    bool isEmpty(size_t r); // return true if rth row is empty
    void setCurrtoGrid();
    void updateNext();
    void setHint();
    void clearHint();
    std::string getNextType() const;
    void setNext(std::string nextcmd); // set next, modify next level
    void setColour(size_t row, size_t col, Colour colour);
    void changeColour(size_t row, size_t col, Colour colour);
    bool checkWhite(size_t row, size_t col); // return true if cell is white
    void gSetState(size_t row, size_t col, State s) const;
    State getState(size_t row, size_t col) const;
    void updateScore(int point); // update curr_score & hi_score
    int getScore() const;
    int getHiScore() const;
    Cell &getCell(size_t x, size_t y);
    Block &currBlock();
    
    friend std::ostream &operator<<(std::ostream &out, const Grid &g);
};

#endif
