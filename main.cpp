#include <iostream>
#include "Position.h"
#include "Enemy.h"    // Blestem
#include "Tower.h"    // Vrajitor
#include "GameMap.h"  // Harta

int main() {
    //crearea mapei (cu dimensiuni mici, de grila)
    GameMap map(60, 15, 20, 1000); // 60 latime, 15 inaltime

    // Plasam vrajitorii (pozitiile sunt acum in grila 60x15)
    map.buildTower(Tower("Vrajitor Grad 2", 30, 10, 100, Position(5, 7))); // (x=5, y=7)
    map.buildTower(Tower("Vrajitor Grad 1", 80, 5, 250, Position(5, 9)));  // (x=5, y=9)

    // Incercam sa plasam unul peste altul (trebuie sa esueze)
    map.buildTower(Tower("Vrajitor Dublura", 10, 10, 10, Position(5, 7)));

    // Apar blestemele la marginea din stanga (x=0)
    map.spawnEnemy(Enemy("Blestem Grad 3", 100, 1, Position(0, 7))); // Pe randul 7
    map.spawnEnemy(Enemy("Blestem Grad 2", 300, 2, Position(0, 12)));// Pe randul 12

    std::cout << map; // Afiseaza grila initiala

    // Simulam 3 runde
    map.updateGame();
    std::cout << map;

    map.updateGame();
    std::cout << map;

    //regula celor 3 (ramane la fel)
    std::cout << "\n\n--- TESTARE REGULA CELOR 3 ---" << std::endl;
    //constructor de copiere
    std::cout << "--- Se apeleaza Constructorul de Copiere ---" << std::endl;
    GameMap mapCopiata = map;
    mapCopiata.spawnEnemy(Enemy("Mahito (Special)", 500, 1, Position(0,1))); //adauga un blestem doar pe copie

    std::cout << "\n--- Harta Originala ---" << std::endl;
    std::cout << map;
    std::cout << "\n--- Harta Copiata ---" << std::endl;
    std::cout << mapCopiata; // Va afisa grila copiata, cu Mahito pe ea

    // ... (restul testului Regula celor 3 ramane la fel) ...
    std::cout << "\n--- Se apeleaza Operatorul de Atribuire ---" << std::endl;
    GameMap mapAtribuita(1,1,1,1);
    mapAtribuita = map;
    std::cout << "\n--- Harta Atribuita (arata ca originala) ---" << std::endl;
    std::cout << mapAtribuita;

    std::cout << "\n--- Sfarsit main() ---" << std::endl;
    return 0;
}