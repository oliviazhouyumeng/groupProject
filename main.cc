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
    if (cmd == "left") {
        g.currBlock().left(g);
        cout << g << endl;
    }
    else if (cmd == "right") {
        g.currBlock().right(g);
        cout << g << endl;
    }
    else if (cmd == "down") {
        g.currBlock().down(g);
        cout << g << endl;
    }
    else if (cmd == "clockwise") {
        g.currBlock().clockwise(g);
        cout << g << endl;
    }
    else if (cmd == "counterclockwise") {
        g.currBlock().counterclockwise(g);
        cout << g << endl;
    }
    else if (cmd == "skip") {
        g.updateNext();
        cout << g << endl;
    }
    else if (cmd == "drop") {
        g.currBlock().drop(g);
        try {
            g.setCurrtoGrid();
        }
        catch(EndException &e) {
            cout << "Game over!" << endl;
        }
        g.updateNext();
        cout << g << endl;
    }
    else if (cmd == "levelup") {
        g.levelUp();
        cout << g << endl;
    }
    else if (cmd == "leveldown") {
        g.levelDown();
        cout << g << endl;
    }
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
    else if (cmd == "I"||cmd == "J"||cmd == "L"||cmd == "S"||cmd == "Z"||cmd == "T"||cmd == "O") {
        g.setNext(cmd);
        cout << g << endl;
    }
    else if (cmd == "restart") {
        g.init();
        cout << g << endl;
    }
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
            if (i+1 < argc) {
                string nextArg = argv[i+1];
                if (!(nextArg == "-scriptfile" || nextArg == "-text" ||
                      nextArg == "-startlevel" || nextArg == "-scriptfile")) {
                    ++i;
                    istringstream iss{nextArg};
                    iss >> seedNum;
                }
            }
        } else if (curArg == "-scriptfile") {
            if (i+1 < argc) {
                string nextArg = argv[i+1];
                if (!(nextArg == "-seed" || nextArg == "-text" ||
                      nextArg == "-startlevel" || nextArg == "-scriptfile")) {
                    ++i;
                    seqFile = argv[i];
                }
            }
        } else if (curArg == "-startlevel") {
            if (i+1 < argc) {
                string nextArg = argv[i+1];
                if (!(nextArg == "-scriptfile" || nextArg == "-text" ||
                      nextArg == "-seed" || nextArg == "-scriptfile")) {
                    ++i;
                    istringstream iss{nextArg};
                    iss >> startLevel;
                }
            }
        }
    }
    
    Grid g;
    string cmd;
    g.setLevel(startLevel);
    if (textMode) g.setGraphics(false); // init a grid w/ graphics disabled
    if (seedNum != 1) {
        for (auto l : g.getLevels()) l->setSeed(seedNum);
    }
    if (seqFile != "") {
        g.getLevels()[0]->setSeq(seqFile);
    }
    g.init();
    cout << g << endl;
    
    try {
        while (true) {
            cout << "> "; // wait for input
            cin >> cmd;
            if (cmd != "sequence") Game(g, cmd);
            else if (cmd == "sequence") {
                string cmdSeq;
                cin >> cmdSeq;
                ifstream f{cmdSeq};
                while (f >> cmd) {
                    Game(g, cmd);
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
