#ifndef GRAPHICSDISPLAY_H
#define GRAPHICSDISPLAY_H
#include <iostream>
#include <vector>
#include "observer.h"
#include "state.h"
#include "info.h"
#include "window.h"

class Cell;
class Grid;

class GraphicsDisplay: public Observer {
  int gridWidth = 396;
  int gridHeight = 648;
  int winWidth = 612;
  int winHeight = 648;
  Xwindow xw;
  void ScoreBoard(Grid &g);
  void NextBlock(Grid &g);
  void RedrawLeft(Grid &g);

 public:
  GraphicsDisplay();
  void notify(Subject<Info, State> &whoNotified, Grid &g) override;
};
#endif
