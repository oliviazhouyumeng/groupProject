#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include "window.h"
#include "grid.h"
#include "state.h"
#include "block.h"
#include "level.h"
#include <sstream>
#include "endexception.h"
using namespace std;

void Game(Grid &g, string cmd) {
    if (cmd == "left" || cmd == "lef") {
        g.currBlock().left(g);
        cout << g << endl;
    }
    else if (cmd == "right" || cmd == "ri" || cmd == "rig" || cmd == "righ") {
        g.currBlock().right(g);
        cout << g << endl;
    }
    else if (cmd == "down" || cmd == "do" || cmd == "dow") {
        g.currBlock().down(g);
        cout << g << endl;
    }
    else if (cmd == "clockwise" || cmd == "cw") {
        g.currBlock().clockwise(g);
        cout << g << endl;
    }
    else if (cmd == "counterclockwise" || cmd == "ccw") {
        g.currBlock().counterclockwise(g);
        cout << g << endl;
    }
    else if (cmd == "skip" || cmd == "s") {
        g.updateNext();
        cout << g << endl;
    }
    else if (cmd == "drop" || cmd == "dr") {
        g.currBlock().drop(g);
        try {
            g.setCurrtoGrid();
            g.updateNext();
            cout << g << endl;
        }
        catch(EndException &e) {
            cout << "Game over!" << endl;
        }
    }
    else if (cmd == "levelup" || cmd == "lu") {
        g.levelUp();
        cout << g << endl;
    }
    else if (cmd == "leveldown" || cmd == "ld") {
        g.levelDown();
        cout << g << endl;
    }
    else if (cmd == "norandom") {
        string seq;
        cin >> seq;
        int curlev = g.getLevel();
        if (curlev >= 3) {
            g.getLevels()[curlev]->setRandom(false);
            g.getLevels()[curlev]->setSeq(seq);
            g.setNoRand(true);
        }
    }
    else if (cmd == "random") {
        int curlev = g.getLevel();
        if (curlev >= 3) g.getLevels()[curlev]->setRandom(true);
    }
    else if (cmd == "I"||cmd == "J"||cmd == "L"||cmd == "S"||cmd == "Z"||cmd == "T"||cmd == "O") {
        g.changeCurr(cmd);
        cout << g << endl;
    }
    //else if (cmd == "hint")
}

int main(int argc, char *argv[]) {
    cin.exceptions(ios::eofbit|ios::failbit);
    bool textMode = false;
    int startLevel = 0;
    unsigned seedNum = time(0);
    bool setseed = false;
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
                    setseed = true;
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
    g.setStartLevel(startLevel);
    if (textMode) g.setGraphics(false); // init a grid w/ graphics disabled
    if (setseed) {
        for (auto l : g.getLevels()) {
            l->setSeed(seedNum);
            l->setIsSeed(true);
        }
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
            if (cmd != "sequence" && cmd != "restart") Game(g, cmd);
            else if (cmd == "sequence") {
                string cmdSeq;
                cin >> cmdSeq;
                ifstream f{cmdSeq};
                while (f >> cmd) {
                    Game(g, cmd);
                }
            }
            else if (cmd == "restart") {
                g.init();
                cout << g << endl;
            }
            else {
                cin.clear();
                cin.ignore();
            }
        }
    }
    catch (ios::failure &) {}  // Any I/O failure quits
}
