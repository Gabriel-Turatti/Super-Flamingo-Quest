#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include "Block.hpp"
#include "Item.hpp"
#include "Enemy.hpp"

class Map {
public:
    std::vector<Block> Blocks;
    std::vector<Item> itens;
    std::vector<Enemy> enemies;
    int widthLevel;
    int heightLevel;
    float playerX;
    float playerY;
};

#endif