#pragma once
#include <iostream>
#include <string>
#include "Position.h"

class Enemy {
private:
    std::string type; // "Goblin", "Orc", etc.
    int health;
    int speed;
    Position currentPosition;

public:
    // Constructor cu parametri
    Enemy(std::string type, int health, int speed, const Position& startPos);

    // Getteri (pentru a putea citi starea din exterior)
    const std::string& getType() const; // Returnează prin referință constantă
    int getHealth() const;
    Position getPosition() const;

    void takeDamage(int damageAmount);
    void move();

    friend std::ostream& operator<<(std::ostream& os, const Enemy& enemy);
};