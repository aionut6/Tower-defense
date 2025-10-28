#include "Position.h"

//implementarea constructorului
Position::Position(int x, int y) : x(x), y(y) {

}

//getteri pt x si y
int Position::getX() const {
    return x;
}

int Position::getY() const {
    return y;
}

//implementarea <<
std::ostream& operator<<(std::ostream& os, const Position& pos) {
    os << "(" << pos.x << ", " << pos.y << ")";
    return os;
}