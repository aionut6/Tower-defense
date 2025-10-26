#pragma once
#include <iostream>

class Position {
private:
    int x;
    int y;

public:

    Position(int x = 0, int y = 0);


    int getX() const;
    int getY() const;

    friend std::ostream& operator<<(std::ostream& os, const Position& pos);
};