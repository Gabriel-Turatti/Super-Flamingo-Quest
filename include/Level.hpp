#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include "Block.hpp"
#include "Item.hpp"
#include "Enemy.hpp"

class Level {
public:
    std::map<int, std::map<int, Block>> FrontBlocksMap;
    std::map<int, std::map<int, Block>> BackBlocksMap;
    std::vector<Item> itens;
    std::vector<Enemy> enemies;
    int widthLevel;
    int heightLevel;
    std::string name;
    char* levelTheme;
    int time;
    std::vector<door> entrances;
    std::vector<door> exits;
};

#endif