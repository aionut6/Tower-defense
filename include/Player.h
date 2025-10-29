#pragma once
#include <iostream>
#include <string> // Pentru nume

class Player {
private:
    std::string playerName;
    int lives;
    int money;
    int experience;
    int level;
    int nextLevelExp;

    // Functie privata ajutatoare
    void levelUpCheck();

public:
    explicit Player(std::string name, int startLives, int startMoney);

    // Getteri
    [[nodiscard]] const std::string& getName() const;
    [[nodiscard]] int getLives() const;
    [[nodiscard]] int getMoney() const;
    [[nodiscard]] int getLevel() const;
    [[nodiscard]] int getExperience() const;

    void loseLife();
    bool spendMoney(int amount);
    void gainMoney(int amount);
    void gainExperience(int amount); // Functie noua

    // O abilitate simpla (doar afiseaza)
    void useAbility(const std::string& abilityName) const;

    friend std::ostream& operator<<(std::ostream& os, const Player& player);
};