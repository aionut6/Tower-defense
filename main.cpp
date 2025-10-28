// main.cpp
#include <iostream>
#include "Position.h"
#include "Enemy.h"
#include "Tower.h"
#include "GameMap.h"
#include <string> // Necesare pentru numele playerului

int main() {
    // Crearea mapei cu nume player
    GameMap map(60, 15, "Yuji Itadori", 20, 1000);

    map.buildTower(Tower("Vrajitor Grad 2", 30, 10, 100, Position(10, 3), 10));
    map.buildTower(Tower("Vrajitor Grad 1", 80, 5, 250, Position(10, 7), 5));
    map.buildTower(Tower("Gojo Satoru (Test)", 999, 50, 500, Position(15, 5), 20)); // Eroare pozitie

    map.spawnEnemy("Blestem Grad 3", 100, 5);
    map.spawnEnemy("Blestem Grad 2", 300, 2);

    std::cout << map;

    // Simulam 30 de tick-uri
    for (int i = 1; i <= 30; ++i) {
        std::cout << "\n<<<<<<<<<< TICK " << i << " >>>>>>>>>>" << std::endl;
        map.updateGame();

        // Afisam starea doar la fiecare 5 tick-uri
        if (i % 5 == 0) {
            std::cout << map;
            // Testam abilitatea
            // map.player.useAbility("Pumnul Divergent"); // Eroare - player e privat
        }
    }

    // Adaugam reward la final (optional)
    map.rewardPlayerForRound();

    std::cout << "--- SIMULARE INCHEIATA ---" << std::endl;
    std::cout << map;

    // Testarea Regulii celor 3 (ramane la fel)
    std::cout << "\n\n--- TESTARE REGULA CELOR 3 ---" << std::endl;
    GameMap mapCopiata = map;
    std::cout << "\n--- Harta Originala ---" << std::endl;
    std::cout << map;
    std::cout << "\n--- Harta Copiata ---" << std::endl;
    std::cout << mapCopiata;

    std::cout << "\n--- Verificare Player (pentru Cppcheck) ---" << std::endl;
    std::cout << "Nume Player: " << map.getPlayerName() << std::endl;
    std::cout << "Nivel Player: " << map.getPlayerLevel() << std::endl;
    std::cout << "Experienta Player: " << map.getPlayerExperience() << std::endl;
    map.usePlayerAbility("Expansiunea Domeniului"); // Apelam abilitatea

    std::cout << "\n--- Sfarsit main() ---" << std::endl;
    return 0;
}