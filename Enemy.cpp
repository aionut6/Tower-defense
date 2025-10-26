#include "Enemy.h"
#include <iostream>
#include <utility>

Enemy::Enemy(std::string type, int health, int speed, const Position& startPos)
    : type(std::move(type)), health(health), speed(speed), currentPosition(startPos) {
}

const std::string& Enemy::getType() const {
    return type;
}

int Enemy::getHealth() const {
    return health;
}

Position Enemy::getPosition() const {
    return currentPosition;
}

void Enemy::takeDamage(int damageAmount) {
    health -= damageAmount;
    if (health < 0) {
        health = 0;
    }
}

void Enemy::move() {
    std::cout << type << " se misca spre baza." << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Enemy& enemy) {
    os << "Inamic [Tip: " << enemy.type
       << ", Viata: " << enemy.health
       << ", Viteza: " << enemy.speed
       << ", Pozitie: " << enemy.currentPosition << "]";
    return os;
}