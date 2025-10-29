#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Position.h"
#include "Enemy.h"

class Tower { //sorcerer
private:
    std::string type;
    int damage;
    int range;
    int cost;
    Position placement;

    int attackCooldown; // Cate "tick-uri" asteapta intre atacuri
    int attackTimer; // Contor pana la urmatorul atac

    [[nodiscard]] bool isEnemyInRange(const Enemy& enemy) const;

public:
    Tower(std::string type, int damage, int range, int cost, const Position& pos, int attackCooldown);

    [[nodiscard]] const std::string& getType() const;
    [[nodiscard]] int getCost() const;
    [[nodiscard]] Position getPosition() const;

    // Functie noua de update, apelata de GameMap
    // Primeste *toata* lista de inamici ca sa isi aleaga o tinta
    void updateAttack(std::vector<Enemy>& enemies);

    friend std::ostream& operator<<(std::ostream& os, const Tower& tower);
};