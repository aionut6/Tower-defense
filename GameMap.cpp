#include "GameMap.h"
#include <iostream>
#include <algorithm>

GameMap::GameMap(int width, int height, int startLives, int startMoney)
    : width(width), height(height), playerLives(startLives), playerMoney(startMoney) {
    //towers si enemies sunt automat goi
    std::cout << "Harta jocului a fost creata." << std::endl;
}

//regula celor 3
GameMap::~GameMap() {
    std::cout << "Harta jocului a fost distrusa." << std::endl;
}

//constructor de copiere
GameMap::GameMap(const GameMap& other)
    : width(other.width), height(other.height),
      playerLives(other.playerLives), playerMoney(other.playerMoney),
      towers(other.towers), enemies(other.enemies) {

    std::cout << "Harta jocului a fost COPIATA (Copy Constructor)." << std::endl;
}

GameMap& GameMap::operator=(const GameMap& other) {
    std::cout << "Harta jocului a fost ATRIBUITA (Copy Assignment)." << std::endl;

    if (this == &other) {
        return *this;
    }

    width = other.width;
    height = other.height;
    playerLives = other.playerLives;
    playerMoney = other.playerMoney;

    towers = other.towers;
    enemies = other.enemies;

    return *this;
}

//construirea unui turn
bool GameMap::buildTower(const Tower& newTower) {
    //verifica daca jucatorul are suficienti bani
    if (playerMoney >= newTower.getCost()) {
        //verifica daca se afla alt turn pe acea pozitie
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
            //scade banii si adauga turnul
            playerMoney -= newTower.getCost();
            towers.push_back(newTower); //adaugă o copie a turnului în vector
            std::cout << "Turn " << newTower.getType() << " construit! Bani ramasi: " << playerMoney << std::endl;
            return true;
        }
    } else {
        std::cout << "EROARE: Fonduri insuficiente pentru " << newTower.getType() << std::endl;
    }

    return false; //construirea a eșuat
}

//adaugarea unui inamic
void GameMap::spawnEnemy(const Enemy& newEnemy) {
    enemies.push_back(newEnemy); // Adaugă o copie a inamicului
    std::cout << "Un " << newEnemy.getType() << " a intrat pe harta!" << std::endl;
}

void GameMap::updateGame() {
    std::cout << "\n--- ACTUALIZARE RUNDA ---" << std::endl;

    //turnurile atacă inamicii
    for (const Tower& tower : towers) {
        //fiecare turn iterează prin toți inamicii
        for (Enemy& enemy : enemies) {
            tower.attack(enemy);
        }
    }

    // TODO muta inamicii
    // for (Enemy& enemy : enemies) { enemy.move(); }

    //curata inamicii morti
    auto it = std::ranges::remove_if(enemies,
                                     [](const Enemy& e) {
                                         //returneaza true daca inamicul a fost eliminat
                                         return e.getHealth() <= 0;
                                     }).begin();

    //verificam daca am mai gasit inamici morti
    if (it != enemies.end()) {
        std::cout << "Eliminam inamicii morti..." << std::endl;
        enemies.erase(it, enemies.end());
    }
}

std::ostream& operator<<(std::ostream& os, const GameMap& map) {
    os << "====== STARE HARTA ======\n";
    os << "Dimensiuni: " << map.width << "x" << map.height << "\n";
    os << "Viata Bazei: " << map.playerLives << "\n";
    os << "Bani: " << map.playerMoney << "\n";


    os << "\n--- Turnuri (" << map.towers.size() << ") ---\n";
    if (map.towers.empty()) {
        os << "Niciun turn construit.\n";
    } else {
        for (const Tower& t : map.towers) {
            os << t << "\n";
        }
    }

    os << "\n--- Inamici (" << map.enemies.size() << ") ---\n";
    if (map.enemies.empty()) {
        os << "Niciun inamic pe harta.\n";
    } else {
        for (const Enemy& e : map.enemies) {
            os << e << "\n";
        }
    }
    os << "===========================\n";
    return os;
}