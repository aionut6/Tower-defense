#pragma once
#include <iostream>
#include <string>
#include "Position.h"

class Enemy { //class Curse
private:
    std::string type; //"Grade 3", "Special Grade"
    int health;
    int speed;
    Position currentPosition;

public:
    Enemy(std::string type, int health, int speed, const Position& startPos);

    //getteri
    [[nodiscard]] const std::string& getType() const;
    [[nodiscard]] int getHealth() const;
    [[nodiscard]] int getSpeed() const;
    [[nodiscard]] Position getPosition() const;

    //actiuni
    void takeDamage(int damageAmount);
    void move();

    //functiue pt slow/freeze
    void setSpeed(int newSpeed);

    friend std::ostream& operator<<(std::ostream& os, const Enemy& enemy);
};