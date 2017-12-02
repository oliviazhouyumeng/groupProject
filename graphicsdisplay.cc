#include <iostream>
#include <string>
#include "graphicsdisplay.h"
#include "info.h"
#include "subject.h"
#include "grid.h"
#include "window.h"
#include "cell.h"
using namespace std;

GraphicsDisplay::GraphicsDisplay(int gridWidth, int gridHeight, int winWidth, int winHeight):
 gridWidth{gridWidth}, gridHeight{gridHeight}, winWidth{winWidth}, winHeight{winHeight}, xw{winWidth, winHeight} {
  xw.fillRectangle(0, 0, winWidth - gridWidth, winHeight, Xwindow::Brown);
  xw.fillRectangle(216, 0, gridWidth, winHeight, Xwindow::White);
  xw.drawString(30, 50, "Level:", Xwindow::Cyan);
  xw.drawString(30, 80, "Score:", Xwindow::Cyan);
  xw.drawString(30, 110, "Hi Score:", Xwindow::Cyan);
  xw.drawBigString(20, 165, "------------", Xwindow::Black);
  xw.drawString(30, 205, "Next:", Xwindow::Cyan);
  xw.drawString(140, 50, "0", Xwindow::Cyan);
  xw.drawString(140, 80, "0", Xwindow::Cyan);
  xw.drawString(125, 110, "100", Xwindow::Cyan);
}

void GraphicsDisplay::ScoreBoard(Grid &g) {
  int curscore = g.getScore();
  int hiscore = g.getHiScore();
  int curLevel = g.getLevel();
  string cs = to_string(curscore);
  string hs = to_string(hiscore);
  string cl = to_string(curLevel);

  xw.drawString(140, 50, cl, Xwindow::Cyan);
  xw.drawString(140, 80, cs, Xwindow::Cyan);
  xw.drawString(125, 110, hs, Xwindow::Cyan);
}

void GraphicsDisplay::NextBlock(Grid &g) {
  string nt = g.getNextType();
  int colNum = 11;
  int initC = 30;
  int initR = 230;
  int cellSize = gridWidth / colNum;
  if (nt == "I") {
    xw.fillRectangle(initC, initR, cellSize, cellSize, Xwindow::Red);
    xw.fillRectangle(initC + cellSize, initR, cellSize, cellSize, Xwindow::Red);
    xw.fillRectangle(initC + (2 * cellSize), initR, cellSize, cellSize, Xwindow::Red);
    xw.fillRectangle(initC + (3 * cellSize), initR, cellSize, cellSize, Xwindow::Red);
  }
  else if (nt == "J") {
    xw.fillRectangle(initC, initR, cellSize, cellSize, Xwindow::Green);
    xw.fillRectangle(initC, initR + cellSize, cellSize, cellSize, Xwindow::Green);
    xw.fillRectangle(initC + cellSize, initR + cellSize, cellSize, cellSize, Xwindow::Green);
    xw.fillRectangle(initC + (2 * cellSize), initR + cellSize, cellSize, cellSize, Xwindow::Green);
  }
  else if (nt == "L") {
    xw.fillRectangle(initC + (2 * cellSize), initR, cellSize, cellSize, Xwindow::Blue);
    xw.fillRectangle(initC, initR + cellSize, cellSize, cellSize, Xwindow::Blue);
    xw.fillRectangle(initC + cellSize, initR + cellSize, cellSize, cellSize, Xwindow::Blue);
    xw.fillRectangle(initC + (2 * cellSize), initR + cellSize, cellSize, cellSize, Xwindow::Blue);
  }
  else if (nt == "O") {
    xw.fillRectangle(initC + cellSize, initR, cellSize, cellSize, Xwindow::Cyan);
    xw.fillRectangle(initC + cellSize, initR + cellSize, cellSize, cellSize, Xwindow::Cyan);
    xw.fillRectangle(initC + (2 * cellSize), initR + cellSize, cellSize, cellSize, Xwindow::Cyan);
    xw.fillRectangle(initC + (2 * cellSize), initR, cellSize, cellSize, Xwindow::Cyan);
  }
  else if (nt == "S") {
    xw.fillRectangle(initC + cellSize, initR, cellSize, cellSize, Xwindow::Yellow);
    xw.fillRectangle(initC, initR + cellSize, cellSize, cellSize, Xwindow::Yellow);
    xw.fillRectangle(initC + (2 * cellSize), initR, cellSize, cellSize, Xwindow::Yellow);
    xw.fillRectangle(initC + cellSize, initR + cellSize, cellSize, cellSize, Xwindow::Yellow);
  }
  else if (nt == "T") {
    xw.fillRectangle(initC, initR, cellSize, cellSize, Xwindow::Orange);
    xw.fillRectangle(initC + cellSize, initR, cellSize, cellSize, Xwindow::Orange);
    xw.fillRectangle(initC + (2 * cellSize), initR, cellSize, cellSize, Xwindow::Orange);
    xw.fillRectangle(initC + cellSize, initR + cellSize, cellSize, cellSize, Xwindow::Orange);
  }
  else if (nt == "Z") {
    xw.fillRectangle(initC, initR, cellSize, cellSize, Xwindow::Magenta);
    xw.fillRectangle(initC + cellSize, initR, cellSize, cellSize, Xwindow::Magenta);
    xw.fillRectangle(initC + cellSize, initR + cellSize, cellSize, cellSize, Xwindow::Magenta);
    xw.fillRectangle(initC + (2 * cellSize), initR + cellSize, cellSize, cellSize, Xwindow::Magenta);
  }
}

