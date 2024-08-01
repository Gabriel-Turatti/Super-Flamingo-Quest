#ifndef EFFECT_H
#define EFFECT_H

#include "raylib.h"
#include "Block.hpp"
#include "Functions.hpp"
#include "Flamingo.hpp"
#include <fstream>
#include <vector>

class Effect {
public:
    Rectangle rect;
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


    Effect(Vector2 position, Vector2 direction, int lifespan, int identificator, int damager[5], int SCALER);

    bool update(std::vector<Block> map, Flamingo &player);
};

#endif