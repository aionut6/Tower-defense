#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Position.h"

class Enemy { //class Curse
private:
    std::string type;
    int health;
    Position currentPosition;

    std::vector<Position> path; // Calea prestabilita
    int pathIndex; // Pozitia curenta pe cale
    int moveCooldown; // Cate "tick-uri" asteapta inainte de a se misca
    int moveTimer; // Contor pana la urmatoarea miscare

public:
    // Constructor actualizat
    Enemy(std::string type, int health, int moveCooldown, const std::vector<Position>& path);

    // Getteri
    [[nodiscard]] const std::string& getType() const;
    [[nodiscard]] int getHealth() const;
    [[nodiscard]] Position getPosition() const;

    // Actiuni
    void takeDamage(int damageAmount);

    // Functie noua de update, apelata de GameMap in fiecare runda
    void updateMovement();

    // Functie noua care verifica daca a ajuns la final
    [[nodiscard]] bool hasFinishedPath() const;

    friend std::ostream& operator<<(std::ostream& os, const Enemy& enemy);
};