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
class Observer;
class InvalidMove{};

class Grid {
    std::vector<std::vector<Cell>> theGrid; //the actual grid
    std::vector<std::shared_ptr<Block>> liveBlocks;
    int hi_score; //the highest score in game
    int curr_score; // the current score in game
    int currlevel; //the current level
    int startLevel; 
    std::vector<std::shared_ptr<Level>> levels;
    int seqCount;
    std::string blockSeq;// for block types reading if Level returns a seq file name
    std::shared_ptr<Block> curr; // the current block on the board
    std::string next; // the next block will appear on the board
    int nextlevel; // the level of next block
    bool graphicsOn; // default = true, false = textonly
    int starCount;
    bool redraw;
    bool isNoRand;
    std::shared_ptr<TextDisplay> td; // the text display
    std::shared_ptr<GraphicsDisplay> gd; // the graphics diaplay
    // Add private members, if necessary.
    
public:
    Grid(int hi_score = 0, int curr_score = 0, bool graphicsOn = true, bool redraw = false, bool isNoRand = false);
    ~Grid();
    void setGraphics(std::shared_ptr<GraphicsDisplay> GD);
    void endGame() const;  // end the game
    void init(); // Sets up an n x n grid.  Clears old grid, if necessary.
    void Graphics(bool b);
    bool isGraphics() const;
    void levelUp();
    void levelDown();
    std::vector<std::shared_ptr<Level>> &getLevels();
    int getLevel() const;
    void setStartLevel(int l);
    void clearRow(size_t r);
    void moveDown(); // clear empty lines
    bool isFull(size_t r);
    bool isEmpty(size_t r); // return true if rth row is empty
    void setCurrtoGrid();
    void updateNext();
    void setHint();
    void clearHint();
    std::string getNextType() const;
    void changeCurr(std::string cmd);
    void setColour(size_t row, size_t col, Colour colour);
    void changeColour(size_t row, size_t col, Colour colour);
    bool checkWhite(size_t row, size_t col); // return true if cell is white
    void gSetState(size_t row, size_t col, State s);
    State getState(size_t row, size_t col);
    void updateScore(int point); // update curr_score & hi_score
    int getScore() const;
    int getHiScore() const;
    bool getRedraw() const;
    void setRedraw(bool rd);
    void setNoRand(bool nr);
    Cell &getCell(size_t x, size_t y);
    Block &currBlock();
    
    friend std::ostream &operator<<(std::ostream &out, const Grid &g);
};

#endif
