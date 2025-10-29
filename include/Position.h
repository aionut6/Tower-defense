#pragma once
#include <iostream>

class Position {
private:
    int x;
    int y;

public:

    explicit Position(int x = 0, int y = 0);
    //getteri pt x si y
    [[nodiscard]]int getX() const;
    [[nodiscard]]int getY() const;

//implementarea <<
    friend std::ostream& operator<<(std::ostream& os, const Position& pos);
};