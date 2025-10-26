// GameMap.cpp

#include "GameMap.h"
#include <utility>      // Pentru std::move
#include <iostream>     // Pentru std::cout
#include <algorithm>    // Pentru std::remove_if (funcție complexă)

// --- Constructor / Destructor ---

GameMap::GameMap(int width, int height, int startLives, int startMoney)
    : width(width), height(height), playerLives(startLives), playerMoney(startMoney) {
    // Vectorii 'towers' și 'enemies' sunt inițializați automat ca fiind goi.
    std::cout << "Harta jocului a fost creata." << std::endl;
}

// --- CERINȚA 3: REGULA CELOR 3 ---

// 1. Destructor
GameMap::~GameMap() {
    // Deoarece folosim std::vector (care se curăță singur - RAII),
    // nu avem nevoie să ștergem manual 'towers' sau 'enemies'.
    // Destructorul este definit doar pentru a respecta cerința.
    std::cout << "Harta jocului a fost distrusa." << std::endl;
}

// 2. Constructor de copiere
GameMap::GameMap(const GameMap& other)
    : width(other.width), height(other.height),
      playerLives(other.playerLives), playerMoney(other.playerMoney),
      towers(other.towers), enemies(other.enemies) {
    // Când copiem un std::vector (ex: towers(other.towers)),
    // acesta face automat o "deep copy" (copie completă)
    // a tuturor elementelor din el.
    std::cout << "Harta jocului a fost COPIATA (Copy Constructor)." << std::endl;
}

// 3. Operator de atribuire (asignare) prin copiere
GameMap& GameMap::operator=(const GameMap& other) {
    std::cout << "Harta jocului a fost ATRIBUITA (Copy Assignment)." << std::endl;
    // 1. Verificăm auto-atribuirea (ex: map1 = map1)
    if (this == &other) {
        return *this; // Nu facem nimic și returnăm obiectul curent
    }

    // 2. Copiem membrii non-vectoriali
    width = other.width;
    height = other.height;
    playerLives = other.playerLives;
    playerMoney = other.playerMoney;

    // 3. Copiem vectorii (std::vector se descurcă singur cu copierea)
    towers = other.towers;
    enemies = other.enemies;

    // 4. Returnăm o referință la obiectul curent
    return *this;
}

// --- CERINȚA 6: Funcții Netriviale ---

// Funcția 1: Construirea unui turn
bool GameMap::buildTower(const Tower& newTower) {
    // Verifică dacă jucătorul are suficienți bani
    if (playerMoney >= newTower.getCost()) {
        // Verifică dacă locația e validă (nu e deja alt turn acolo)
        bool locationOk = true;
        for (const Tower& existingTower : towers) {
            if (existingTower.getPosition().getX() == newTower.getPosition().getX() &&
                existingTower.getPosition().getY() == newTower.getPosition().getY()) {
                locationOk = false;
                std::cout << "EROARE: Locatie deja ocupata de un turn!" << std::endl;
                break;
            }
        }

        if (locationOk) {
            // Scade banii și adaugă turnul
            playerMoney -= newTower.getCost();
            towers.push_back(newTower); // Adaugă o copie a turnului în vector
            std::cout << "Turn " << newTower.getType() << " construit! Bani ramasi: " << playerMoney << std::endl;
            return true;
        }
    } else {
        std::cout << "EROARE: Fonduri insuficiente pentru " << newTower.getType() << std::endl;
    }

    return false; // Construirea a eșuat
}

// Funcția 2: Adăugarea unui inamic
void GameMap::spawnEnemy(const Enemy& newEnemy) {
    enemies.push_back(newEnemy); // Adaugă o copie a inamicului
    std::cout << "Un " << newEnemy.getType() << " a intrat pe harta!" << std::endl;
}

// Funcția 3: Funcția principală a jocului (cea mai complexă)
void GameMap::updateGame() {
    std::cout << "\n--- ACTUALIZARE RUNDA ---" << std::endl;

    // 1. Turnurile atacă inamicii
    // Iterăm prin fiecare turn
    for (const Tower& tower : towers) {
        // Fiecare turn iterează prin toți inamicii
        // (Inamicul nu e 'const' pt. că funcția 'attack' îi va modifica viața)
        for (Enemy& enemy : enemies) {
            // Funcția 'attack' conține logica "isEnemyInRange"
            tower.attack(enemy);
        }
    }

    // 2. (Opțional, de adăugat ulterior) Mută inamicii
    // for (Enemy& enemy : enemies) { enemy.move(); }

    // 3. Curăță inamicii morți (health <= 0)
    // Folosim "erase-remove idiom" - o tehnică standard C++
    // std::remove_if mută toți inamicii "buni" la începutul vectorului
    // și returnează un iterator la primul inamic "rău" (mort)
    auto it = std::remove_if(enemies.begin(), enemies.end(),
        [](const Enemy& e) {
            // Aceasta este o funcție lambda. Returnează 'true' dacă inamicul trebuie șters.
            return e.getHealth() <= 0;
        });

    // Verificăm dacă am găsit inamici morți
    if (it != enemies.end()) {
        std::cout << "Eliminam inamicii morti..." << std::endl;
        // Ștergem toți inamicii de la iteratorul 'it' până la sfârșit
        enemies.erase(it, enemies.end());
    }
}

// --- CERINȚA 4: Operatorul << ---
std::ostream& operator<<(std::ostream& os, const GameMap& map) {
    os << "====== STARE HARTA ======\n";
    os << "Dimensiuni: " << map.width << "x" << map.height << "\n";
    os << "Viata Bazei: " << map.playerLives << "\n";
    os << "Bani: " << map.playerMoney << "\n";

    // Afișează turnurile (folosind operator<< din Tower)
    os << "\n--- Turnuri (" << map.towers.size() << ") ---\n";
    if (map.towers.empty()) {
        os << "Niciun turn construit.\n";
    } else {
        for (const Tower& t : map.towers) {
            os << t << "\n"; // Apel compus
        }
    }

    // Afișează inamicii (folosind operator<< din Enemy)
    os << "\n--- Inamici (" << map.enemies.size() << ") ---\n";
    if (map.enemies.empty()) {
        os << "Niciun inamic pe harta.\n";
    } else {
        for (const Enemy& e : map.enemies) {
            os << e << "\n"; // Apel compus
        }
    }
    os << "===========================\n";
    return os;
}