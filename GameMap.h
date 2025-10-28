#pragma once

#include <iostream>
#include <vector>
#include "Tower.h"
#include "Enemy.h"

class GameMap {
private:
    int width;
    int height;
    int playerLives;
    int playerMoney;

    std::vector<Tower> towers;
    std::vector<Enemy> enemies;

    std::vector<std::vector<char>> grid;

public:
    GameMap(int width, int height, int startLives, int startMoney);

    //regula celor 3
    ~GameMap();
    GameMap(const GameMap& other);
    GameMap& operator=(const GameMap& other);

    //daca sunt bani si loc pe harta adauga turn
    bool buildTower(const Tower& newTower);

    //adauga inamic
    void spawnEnemy(const Enemy& newEnemy);

    //simularea unei runde
    void updateGame();

    friend std::ostream& operator<<(std::ostream& os, const GameMap& map);
};