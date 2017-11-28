#ifndef state_h
#define state_h

enum class Direction {N, W, E, S};
enum class StateType {AC, NA}; // Active:default, can move&rotate, cells in the current block
                               // NotActive: change to notactive after drop, cannot move&rotate

struct State {
    Direction direction;
    StateType stype;
};

#endif
