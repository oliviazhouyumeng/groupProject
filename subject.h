#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include <memory>
#include "observer.h"
/* A note on InfoType and StateType:
 
 We have separated the collection of fields into two parts:  its Info
 and its State.
 
 Info is for the parts of the subjject inherent to what it is:  its position
 and its colour.
 
 State is for the parts of the subject that, when changed, trigger
 notifications.  This is the information that the Observer "gets" when it
 calls getState on the subject.  It comprises the type of state, a direction,
 and a colour.  For more details, see state.h.
 */

class Grid;


template <typename InfoType, typename StateType> class Subject {
    std::vector<std::shared_ptr<Observer>> observers;
    StateType state;
public:
    void attach(std::shared_ptr<Observer> o);
    void notifyObservers(Grid &g);
    virtual InfoType getInfo() const = 0;
    StateType getState() const;
    void setState(StateType newS);
};

template <typename InfoType, typename StateType>
void Subject<InfoType, StateType>::attach(std::shared_ptr<Observer> o) {
    observers.emplace_back(o);
}



template <typename InfoType, typename StateType>
void Subject<InfoType, StateType>::notifyObservers(Grid &g) {
    for (auto &ob : observers) ob->notify(*this, g);
}

template <typename InfoType, typename StateType>
void Subject<InfoType, StateType>::setState(StateType newS) { state = newS; }

template <typename InfoType, typename StateType>
StateType Subject<InfoType, StateType>::getState() const { return state; }
#endif
