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
    string cmd;
    Grid g;
    g.init();
    //set level

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
