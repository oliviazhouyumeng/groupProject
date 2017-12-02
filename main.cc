#include <iostream>
#include <fstream>
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

void Game(Grid &g, string cmd) {
    if (cmd == "left") g.currBlock().left(g);
    else if (cmd == "right") g.currBlock().right(g);
    else if (cmd == "down") g.currBlock().down(g);
    else if (cmd == "clockwise") g.currBlock().clockwise(g);
    else if (cmd == "counterclockwise") g.currBlock().counterclockwise(g);
    else if (cmd == "skip") g.updateNext();
    else if (cmd == "drop") {
        g.currBlock().drop(g);
        try {
            g.setCurrtoGrid();
        }
        catch(EndException &e) {
            cout << "Game over!" << endl;
        }
        g.updateNext();
    }
    else if (cmd == "levelop") g.levelUp();
    else if (cmd == "leveldown") g.levelDown();
    else if (cmd == "norandom") {
        string seq;
        cin >> seq;
        int curlev = g.getLevel();
        if (curlev >= 3) {
            g.getLevels()[curlev]->setSeq(seq);
            g.getLevels()[curlev]->setRandom(false);
        }
    }
    else if (cmd == "random") {
        int curlev = g.getLevel();
        if (curlev >= 3) g.getLevels()[curlev]->setRandom(true);
    }
    else if (cmd == "I"||cmd == "J"||cmd == "L"||cmd == "S"||cmd == "Z"||cmd == "T"||cmd == "O") g.setNext(cmd);
    else if (cmd == "restart") g.init();
    //else if (cmd == "hint")
}

int main(int argc, char *argv[]) {
    cin.exceptions(ios::eofbit|ios::failbit);
    bool textMode = false;
    int startLevel = 0;
    unsigned seedNum = 1;
    string seqFile = "";
    for (int i = 1; i < argc; ++i){
        string curArg = argv[i];
        if (curArg == "-text") {
            textMode = true;
        } else if (curArg == "-seed") {
            ++i;
            seedNum = *argv[i];
        } else if (curArg == "-scriptfile") {
            if (!(i+1 >= argc || argv[i+1] == "-seed" || argv[i+1] == "-text" ||
                argv[i+1] == "-startlevel" || argv[i+1] == "-scriptfile")) {
                ++i;
                seqFile = argv[i];
            }
        } else if (curArg == "-startlevel") {
            ++i;
            startLevel = *argv[i];
        }
    }
    
    Grid g;
    string cmd;
    g.setLevel(startLevel);
    if (textMode) g.setGraphics(false); // init a grid w/ graphics disabled
    if (seedNum != 1) {
        for (auto l : g.getLevels()) l->getSeed(seedNum);
    }
    if (seqFile != "") {
        g.getLevels()[0]->setSeq(seqFile);
    }
    g.init();
    
    try {
        while (true) {
            cout << "> "; // wait for input
            cin >> cmd;
            if (cmd != "sequence") try {Game(g, cmd);}
            else if (cmd == "sequence") {
                string cmdSeq;
                cin >> cmdSeq;
                ifstream f{cmdSeq};
                while (f >> cmd) {
                    try {Game(g, cmd);}
                }
            }
            else {
                cin.clear();
                cin.ignore();
            }
        }
    }
    catch (ios::failure &) {}  // Any I/O failure quits
}
