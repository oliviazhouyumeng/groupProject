#include "textdisplay.h"
using namespace std;

TextDisplay::~TextDisplay(){
}

TextDisplay::TextDisplay(int width, int length): theDisplay(length, vector<char> (width, '-')), width{width}, length{length}{}

//enum class Colour {White=0, Black, Red, Green, Blue, Cyan, Yellow, Magenta, Orange, Brown};


void TextDisplay::notify(Subject<Info, State> &whoNotified){
    Colour cl = whoNotified.getInfo().colour;
    size_t r = whoNotified.getInfo().row;
    size_t c = whoNotified.getInfo().col;
    if(cl == Colour::Brown){
        theDisplay[r][c] = '*';
    }
    if(cl == Colour::Black){
        theDisplay[r][c] = '?';
    }
    if(cl == Colour::Red){
        theDisplay[r][c] = 'I';
    }
    if(cl == Colour::Green){
        theDisplay[r][c] = 'J';
    }
    if(cl == Colour::Blue){
        theDisplay[r][c] = 'L';
    }
    if(cl == Colour::Cyan){
        theDisplay[r][c] = 'O';
    }
    if(cl == Colour::Yellow){
        theDisplay[r][c] = 'S';
    }
    if(cl == Colour::Magenta){
        theDisplay[r][c] = 'Z';
    }
    if(cl == Colour::Orange){
        theDisplay[r][c] = 'T';
    }
}

ostream &operator<<(std::ostream &out, const TextDisplay &td){
    for(int i = 0; i < td.length; i++){
        for(int j = 0; j < td.width; j++){
            out << td.theDisplay[i][j];
            if(j == td.width-1){
                out << endl;
            }
        }
    }
    return out;
}
