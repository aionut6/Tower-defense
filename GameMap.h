#pragma once

#include <iostream>
#include <vector>     //evidenta
#include "Tower.h"    //are turnuri
#include "Enemy.h"    //are inamici

class GameMap {
private:
    int width;
    int height;
    int playerLives;
    int playerMoney;

    std::vector<Tower> towers;
    std::vector<Enemy> enemies;

public:
    GameMap(int width, int height, int startLives, int startMoney);

    //regula celor 3

    //destructor
    ~GameMap();
    //constructor de copiere
    GameMap(const GameMap& other);
    //operator de atribuire (asignare) prin copiere
    GameMap& operator=(const GameMap& other);

    //daca sunt bani si loc pe harta adauga turn
    bool buildTower(const Tower& newTower);

    //adauga inamic
    void spawnEnemy(const Enemy& newEnemy);

    //simularea unei runde
    void updateGame();

    friend std::ostream& operator<<(std::ostream& os, const GameMap& map);
};