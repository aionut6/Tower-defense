#include <iostream>
#include "Position.h"
#include "Enemy.h"    // Blestem
#include "Tower.h"    // Vrajitor
#include "GameMap.h"  // Harta

int main() {
    //crearea mapei
    GameMap map(800, 600, 20, 1000);

    Tower grade2Sorcerer("Vrajitor Grad 2", 30, 100, 100, Position(50, 50));
    map.buildTower(grade2Sorcerer);

    Tower grade1Sorcerer("Vrajitor Grad 1", 80, 70, 250, Position(100, 100));
    map.buildTower(grade1Sorcerer);

    map.buildTower(Tower("Gojo Satoru (Special)", 999, 999, 5000, Position(10, 10))); //energie insuficienta

    map.spawnEnemy(Enemy("Blestem Grad 3", 100, 5, Position(70, 70))); //in raza ambilor vrajitori
    map.spawnEnemy(Enemy("Blestem Grad 2", 300, 2, Position(500, 500))); //in afara razei

    std::cout << map;

    map.updateGame(); // Blestemul Grad 3 ar trebui sa ia damage (30 + 80 = 110) si e invins.
    std::cout << map; // Arata starea dupa atac. Blestemul e mort.

    map.updateGame(); // Runda 2. Blestemele moarte (Grad 3) ar trebui sa dispara.
    std::cout << map; // Arata starea dupa curatare. Doar Blestemul Grad 2 a ramas.

    //regula celor 3
    std::cout << "\n\n--- TESTARE REGULA CELOR 3 ---" << std::endl;
    //constructor de copiere
    std::cout << "--- Se apeleaza Constructorul de Copiere ---" << std::endl;
    GameMap mapCopiata = map;
    mapCopiata.spawnEnemy(Enemy("Mahito (Special)", 500, 1, Position(1,1))); //adauga un blestem doar pe copie

    std::cout << "\n--- Harta Originala (are 1 blestem) ---" << std::endl;
    std::cout << map;
    std::cout << "\n--- Harta Copiata (are 2 blesteme) ---" << std::endl;
    std::cout << mapCopiata;

    std::cout << "\n--- Se apeleaza Operatorul de Atribuire ---" << std::endl;
    GameMap mapAtribuita(1,1,1,1);
    mapAtribuita = map;

    std::cout << "\n--- Harta Atribuita (arata ca originala) ---" << std::endl;
    std::cout << mapAtribuita;

    std::cout << "\n--- Sfarsit main() ---" << std::endl;
    //Test Destructor, distruge toate 3 hartile
    return 0;
}