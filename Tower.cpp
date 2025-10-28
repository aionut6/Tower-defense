#include "Tower.h"
#include <utility>
#include <cmath>
#include <iostream>

//constructor
Tower::Tower(std::string type, int damage, int range, int cost, const Position& pos)
    : type(std::move(type)), damage(damage), range(range), cost(cost), placement(pos) {
}

//getteri
const std::string& Tower::getType() const {
    return type;
}

int Tower::getCost() const {
    return cost;
}

Position Tower::getPosition() const {
    return placement;
}


bool Tower::isEnemyInRange(const Enemy& enemy) const {
    //distanta dintre inamic si turn = sqrt( (x2 - x1)^2 + (y2 - y1)^2 )

    int deltaX = enemy.getPosition().getX() - placement.getX();
    int deltaY = enemy.getPosition().getY() - placement.getY();


    double distance = std::sqrt(std::pow(deltaX, 2) + std::pow(deltaY, 2));

    //adevarat doar daca e in raza turnului
    return distance <= range;
}

void Tower::attack(Enemy& enemy) const {
    //daca inamicul e in raza isi ia damage
    if (isEnemyInRange(enemy)) {
        std::cout << "Turnul " << type << " ataca " << enemy.getType()
                  << " pentru " << damage << " viata!" << std::endl;
        enemy.takeDamage(damage);
    }
}

std::ostream& operator<<(std::ostream& os, const Tower& tower) {
    os << "Turn [Tip: " << tower.type
       << ", Damage: " << tower.damage
       << ", Raza: " << tower.range
       << ", Cost: " << tower.cost
       << ", Pozitie: " << tower.placement << "]"; // <-- APEL COMPUS
    return os;
}