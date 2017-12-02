#ifndef _OBSERVER_H_
#define _OBSERVER_H_
#include "info.h"

template <typename InfoType, typename StateType> class Subject;
class Cell;
class Grid;

class Observer {
public:
    virtual void notify(Subject<InfoType, StateType> &whoFrom, Grid &g) = 0; // pass the Subject that called the notify method
    virtual ~Observer() = default;
};
#endif
