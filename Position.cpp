#include "Position.h"

//implementarea constructorului
Position::Position(int x, int y) : x(x), y(y) {

}

//getter pentru x
int Position::getX() const {
    return x;
}

//getter pentru y
int Position::getY() const {
    return y;
}

std::ostream& operator<<(std::ostream& os, const Position& pos) {
    os << "(" << pos.x << ", " << pos.y << ")";
    return os;
}