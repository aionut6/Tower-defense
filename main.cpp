#include <iostream>
#include "Position.h"
#include "Enemy.h"
#include "Tower.h"
#include "GameMap.h"

int main() {
    // Harta de 60x15. Calea este pe randul 5
    GameMap map(60, 15, 20, 1000);

    // Plasam vrajitori cu viteze de atac diferite (cooldown in tick-uri)
    // Ataca la fiecare 10 tick-uri
    map.buildTower(Tower("Vrajitor Grad 2", 30, 10, 100, Position(10, 3), 10));
    // Ataca la fiecare 5 tick-uri (mai rapid)
    map.buildTower(Tower("Vrajitor Grad 1", 80, 5, 250, Position(10, 7), 5));
    // Ataca lent, dar e pus gresit (pe cale '#')
    map.buildTower(Tower("Gojo Satoru (Test)", 999, 50, 500, Position(15, 5), 20));


    // Apar blesteme cu viteze de miscare diferite
    // Se misca 1 pas la fiecare 5 tick-uri
    map.spawnEnemy("Blestem Grad 3", 100, 5);
    // Se misca 1 pas la fiecare 2 tick-uri (mai rapid)
    map.spawnEnemy("Blestem Grad 2", 300, 2);

    std::cout << map;

    // Simulam 30 de tick-uri (runde) de joc
    for (int i = 0; i < 30; ++i) {
        map.updateGame();

        if (i % 5 == 0) {
            std::cout << map;
        }
    }

    std::cout << "--- SIMULARE INCHEIATA ---" << std::endl;
    std::cout << map;

    // Testarea Regulii celor 3 (ramane la fel)
    std::cout << "\n\n--- TESTARE REGULA CELOR 3 ---" << std::endl;
    GameMap mapCopiata = map;
    std::cout << "\n--- Harta Originala ---" << std::endl;
    std::cout << map;
    std::cout << "\n--- Harta Copiata ---" << std::endl;
    std::cout << mapCopiata;

    std::cout << "\n--- Sfarsit main() ---" << std::endl;
    return 0;
}