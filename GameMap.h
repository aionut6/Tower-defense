#pragma once

#include <iostream>
#include <vector>     // Vom folosi vectori pentru a ține evidența
#include <string>
#include "Tower.h"    // Harta ARE turnuri
#include "Enemy.h"    // Harta ARE inamici

class GameMap {
private:
    int width;
    int height;
    int playerLives;
    int playerMoney;

    // --- COMPUNEREA PRINCIPALĂ ---
    std::vector<Tower> towers;
    std::vector<Enemy> enemies;

public:
    // --- Constructor / Destructor ---
    GameMap(int width, int height, int startLives, int startMoney);

    // --- CERINȚA 3: REGULA CELOR 3 ---
    // 1. Destructor
    ~GameMap();
    // 2. Constructor de copiere
    GameMap(const GameMap& other);
    // 3. Operator de atribuire (asignare) prin copiere
    GameMap& operator=(const GameMap& other);

    // --- CERINȚA 6: Funcții Netriviale ---

    // Adaugă un turn pe hartă dacă sunt bani și e loc
    bool buildTower(const Tower& newTower);

    // Adaugă un inamic nou pe hartă
    void spawnEnemy(const Enemy& newEnemy);

    // Funcția principală care simulează o rundă de joc
    void updateGame();

    // --- CERINȚA 4: Operatorul << ---
    friend std::ostream& operator<<(std::ostream& os, const GameMap& map);
};