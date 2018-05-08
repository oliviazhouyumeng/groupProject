#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include <iostream>
#include <vector>
#include "observer.h"
#include "grid.h"
#include "state.h"
#include "info.h"
#include "subject.h"

class Cell;

class TextDisplay: public Observer {
	const int width = 11;
  const int length = 18;
  std::vector<std::vector<char>> theDisplay;

 public:
  ~TextDisplay();
    
  TextDisplay();
    
  void notify(Subject<Info, State> &whoNotified, Grid &g) override;
    
  friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};
#endif
