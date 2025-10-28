#include "Enemy.h"
#include <utility>

Enemy::Enemy(std::string type, int health, int moveCooldown, const std::vector<Position>& path)
    : type(std::move(type)),
      health(health),
      currentPosition(path.empty() ? Position(0,0) : path[0]), // Porneste de la inceputul caii
      path(path),
      pathIndex(0),
      moveCooldown(moveCooldown),
      moveTimer(0) // Porneste gata de miscare
{
}

// Getteri
const std::string& Enemy::getType() const {
    return type;
}

int Enemy::getHealth() const {
    return health;
}

Position Enemy::getPosition() const {
    return currentPosition;
}

// Actiuni
void Enemy::takeDamage(int damageAmount) {
    health -= damageAmount;
    if (health < 0) {
        health = 0;
    }
}

// Logica de miscare apelata in fiecare runda
void Enemy::updateMovement() {
    // Daca e in viata si nu a ajuns la final
    if (getHealth() > 0 && !hasFinishedPath()) {
        moveTimer--;
        if (moveTimer <= 0) {
            // E timpul sa se miste
            pathIndex++;
            if (!hasFinishedPath()) {
                currentPosition = path[pathIndex];
            }
            moveTimer = moveCooldown; // Reseteaza contorul
        }
    }
}

bool Enemy::hasFinishedPath() const {
    // A terminat daca indexul e in afara limitelor caii
    return pathIndex >= static_cast<int>(path.size()) - 1;}

std::ostream& operator<<(std::ostream& os, const Enemy& enemy) {
    os << "Blestem [Tip: " << enemy.type
       << ", Viata: " << enemy.health
       << ", Poz: " << enemy.currentPosition << "]";
    return os;
}