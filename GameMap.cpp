// GameMap.cpp
#include "GameMap.h"
#include <iostream>
#include <algorithm>
#include <vector>

// Constructor actualizat
GameMap::GameMap(int width, int height, std::string playerName, int startLives, int startMoney)
    : width(width),
      height(height),
      player(std::move(playerName), startLives, startMoney) // Initializeaza Player
{
    grid.resize(height, std::vector<char>(width, '.'));
    for (int x = 0; x < width; ++x) {
        if(height > 5) {
             enemyPath.emplace_back(x, 5);
             grid[5][x] = '#';
        }
    }
    std::cout << "Harta (grila) " << width << "x" << height << " a fost creata." << std::endl;
}

GameMap::~GameMap() {
    std::cout << "Harta jocului a fost distrusa." << std::endl;
}

// Constructor de Copiere actualizat
GameMap::GameMap(const GameMap& other)
    : width(other.width),
      height(other.height),
      towers(other.towers),
      enemies(other.enemies),
      grid(other.grid),
      enemyPath(other.enemyPath),
      player(other.player) // Copiaza Player
{
    std::cout << "Harta jocului a fost COPIATA (Copy Constructor)." << std::endl;
}

// Operator= actualizat
GameMap& GameMap::operator=(const GameMap& other) {
    std::cout << "Harta jocului a fost ATRIBUITA (Copy Assignment)." << std::endl;
    if (this == &other) { return *this; }
    width = other.width;
    height = other.height;
    towers = other.towers;
    enemies = other.enemies;
    grid = other.grid;
    enemyPath = other.enemyPath;
    player = other.player; // Copiaza Player
    return *this;
}

// buildTower actualizat
bool GameMap::buildTower(const Tower& newTower) {
    if (!player.spendMoney(newTower.getCost())) {
        std::cout << "EROARE: Fonduri insuficiente!" << std::endl;
        return false;
    }

    int x = newTower.getPosition().getX();
    int y = newTower.getPosition().getY();

    if (y >= 0 && y < height && x >= 0 && x < width && grid[y][x] == '.') {
        towers.push_back(newTower);
        grid[y][x] = 'T';
        std::cout << "Vrajitor " << newTower.getType() << " plasat! Bani ramasi: " << player.getMoney() << std::endl;
        return true;
    } else {
        player.gainMoney(newTower.getCost()); // Dam banii inapoi
        std::cout << "EROARE: Pozitie invalida sau ocupata!" << std::endl;
        return false;
    }
}

// spawnEnemy (ramane la fel)
void GameMap::spawnEnemy(std::string type, int health, int moveCooldown) {
    enemies.emplace_back(std::move(type), health, moveCooldown, enemyPath);
    std::cout << "Un blestem " << enemies.back().getType() << " a aparut pe harta!" << std::endl;
}

// Functie noua
void GameMap::rewardPlayerForRound() {
    // Exemplu: dam 10 XP pentru fiecare blestem ramas pe harta
    int xpReward = enemies.size() * 10;
    if (xpReward > 0) {
        player.gainExperience(xpReward);
    }
}


// updateGame actualizat
void GameMap::updateGame() {
    std::cout << "\n--- ACTUALIZARE RUNDA ---" << std::endl;

    for (Tower& tower : towers) {
        tower.updateAttack(enemies);
    }

    int enemiesDefeatedThisRound = 0; // Contor pt XP
    for (Enemy& enemy : enemies) {
        int healthBefore = enemy.getHealth(); // Verificam daca moare
        enemy.updateMovement();

        if (enemy.getHealth() > 0 && enemy.hasFinishedPath()) {
            player.loseLife();
            enemy.takeDamage(9999);
            std::cout << "Un blestem a ajuns la baza! Vieti ramase: " << player.getLives() << std::endl;
        }

        // Daca inamicul a murit in aceasta runda (din atac sau ajuns la baza)
        if(healthBefore > 0 && enemy.getHealth() <= 0) {
            enemiesDefeatedThisRound++;
        }
    }

    // Dam XP pentru blestemele invinse
    if(enemiesDefeatedThisRound > 0) {
        player.gainExperience(enemiesDefeatedThisRound * 25); // 25 XP per blestem
    }

    // Curatam blestemele moarte
    auto it = std::ranges::remove_if(enemies,
                                     [](const Enemy& e) { return e.getHealth() <= 0; }).begin();

    if (it != enemies.end()) {
        std::cout << "Eliminam blestemele invinse..." << std::endl;
        enemies.erase(it, enemies.end());
    }
}

// Operator<< actualizat
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
    os << map.player << "\n"; // Afisam player-ul
    os << "Vrajitori: " << map.towers.size() << " | Blesteme: " << map.enemies.size() << "\n";

    for (int y = 0; y < map.height; ++y) {
        for (int x = 0; x < map.width; ++x) {
            os << tempGrid[y][x];
        }
        os << "\n";
    }
    os << "===========================\n";
    return os;
}