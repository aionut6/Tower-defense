#pragma once
#include <iostream>
#include <string>
#include "Position.h"
#include "Enemy.h"

class Tower { //sorcerer
private:
    std::string type;//"Grade 3", "Special Grade" etc
    int damage;
    int range; //raza tehnicii
    int cost;
    Position placement;

    //verifica daca inamicul e in raza turnului
    [[nodiscard]] bool isEnemyInRange(const Enemy& enemy) const;

public:
    //constructor
    Tower(std::string type, int damage, int range, int cost, const Position& pos);

    //getteri
    [[nodiscard]] const std::string& getType() const;
    [[nodiscard]] int getCost() const;
    [[nodiscard]] Position getPosition() const;

    //ataca un inamic
    void attack(Enemy& enemy) const;

    friend std::ostream& operator<<(std::ostream& os, const Tower& tower);
};