void GraphicsDisplay::notify(Subject<Info, State> &whoNotified, Grid &g) {
  xw.fillRectangle(0, 0, winWidth - gridWidth, winHeight, Xwindow::Brown);
  xw.drawString(30, 50, "Level:", Xwindow::Cyan);
  xw.drawString(30, 80, "Score:", Xwindow::Cyan);
  xw.drawString(30, 110, "Hi Score:", Xwindow::Cyan);
  xw.drawBigString(20, 165, "------------", Xwindow::Black);
  xw.drawString(30, 205, "Next:", Xwindow::Cyan);
  ScoreBoard(g);
  NextBlock(g);

  auto info = whoNotified.getInfo();
  int start = 216;
  int colNum = 11;
  int cellSize = gridWidth / colNum; 
  switch(info.colour) {
   case Colour::Black:
    xw.fillRectangle(start + info.col * cellSize, info.row * cellSize, cellSize, cellSize, Xwindow::Black);
    break;
   case Colour::Cyan:
    xw.fillRectangle(start + info.col * cellSize, info.row * cellSize, cellSize, cellSize, Xwindow::Cyan);
    break;
   case Colour::Brown:
    xw.fillRectangle(start + info.col * cellSize, info.row * cellSize, cellSize, cellSize, Xwindow::Brown);
    break;
   case Colour::Red:
    xw.fillRectangle(start + info.col * cellSize, info.row * cellSize, cellSize, cellSize, Xwindow::Red);
    break;
   case Colour::Green:
    xw.fillRectangle(start + info.col * cellSize, info.row * cellSize, cellSize, cellSize, Xwindow::Green);
    break; 
   case Colour::Blue:
    xw.fillRectangle(start + info.col * cellSize, info.row * cellSize, cellSize, cellSize, Xwindow::Blue);
    break;
   case Colour::Yellow:
    xw.fillRectangle(start + info.col * cellSize, info.row * cellSize, cellSize, cellSize, Xwindow::Yellow);
    break;
   case Colour::Magenta:
    xw.fillRectangle(start + info.col * cellSize, info.row * cellSize, cellSize, cellSize, Xwindow::Magenta);
    break;
   case Colour::Orange:
    xw.fillRectangle(start + info.col * cellSize, info.row * cellSize, cellSize, cellSize, Xwindow::Orange);
    break;
   case Colour::White:
    xw.fillRectangle(start + info.col * cellSize, info.row * cellSize, cellSize, cellSize, Xwindow::White);
    break;
  }
}
