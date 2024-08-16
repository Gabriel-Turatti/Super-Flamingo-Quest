#ifndef ENEMY_H
#define ENEMY_H

#include "raylib.h"
#include "predefinitions.hpp"
#include "Block.hpp"
#include "Effect.hpp"
#include "Functions.hpp"
#include <fstream>
#include <cmath>



class Enemy {
public:
    Rectangle rect;
    Rectangle rectImage;
    float cx, cy;
    float vx, vy;
    std::vector<Texture2D> images = {};
    
    int imageCount = 0;
    int imageSize;

    int SCALE;
    std::string name;

    // Sound sfxCoin = LoadSound("sfx/coin.wav");

    char types[5] = {'H', 'R', 'P', 'C', 'W'};
    int dmgs[5] = {0, 0, 0, 0, 0};

    int id;
    int tick;

    // Bee
    int patrol1;
    int patrol2;
    Block border1;
    Block border2;

    // Snail
    std::vector<int> closeBlocks;
    Rectangle HBFeet, vision;
    Block ground;

    // Butterfly
    int angle;
    Vector2 orbit;

    // all
    int behavior;

    Enemy(float x, float y, std::string namer, int imagescale, std::map<int, std::map<int, Block>>, int ticker, int i = 0, int j = 0);

    Enemy();

    void update(std::vector<Block> Blocks, Flamingo* player, std::vector<Effect> &effects);

    void bee();

    void snail(std::vector<Block> Blocks);

    void butterfly(std::vector<Block> Blocks, Flamingo* player);

    void crab(Flamingo* player);
    
    void meldrop(Flamingo* player, std::vector<Effect> &effects);

    void getCloseBlocks(std::vector<Block> Blocks);
};

// class Bee : Enemy {

// };

#endif