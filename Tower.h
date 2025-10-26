// Tower.h

#pragma once
#include <iostream>
#include <string>
#include <cmath>
#include "Position.h"
#include "Enemy.h"

class Tower {
private:
    std::string type;
    int damage;
    int range;
    int cost;
    Position placement;

    // Funcție privată ajutătoare (cerința de funcții private)
    // Verifică dacă un inamic e în raza de acțiune
    bool isEnemyInRange(const Enemy& enemy) const;

public:
    // Constructor cu parametri
    Tower(std::string type, int damage, int range, int cost, const Position& pos);

    // Getteri
    std::string getType() const;
    int getCost() const;
    Position getPosition() const; // Util pentru clasa GameMap

    // Funcție de "logică" (cerința de funcție netrivială)
    // Încearcă să atace un inamic.
    void attack(Enemy& enemy) const;

    // Operatorul << pentru afișare
    friend std::ostream& operator<<(std::ostream& os, const Tower& tower);
};