#include "Player.h"
#include <utility>

Player::Player(std::string name, int startLives, int startMoney)
    : playerName(std::move(name)),
      lives(startLives),
      money(startMoney),
      experience(0),
      level(1),
      nextLevelExp(100) // Exp necesara pt nivelul 2
{}

const std::string& Player::getName() const {
    return playerName;
}

int Player::getLives() const {
    return lives;
}

int Player::getMoney() const {
    return money;
}

int Player::getLevel() const {
    return level;
}

int Player::getExperience() const {
    return experience;
}

void Player::loseLife() {
    if (lives > 0) {
        lives--;
    }
}

bool Player::spendMoney(int amount) {
    if (amount > 0 && money >= amount) {
        money -= amount;
        return true;
    }
    return false;
}

void Player::gainMoney(int amount) {
    if (amount > 0) {
        money += amount;
    }
}

void Player::gainExperience(int amount) {
    if (amount > 0 && lives > 0) { // Nu castigi exp daca ai pierdut
        experience += amount;
        std::cout << playerName << " a castigat " << amount << " XP! Total: " << experience << std::endl;
        levelUpCheck();
    }
}

// Functie privata
void Player::levelUpCheck() {
    while (experience >= nextLevelExp) {
        level++;
        experience -= nextLevelExp;
        nextLevelExp = static_cast<int>(nextLevelExp * 1.5); // Creste exponential
        std::cout << "LEVEL UP! " << playerName << " este acum nivelul " << level << "! Exp pana la urmatorul nivel: " << nextLevelExp << std::endl;
        // Aici s-ar putea adauga bonusuri la level up
    }
}

void Player::useAbility(const std::string& abilityName) const {
    if (lives > 0) {
        std::cout << playerName << " foloseste abilitatea: " << abilityName << "!" << std::endl;
    } else {
        std::cout << playerName << " nu poate folosi abilitati." << std::endl;
    }
}

std::ostream& operator<<(std::ostream& os, const Player& player) {
    os << "Player [" << player.playerName << " | Lvl: " << player.level
       << " | Exp: " << player.experience << "/" << player.nextLevelExp
       << " | Vieti: " << player.lives << " | Bani: " << player.money << "]";
    return os;
}