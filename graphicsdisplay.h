#ifndef GRAPHICSDISPLAY_H
#define GRAPHICSDISPLAY_H
#include <iostream>
#include <vector>
#include "observer.h"
#include "state.h"
#include "window.h"
#include "info.h"

class Cell;
class Grid;

class GraphicsDisplay: public Observer<Info, State> {
  const int gridWidth, gridHeight, winWidth, winHeight;
  Xwindow xw;
  void ScoreBoard(Grid &g);
  void NextBlock(Grid &g);

 public:
  GraphicsDisplay(int gridWidth = 396, int gridHeight = 648, int winWidth = 612, int winHeight = 648);
  void notify(Subject<Info, State> &whoNotified, Grid &g) override;
};
#endif