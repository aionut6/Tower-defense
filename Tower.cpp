#include "Tower.h"
#include <utility>
#include <cmath>
#include <iostream>

Tower::Tower(std::string type, int damage, int range, int cost, const Position& pos, int attackCooldown)
    : type(std::move(type)),
      damage(damage),
      range(range),
      cost(cost),
      placement(pos),
      attackCooldown(attackCooldown),
      attackTimer(0) // Porneste gata de atac
{
}

// Getteri
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
    int deltaX = enemy.getPosition().getX() - placement.getX();
    int deltaY = enemy.getPosition().getY() - placement.getY();
    double distance = std::sqrt(std::pow(deltaX, 2) + std::pow(deltaY, 2));
    return distance <= range;
}

// Logica de atac apelata in fiecare runda
void Tower::updateAttack(std::vector<Enemy>& enemies) {
    attackTimer--;
    if (attackTimer > 0) {
        return; // Inca in cooldown
    }

    // Cooldown-ul a trecut, cautam o tinta
    // Acum alegem prima tinta in viata si in raza
    Enemy* target = nullptr;
    for (Enemy& enemy : enemies) {
        if (enemy.getHealth() > 0 && isEnemyInRange(enemy)) {
            target = &enemy;
            break; // Am gasit o tinta
        }
    }

    // Daca am gasit o tinta, atacam
    if (target != nullptr) {
        std::cout << "Vrajitorul " << type << " ataca " << target->getType()
                  << " pentru " << damage << " viata!" << std::endl;
        target->takeDamage(damage);
        attackTimer = attackCooldown; // Reseteaza cooldown-ul
    }
}


std::ostream& operator<<(std::ostream& os, const Tower& tower) {
    os << "Vrajitor [Tip: " << tower.type
       << ", Dmg: " << tower.damage
       << ", Raza: " << tower.range
       << ", Cost: " << tower.cost
       << ", AtkSpd: " << tower.attackCooldown
       << ", Poz: " << tower.placement << "]";
    return os;
}