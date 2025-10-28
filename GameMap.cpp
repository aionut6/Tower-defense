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
    // initializam grila
    grid.resize(height, std::vector<char>(width, '.')); // Umplem grila cu '.'
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
      grid(other.grid)
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
    grid = other.grid; // Adaugam copierea grilei

    return *this;
}

bool GameMap::buildTower(const Tower& newTower) {
    if (playerMoney >= newTower.getCost()) {
        int x = newTower.getPosition().getX();
        int y = newTower.getPosition().getY();

        //daca pozitia e valida
        if (y >= 0 && y < height && x >= 0 && x < width && grid[y][x] == '.') {
            //locul e liber construim
            playerMoney -= newTower.getCost();
            towers.push_back(newTower);
            grid[y][x] = 'T';
            std::cout << "Vrajitor " << newTower.getType() << " plasat! Bani ramasi: " << playerMoney << std::endl;
            return true;
        } else {
            std::cout << "EROARE: Pozitie invalida sau ocupata de alt Vrajitor!" << std::endl;
        }
    } else {
        std::cout << "EROARE: Fonduri insuficiente pentru " << newTower.getType() << std::endl;
    }
    return false;
}

void GameMap::spawnEnemy(const Enemy& newEnemy) {
    enemies.push_back(newEnemy);
    std::cout << "Un blestem " << newEnemy.getType() << " a aparut pe harta!" << std::endl;
}

void GameMap::updateGame() {
    std::cout << "\n--- ACTUALIZARE RUNDA ---" << std::endl;

    // vrajitorii ataca
    for (const Tower& tower : towers) {
        for (Enemy& enemy : enemies) {
            tower.attack(enemy);
        }
    }

    // blestemele se misca
    for (Enemy& enemy : enemies) {
        if (enemy.getHealth() <= 0) continue;

        int x = enemy.getPosition().getX();
        int y = enemy.getPosition().getY();
        int newX = x + enemy.getSpeed();

        //verificam daca a iesit de pe harta
        if (newX >= width) {
            playerLives--; //jucatorul pierde hp
            enemy.takeDamage(9999); //omoram inamicul
            std::cout << "Un blestem a ajuns la baza! Vieti ramase: " << playerLives << std::endl;
        } else {
            //muta inamicul
            enemy.setPosition(Position(newX, y));
        }
    }

    //curatam blestemele moarte
    auto it = std::ranges::remove_if(enemies,
                                     [](const Enemy& e) {
                                         return e.getHealth() <= 0;
                                     }).begin();

    if (it != enemies.end()) {
        std::cout << "Eliminam blestemele invinse..." << std::endl;
        enemies.erase(it, enemies.end());
    }
}

std::ostream& operator<<(std::ostream& os, const GameMap& map) {
    std::vector<std::vector<char>> tempGrid = map.grid;

    //punem toti inamicii pe grila temporara
    for (const Enemy& e : map.enemies) {
        int x = e.getPosition().getX();
        int y = e.getPosition().getY();
        //verificam sa fim in interiorul hartii
        if (y >= 0 && y < map.height && x >= 0 && x < map.width) {
            tempGrid[y][x] = 'B'; // 'B' de la Blestem
        }
    }

    //afisam starea si grila
    os << "====== STAREA HARTII ======\n";
    os << "Vieti: " << map.playerLives << " | Bani: " << map.playerMoney;
    os << " | Vrajitori: " << map.towers.size() << " | Blesteme: " << map.enemies.size() << "\n";

    //desenam grila
    for (int y = 0; y < map.height; ++y) {
        for (int x = 0; x < map.width; ++x) {
            os << tempGrid[y][x];
        }
        os << "\n";
    }
    os << "===========================\n";
    return os;
}