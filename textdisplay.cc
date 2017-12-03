#include "textdisplay.h"
#include "info.h"
#include "cell.h"
using namespace std;

TextDisplay::~TextDisplay(){
}

TextDisplay::TextDisplay(int width, int length): theDisplay(length, vector<char>(width, '-')), width{width}, length{length}{}

void TextDisplay::notify(Subject<Info, State> &whoNotified, Grid &g){
  Colour cl = whoNotified.getInfo().colour;
  size_t r = whoNotified.getInfo().row;
  size_t c = whoNotified.getInfo().col;
  if (cl == Colour::Brown) {
    theDisplay[r][c] = '*';
  } else if (cl == Colour::Black) {
    theDisplay[r][c] = '?';
  } else if (cl == Colour::Red) {
    theDisplay[r][c] = 'I';
  } else if (cl == Colour::Green) {
    theDisplay[r][c] = 'J';
  } else if (cl == Colour::Blue) {
    theDisplay[r][c] = 'L';
  } else if (cl == Colour::Cyan) {
    theDisplay[r][c] = 'O';
  } else if (cl == Colour::Yellow){
    theDisplay[r][c] = 'S';
  } else if (cl == Colour::Magenta){
    theDisplay[r][c] = 'Z';
  } else if (cl == Colour::Orange){
    theDisplay[r][c] = 'T';
  }
}

ostream &operator<<(std::ostream &out, const TextDisplay &td){
    for(int i = 0; i < td.length; i++){
        for(int j = 0; j < td.width; j++){
            out << td.theDisplay[i][j];
        }
        out << endl;
    }
    return out;
}
