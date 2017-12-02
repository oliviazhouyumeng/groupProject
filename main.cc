#include <iostream>
#include <string>
#include <vector>
#include "window.h"
#include "grid.h"
#include "state.h"
#include "block.h"
#include <iostream>
#include <string>
#include <vector>
#include "window.h"
#include "grid.h"
#include "state.h"
#include "block.h"
#include "level.h"
#include <sstream>
#include "endexception.h"
using namespace std;

int main(int argc, char *argv[]) {
    cin.exceptions(ios::eofbit|ios::failbit);
    bool textMode = false;
    int startLevel = 0;
    for (int i = 1; i < argc; ++i){
        string curArg = argv[i];
        if (curArg == "-text") {
            textMode = true;
        } else if (curArg == "-seed") {
            ++i;
            int seedNum = *argv[i];
            // sets the random number generator’s seed to xxx(seedNum)
        } else if (curArg == "-scriptfile") {
            if (!(i+1 >= argc || argv[i+1] == "-seed" || argv[i+1] == "-text" ||
                argv[i+1] == "-startlevel" || argv[i+1] == "-scriptfile")) {
                ++i;
                string scriptFile = argv[i];
            }
            // Use scriptFile instead of sequence.txt as a source of blocks for level 0
        } else if (curArg == "-startlevel") {
            ++i;
            startLevel = *argv[i];
            // Starts the game in level n
        }
    }
    
    Grid g;
    string cmd;
    g.setLevel(startLevel);
    if (textMode) g.setGraphics(false); // init a grid w/ graphics disabled
    g.init();
    
    try {
        while (true) {
            cout << "> "; // wait for input
            cin >> cmd;
            if (cmd == "left") g.currBlock().left(g);
            else if (cmd == "right") g.currBlock().right(g);
            else if (cmd == "down") g.currBlock().down(g);
            else if (cmd == "clockwise") g.currBlock().clockwise(g);
            else if (cmd == "counterclockwise") g.currBlock().counterclockwise(g);
            else if (cmd == "skip") g.updateNext();
            else if (cmd == "drop") {
                g.currBlock().drop();
                try {
                    g.setCurrtoGrid();
                }
                catch(EndException &e) {
                    break;
                    cout << "Game over!" << endl;
                }
                g.updateNext();
            }
            else if (cmd == "levelop") g.levelUp();
            else if (cmd == "leveldown") g.levelDown();
            //else if (cmd == "norandom") file
            //else if (cmd == "random")
            //else if (cmd == "sequence") file
            else if (cmd == "I"||cmd == "J"||cmd == "L"||cmd == "S"||cmd == "z"||cmd == "T"||cmd == "O") g.setNext(cmd);
            else if (cmd == "restart") g.init();
            //else if (cmd == "hint")
        }
    }
    catch (ios::failure &) {}  // Any I/O failure quits
}
