#ifndef ENEMY_H
#define ENEMY_H

#include "raylib.h"
#include "Block.hpp"
#include "Functions.hpp"
#include <fstream>
#include <vector>

class Enemy {
public:
    Rectangle rect;
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
    int direction; // *90º clock-wise

    Enemy(float x, float y, std::string namer, int imagescale, std::vector<Block> map, int ticker, Block grounder);

    void update(std::vector<Block> map);

    void bee();

    void snail(std::vector<Block> map);
};

// class Bee : Enemy {

// };

#endif