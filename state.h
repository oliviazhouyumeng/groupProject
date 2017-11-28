#ifndef state_h
#define state_h

enum class Colour {White=0, Black, Red, Green, Blue, Cyan, Yellow, Magenta, Orange, Brown};
enum class Direction {N, W, E, S};
enum class StateType {};

struct State {
    Colour colour;
    Direction direction;
    StateType type;
};

#endif
