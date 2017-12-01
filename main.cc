#include <iostream>
#include <string>
#include <vector>
#include "window.h"
#include "grid.h"
#include "state.h"
#include "block.h"
#include "level.h"
#include "sstream"
using namespace std;

int main(int argc, char *argv[]) {
    cin.exceptions(ios::eofbit|ios::failbit);
    bool textMode = false;
    int startLevel = 0;
    for (int i = 1; i < argc;){
        string curArg = argv[i];
        if (curArg == "-text") {
            textMode = true;
        } else if (curArg == "-seed") {
            ++i;
            int seedNum = argv[i];
            // sets the random number generator’s seed to xxx(seedNum)
        } else if (curArg == "scriptfile") {
            ++i;
            // xxx : argv[i];
            // Uses xxx instead of sequence.txt as a source of blocks for level 0
        } else if (curArg == "startlevel") {
            ++i;
            startLevel = argv[i];
            // Starts the game in level n
        }
        ++i;
    }
    
    string cmd;
    if (textMode) Grid g; // text only grid
    else Grid g; // text & graphic
    g.init();
    //set level to startLevel
    //generate new blocks

    try {
        while (true) {
            cin >> cmd;
            if (cmd == "left") g.currBlock()->left(); // g.currBlock() accessor
            else if (cmd == "right") g.currBlock()->right();
            else if (cmd == "down") g.currBlock()->down();
            else if (cmd == "clockwise") g.currBlock()->clockwise();
            else if (cmd == "counterclockwise") g.currBlock()->counterclockwise();
            else if (cmd == "drop") {
                g.currBlock()->drop();
                //setPiece
            }
            else if (cmd == "levelop") g.levelUp();
            else if (cmd == "leveldown") g.levelDown();
            //else if (cmd == "norandom") file
            //else if (cmd == "random")
            //else if (cmd == "sequence") file
            // I J L
            else if (cmd == "restart") g.init();
            //hint
        }
    }
    catch (ios::failure &) {}  // Any I/O failure quits
}
