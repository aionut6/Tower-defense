#include "Tower.h"
#include <utility> // Pentru std::move
#include <cmath>   // Pentru sqrt (radical) și pow (putere)
#include <iostream> // Pentru std::cout în funcția attack

// --- Constructor ---
Tower::Tower(std::string type, int damage, int range, int cost, const Position& pos)
    : type(std::move(type)), damage(damage), range(range), cost(cost), placement(pos) {
    // Folosim lista de inițializare
}

// --- Getteri ---
std::string Tower::getType() const {
    return type;
}

int Tower::getCost() const {
    return cost;
}

Position Tower::getPosition() const {
    return placement;
}

// --- Funcție privată ajutătoare ---
bool Tower::isEnemyInRange(const Enemy& enemy) const {
    // Calculăm distanța Euclidiană dintre turn și inamic
    // distanta = sqrt( (x2 - x1)^2 + (y2 - y1)^2 )

    int deltaX = enemy.getPosition().getX() - placement.getX();
    int deltaY = enemy.getPosition().getY() - placement.getY();

    // Folosim pow(baza, exponent) pentru a ridica la pătrat
    double distance = std::sqrt(std::pow(deltaX, 2) + std::pow(deltaY, 2));

    // Returnăm true dacă distanța e mai mică sau egală cu raza turnului
    return distance <= range;
}

// --- Funcție publică (logică) ---
void Tower::attack(Enemy& enemy) const {
    // Verificăm mai întâi dacă inamicul este în raza de acțiune
    if (isEnemyInRange(enemy)) {
        // Dacă este, aplicăm damage-ul
        std::cout << "Turnul " << type << " ataca " << enemy.getType()
                  << " pentru " << damage << " viata!" << std::endl;
        enemy.takeDamage(damage);
    }
}

// --- Operatorul << ---
std::ostream& operator<<(std::ostream& os, const Tower& tower) {
    os << "Turn [Tip: " << tower.type
       << ", Damage: " << tower.damage
       << ", Raza: " << tower.range
       << ", Cost: " << tower.cost
       << ", Pozitie: " << tower.placement << "]"; // <-- APEL COMPUS
    return os;
}