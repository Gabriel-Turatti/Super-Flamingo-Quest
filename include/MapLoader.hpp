#ifndef MAPLOADER_H
#define MAPLOADER_H

#include <string.h>

#include <fstream>
#include <random>
#include <string>
#include <vector>

#include "block.hpp"
#include "Effect.hpp"
#include "Enemy.hpp"
#include "Flamingo.hpp"
#include "Functions.hpp"
#include "Item.hpp"
#include "Level.hpp"
#include "predefinitions.hpp"
#include "raylib.h"

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

    void SaveLevel(Map level);
    void SaveFlamingo(Flamingo *player);
    std::unique_ptr<Flamingo> LoadFlamingo();
    Map LoadLevel(std::string name);
};

#endif