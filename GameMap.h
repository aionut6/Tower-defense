#pragma once
#include <iostream>
#include <vector>
#include "Tower.h"
#include "Enemy.h"
#include "Position.h" // Necesar pentru cale

class GameMap {
private:
    int width;
    int height;
    int playerLives;
    int playerMoney;

    std::vector<Tower> towers;
    std::vector<Enemy> enemies;
    std::vector<std::vector<char>> grid;

    // Calea prestabilita pentru blesteme
    std::vector<Position> enemyPath;

public:
    GameMap(int width, int height, int startLives, int startMoney);

    // Regula celor 3
    ~GameMap();
    GameMap(const GameMap& other);
    GameMap& operator=(const GameMap& other);

    bool buildTower(const Tower& newTower);

    // Functie de spawn actualizata
    void spawnEnemy(std::string type, int health, int moveCooldown);

    void updateGame(); // Aceasta devine "tick-ul" principal

    friend std::ostream& operator<<(std::ostream& os, const GameMap& map);
};