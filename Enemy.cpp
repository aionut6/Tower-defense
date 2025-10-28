#include "Enemy.h"
#include <iostream>
#include <utility>

Enemy::Enemy(std::string type, int health, int speed, const Position& startPos)
    : type(std::move(type)),
      health(health),
      speed(speed),
      currentPosition(startPos)
{

}

//getteri
const std::string& Enemy::getType() const {
    return type;
}

int Enemy::getHealth() const {
    return health;
}

int Enemy::getSpeed() const {
    return speed;
}

Position Enemy::getPosition() const {
    return currentPosition;
}

//actiuni
void Enemy::takeDamage(int damageAmount) {
    health -= damageAmount;
    if (health < 0) {
        health = 0; //preventie hp pe minus
    }
}

void Enemy::setSpeed(int newSpeed) {
    //masura de siguranta sa nu avem viteze negative
    if (newSpeed < 0) {
        speed = 0;
    } else {
        speed = newSpeed;
    }
}

//implementarea miscarii
void Enemy::move(){
    //inamicii se misca dreapta spre x, cream o poz noua bazata pe cea veche
    Position newPos(currentPosition.getX() + speed, currentPosition.getY());

    currentPosition = newPos;

    //vedem unde se deplaseaza
    std::cout << "Blestemul " << type << " inainteaza la " << currentPosition << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Enemy& enemy) {
    os << "Inamic [Tip: " << enemy.type
       << ", Viata: " << enemy.health
       << ", Viteza: " << enemy.speed
       << ", Pozitie: " << enemy.currentPosition << "]"; // <-- APEL COMPUS
    return os;
}