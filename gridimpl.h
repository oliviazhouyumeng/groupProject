#ifndef gridimpl_h
#define gridimpl_h

class TextDisplay;
class GraphicsDisplay;

struct GridImpl{
    std::vector<vector<cell>> theGrid; //the actual grid
    std::vector<unique_ptr<Block>> liveBlocks;
    unique_ptr<Level> l; //the current level
    unique_ptr<Block> curr; // the current block on the board
    unique_ptr<Block> next; // the next block will appear on the board
    unique_ptr<TextDisplay> td = nullptr; // the text display
    unique_ptr<GraphicsDisplay> gd = nullptr; // the graphics diaplay
    int hi_score; //the highest score in game
    int curr_score; // the current score in game
    unique_ptr<Observer<Info, State>> ob = nullptr; //Another observer
};


#endif
