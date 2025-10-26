#include <iostream>
#include "Position.h"
#include "Enemy.h"
#include "Tower.h"
#include "GameMap.h" // Include noua clasă

int main() {
    // --- 1. Crearea Hărții ---
    GameMap map(800, 600, 20, 1000);

    // --- 2. Testare 'buildTower' (Funcție Netrivială 1) ---
    Tower arrowTower("Arrow", 30, 100, 100, Position(50, 50));
    map.buildTower(arrowTower); // Ar trebui să reușească

    Tower cannonTower("Cannon", 80, 70, 250, Position(100, 100));
    map.buildTower(cannonTower); // Ar trebui să reușească

    map.buildTower(Tower("Sniper", 100, 500, 1000, Position(10, 10))); // Bani insuficienți

    // --- 3. Testare 'spawnEnemy' (Funcție Netrivială 2) ---
    map.spawnEnemy(Enemy("Goblin", 100, 5, Position(70, 70))); // În raza ambelor turnuri
    map.spawnEnemy(Enemy("Orc", 300, 2, Position(500, 500))); // În afara razei

    // --- 4. Testare 'operator<<' ---
    std::cout << map;

    // --- 5. Testare 'updateGame' (Funcție Netrivială 3) ---
    map.updateGame(); // Goblinul ar trebui să ia damage (30 + 80 = 110). Orc-ul nu.
    std::cout << map; // Arată starea după atac. Goblinul e mort.

    map.updateGame(); // Runda 2. Inamicii morți (Goblinul) ar trebui să dispară.
    std::cout << map; // Arată starea după curățare. Doar Orc-ul a rămas.

    // --- 6. Testare REGULA CELOR 3 ---
    std::cout << "\n\n--- TESTARE REGULA CELOR 3 ---" << std::endl;
    // 6.1 Test Constructor de Copiere
    std::cout << "--- Se apeleaza Constructorul de Copiere ---" << std::endl;
    GameMap mapCopiata = map;
    mapCopiata.spawnEnemy(Enemy("Troll", 500, 1, Position(1,1))); // Adaugă un inamic doar pe copie

    std::cout << "\n--- Harta Originala (doar 1 inamic) ---" << std::endl;
    std::cout << map;
    std::cout << "\n--- Harta Copiata (2 inamici) ---" << std::endl;
    std::cout << mapCopiata;

    // 6.2 Test Operator de Atribuire
    std::cout << "\n--- Se apeleaza Operatorul de Atribuire ---" << std::endl;
    GameMap mapAtribuita(1,1,1,1); // O hartă goală, temporară
    mapAtribuita = map; // mapAtribuita devine o copie a hărții 'map' originale

    std::cout << "\n--- Harta Atribuita (arata ca originala) ---" << std::endl;
    std::cout << mapAtribuita;

    std::cout << "\n--- Sfarsit main() ---" << std::endl;
    // 6.3 Test Destructor
    // Când 'main' se termină, toți 3 ('map', 'mapCopiata', 'mapAtribuita')
    // vor fi distruși, iar mesajele din destructor ar trebui să apară.
    return 0;
}