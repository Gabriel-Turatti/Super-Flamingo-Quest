#ifndef MAPLOADER_H
#define MAPLOADER_H

#include "raylib.h"
#include <string>
#include <vector>
#include <fstream>
#include <random>

#include "Block.hpp"
#include "Effect.hpp"
#include "Item.hpp"
#include "Level.hpp"
#include "Flamingo.hpp"
#include "Enemy.hpp"
#include "Functions.hpp"


class MapLoader {
public:
    struct Dust {
        Vector2 pos;
        Vector2 dt;
        Color cor;
        int timer;
    };
    std::vector<Block> Blocks;
    std::vector<Item> itens;
    std::vector<Enemy> enemies;
    std::vector<Effect> effects;
    std::vector<Dust> dusts;
    int SCALE;
    int BS;
    float WT;
    float HT;

    MapLoader(int SCALER, int BSer, float width, float height);
    MapLoader();

    Map LoadFile(std::string name);
};

#endif