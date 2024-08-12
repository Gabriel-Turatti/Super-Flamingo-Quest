#ifndef EFFECT_H
#define EFFECT_H

#include "raylib.h"
#include "predefinitions.hpp"
#include "Block.hpp"
#include "Item.hpp"
#include "Functions.hpp"
#include "Flamingo.hpp"
#include <fstream>
#include <vector>

class Effect {
public:
    Rectangle rect;
    Rectangle rectImage;
    float cx, cy;
    float vx, vy;
    Texture2D image;
    int SCALE;
    int id;
    int timer;
    int imageSize, imageCount;
    int dmg[5];
    int tick;
    std::vector<int> closeBlocks;
    std::vector<int> closeItens;
    std::vector<int> closeEnemies;


    Effect(Vector2 position, Vector2 direction, int lifespan, int identificator, int damager[5], int SCALER);

    bool update(std::vector<Block> Blocks, Flamingo &player, std::vector<Item> &itens, std::vector<Enemy> &enemies);

    bool meldropShot(std::vector<Block> Blocks, Flamingo &player);
    bool transmutation(std::vector<Item> &itens);
    bool spear(std::vector<Enemy> &enemies, std::vector<Item> &itens);
    bool bird();
};

#endif