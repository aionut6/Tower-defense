#include "GameMap.h"
#include <iostream>
#include <algorithm>
#include <vector>

GameMap::GameMap(int width, int height, int startLives, int startMoney)
    : width(width),
      height(height),
      playerLives(startLives),
      playerMoney(startMoney)
{
    grid.resize(height, std::vector<char>(width, '.'));

    // Definim calea (de ex: un 'S' pe randul 5)
    for (int x = 0; x < width; ++x) {
        enemyPath.emplace_back(x, 5); // Cale dreapta pe randul 5
        if(height > 5) grid[5][x] = '#'; // Linia corecta
    }

    std::cout << "Harta (grila) " << width << "x" << height << " a fost creata." << std::endl;
}

GameMap::~GameMap() {
    std::cout << "Harta jocului a fost distrusa." << std::endl;
}

GameMap::GameMap(const GameMap& other)
    : width(other.width),
      height(other.height),
      playerLives(other.playerLives),
      playerMoney(other.playerMoney),
      towers(other.towers),
      enemies(other.enemies),
      grid(other.grid),
      enemyPath(other.enemyPath) // Copiem si calea
{
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
    grid = other.grid;
    enemyPath = other.enemyPath; // Copiem si calea
    return *this;
}

bool GameMap::buildTower(const Tower& newTower) {
    if (playerMoney < newTower.getCost()) {
        std::cout << "EROARE: Fonduri insuficiente!" << std::endl;
        return false;
    }

    int x = newTower.getPosition().getX();
    int y = newTower.getPosition().getY();

    if (y >= 0 && y < height && x >= 0 && x < width && grid[y][x] == '.') {
        playerMoney -= newTower.getCost();
        towers.push_back(newTower);
        grid[y][x] = 'T';
        std::cout << "Vrajitor " << newTower.getType() << " plasat! Bani ramasi: " << playerMoney << std::endl;
        return true;
    }

    std::cout << "EROARE: Pozitie invalida sau ocupata!" << std::endl;
    return false;
}

// Functia spawn actualizata
void GameMap::spawnEnemy(std::string type, int health, int moveCooldown) {
    // Cream un inamic nou si ii dam calea hartii
    enemies.emplace_back(std::move(type), health, moveCooldown, enemyPath);
    std::cout << "Un blestem " << enemies.back().getType() << " a aparut pe harta!" << std::endl;
}

// Functia de update (tick)
void GameMap::updateGame() {
    std::cout << "\n--- ACTUALIZARE RUNDA ---" << std::endl;

    // 1. Vrajitorii isi actualizeaza atacurile
    for (Tower& tower : towers) {
        tower.updateAttack(enemies);
    }

    // 2. Blestemele isi actualizeaza miscarea
    for (Enemy& enemy : enemies) {
        enemy.updateMovement();

        // Verificam daca a ajuns la final
        if (enemy.getHealth() > 0 && enemy.hasFinishedPath()) {
            playerLives--;
            enemy.takeDamage(9999); // Omoram inamicul
            std::cout << "Un blestem a ajuns la baza! Vieti ramase: " << playerLives << std::endl;
        }
    }

    // 3. Curatam blestemele moarte
    auto it = std::ranges::remove_if(enemies,
                                     [](const Enemy& e) {
                                         return e.getHealth() <= 0;
                                     }).begin();

    if (it != enemies.end()) {
        std::cout << "Eliminam blestemele invinse..." << std::endl;
        enemies.erase(it, enemies.end());
    }
}

// Operatorul << (ramane la fel ca inainte)
std::ostream& operator<<(std::ostream& os, const GameMap& map) {
    std::vector<std::vector<char>> tempGrid = map.grid;

    for (const Enemy& e : map.enemies) {
        int x = e.getPosition().getX();
        int y = e.getPosition().getY();
        if (y >= 0 && y < map.height && x >= 0 && x < map.width) {
            if (e.getHealth() > 0) {
                 tempGrid[y][x] = 'B';
            }
        }
    }

    os << "====== STAREA HARTII ======\n";
    os << "Vieti: " << map.playerLives << " | Bani: " << map.playerMoney;
    os << " | Vrajitori: " << map.towers.size() << " | Blesteme: " << map.enemies.size() << "\n";

    for (int y = 0; y < map.height; ++y) {
        for (int x = 0; x < map.width; ++x) {
            os << tempGrid[y][x];
        }
        os << "\n";
    }
    os << "===========================\n";
    return os;
}