#ifndef GRIDIMPL_H
#define GRIDIMPL_H

class TextDisplay;
class GraphicsDisplay;

struct GridImpl{
    std::vector<vector<cell>> theGrid; //the actual grid
    std::vector<std::unique_ptr<Block>> liveBlocks;
    std::unique_ptr<Level> l; //the current level
    std::unique_ptr<Block> curr; // the current block on the board
    std::unique_ptr<Block> next; // the next block will appear on the board
    std::unique_ptr<TextDisplay> td = nullptr; // the text display
    std::unique_ptr<GraphicsDisplay> gd = nullptr; // the graphics diaplay
    int hi_score; //the highest score in game
    int curr_score; // the current score in game
    std::unique_ptr<Observer<Info, State>> ob = nullptr; //Another observer
};

#endif
