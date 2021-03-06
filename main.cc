#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "window.h"
#include "grid.h"
#include "state.h"
#include "block.h"
#include "level.h"
#include <sstream>
#include "graphicsdisplay.h"
#include "endexception.h"
using namespace std;

void Game(Grid &g, string cmd) {
    if (cmd == "left" || cmd.substr(0, 3) == "lef") {
        g.currBlock().cancelHint(g);
        g.currBlock().left(g);
    }
    else if (cmd == "right" || cmd.substr(0, 2) == "ri") {
        g.currBlock().cancelHint(g);
        g.currBlock().right(g);
    }
    else if (cmd == "down" || cmd.substr(0, 2) == "do") {
        g.currBlock().cancelHint(g);
        g.currBlock().down(g);
    }
    else if (cmd == "clockwise" || cmd.substr(0, 2) == "cl" || cmd == "cw") {
        g.currBlock().cancelHint(g);
        g.currBlock().clockwise(g);
    }
    else if (cmd == "counterclockwise" || cmd.substr(0, 2) == "co" || cmd == "ccw") {
        g.currBlock().cancelHint(g);
        g.currBlock().counterclockwise(g);
    }
    else if (cmd == "skip" || cmd.substr(0, 2) == "sk") {
        g.currBlock().cancelHint(g);
        g.updateNext();
    }
    else if (cmd == "drop" || cmd.substr(0, 2) == "dr") {
        g.currBlock().cancelHint(g);
        g.currBlock().drop(g);
        try {
            g.setCurrtoGrid();
            g.updateNext();
        }
        catch(EndException &e) {
            cout << "Game over!" << endl;
        }
    }
    else if (cmd == "levelup" || cmd.substr(0, 6) == "levelu" || cmd == "lu") {
        g.currBlock().cancelHint(g);
        g.levelUp();
    }
    else if (cmd == "leveldown" || cmd.substr(0, 6) == "leveld" || cmd == "ld") {
        g.currBlock().cancelHint(g);
        g.levelDown();
    }
    else if (cmd == "norandom" || cmd.substr(0, 1) == "n") {
        g.currBlock().cancelHint(g);
        string seq;
        cin >> seq;
        int curlev = g.getLevel();
        if (curlev >= 3) {
            g.getLevels()[curlev]->setRandom(false);
            g.getLevels()[curlev]->setSeq(seq);
            g.setNoRand(true);
        }
    }
    else if (cmd == "random" || cmd.substr(0, 2) == "ra") {
        g.currBlock().cancelHint(g);
        srand(time(NULL));
        int curlev = g.getLevel();
        if (curlev >= 3) {
            g.setNoRand(false);
            g.getLevels()[curlev]->setRandom(true);
            g.getLevels()[curlev]->setSeed(time(NULL));
        }
    }
    else if (cmd == "I"||cmd == "J"||cmd == "L"||cmd == "S"||cmd == "Z"||cmd == "T"||cmd == "O") {
        g.currBlock().cancelHint(g);
        g.changeCurr(cmd);
    }
    else if (cmd == "hint" || cmd.substr(0, 1) == "h") {
        g.currBlock().cancelHint(g);
        g.currBlock().giveHint(g);
    }
}

void game(Grid &g, string cmd) {
    istringstream iss{cmd};
    int num;
    if (iss >> num) {
        iss >> cmd;
        if (!(cmd == "hint" || cmd == "norandom" || cmd == "random")) {
            for (int i = 0; i < num; ++i) {
                Game(g, cmd);
            }
        }
    } else {
        Game(g, cmd);
    }
    cout << g << endl;
}

int main(int argc, char *argv[]) {
    cin.exceptions(ios::eofbit|ios::failbit);
    bool textMode = false;
    int startLevel = 0;
    long seedNum = time(0);
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
    g.setCurrL(startLevel);

    srand(time(NULL));

    if (textMode) g.setGraphics(false); // init a grid w/ graphics disabled

    for (auto &l : g.getLevels()) {
        if (setseed) {
            srand(seedNum);
            l->setSeed(seedNum);
            l->setIsSeed(true);
        } else {
            srand(time(NULL));
            l->setSeed(time(NULL));
            l->setIsSeed(false);
        }
    }

    if (seqFile != "") {
        g.getLevels()[0]->setSeq(seqFile);
    }

    g.init();
    cout << g << endl;
    
    try {
        while (true) {
            cin >> cmd;
            if (cmd != "sequence" && cmd != "restart" && 
                cmd.substr(0, 2) != "se" && cmd.substr(0, 2) != "re") 
                game(g, cmd);
            else if (cmd == "sequence" || cmd.substr(0, 2) == "se") {
                string cmdSeq;
                cin >> cmdSeq;
                ifstream f{cmdSeq};
                while (f >> cmd) {
                    game(g, cmd);
                }
            }
            else if (cmd == "restart" || cmd.substr(0, 2) == "re") {
                g.init();
                cout << g << endl;
            }
        }
    }
    catch (ios::failure &) {}  // Any I/O failure quits
}
