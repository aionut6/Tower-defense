// GameMap.h
#pragma once
#include <iostream>
#include <vector>
#include <string> // Necesar pt numele playerului
#include "Tower.h"
#include "Enemy.h"
#include "Position.h"
#include "Player.h"

class GameMap {
private:
    int width;
    int height;
    std::vector<Tower> towers;
    std::vector<Enemy> enemies;
    std::vector<std::vector<char>> grid;
    std::vector<Position> enemyPath;
    Player player; // Contine un obiect Player

public:
    // Constructor actualizat
    GameMap(int width, int height, std::string playerName, int startLives, int startMoney);

    // Regula celor 3
    ~GameMap();
    GameMap(const GameMap& other);
    GameMap& operator=(const GameMap& other);

    bool buildTower(const Tower& newTower);
    void spawnEnemy(std::string type, int health, int moveCooldown);
    void updateGame();

    // Functie noua pentru a da XP la final de runda
    void rewardPlayerForRound();

    [[nodiscard]] const std::string& getPlayerName() const;
    [[nodiscard]] int getPlayerLevel() const;
    [[nodiscard]] int getPlayerExperience() const;
    void usePlayerAbility(const std::string& abilityName) const;

    friend std::ostream& operator<<(std::ostream& os, const GameMap& map);
};