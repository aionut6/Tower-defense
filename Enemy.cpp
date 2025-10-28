#include "Enemy.h"
#include <iostream>

int Position::getX() const {
    return x;
}

int Position::getY() const {
    return y;
}

std::ostream& operator<<(std::ostream& os, const Position& pos) {

    os << "(" << pos.x << ", " << pos.y << ")";
    return os;
}

// --- Actiuni ---
void Enemy::takeDamage(int damageAmount) {
    health -= damageAmount;
    if (health < 0) {
        health = 0;
    }
}

void Enemy::setSpeed(int newSpeed) {
    if (newSpeed < 0) {
        speed = 0;
    } else {
        speed = newSpeed;
    }
}

void Enemy::setPosition(const Position& newPos) {
    currentPosition = newPos;
}

std::ostream& operator<<(std::ostream& os, const Enemy& enemy) {
    os << "Blestem [Tip: " << enemy.type
       << ", Viata: " << enemy.health
       << ", Viteza: " << enemy.speed
       << ", Poz: " << enemy.currentPosition << "]";
    return os;
}