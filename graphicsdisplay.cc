#include <iostream>
#include "graphicsdisplay.h"
#include "info.h"
#include "subject.h"
using namespace std;

GraphicsDisplay::GraphicsDisplay(int gridWidth, int gridHeight, int winWidth, int winHeight):
 gridWidth{gridWidth}, gridHeight{gridHeight}, winWidth{winWidth}, winHeight{winHeight} {
  xw.fillRectangle(0, 0, winWidth, winHeight, Xwindow::Brown);
  xw.fillRectangle(216, 0, gridWidth, winHeight, Xwindow::White);
  xw.drawString(30, 50, "Level:", Xwindow::Cyan);
  xw.drawString(30, 80, "Score:", Xwindow::Cyan);
  xw.drawString(30, 110, "Hi Score:", Xwindow::Cyan);
  //...
}

// haven't changed
void GraphicsDisplay::notify(Subject<Info, State> &whoNotified) {
  auto info = whoNotified.getInfo();
  int cellSize = winWidth / gridWidth;
  switch(info.colour) {
   case Colour::Black:
    xw.fillRectangle(info.col * cellSize, info.row * cellSize, cellSize, cellSize, Xwindow::Black);
    break;
   case Colour::White:
    xw.fillRectangle(info.col * cellSize, info.row * cellSize, cellSize, cellSize, Xwindow::White);
    break;
   default:
    xw.fillRectangle(info.col * cellSize, info.row * cellSize, cellSize, cellSize, Xwindow::Blue);
  }
}
