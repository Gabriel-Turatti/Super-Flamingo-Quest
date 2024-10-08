#ifndef BLOCK_H
#define BLOCK_H

#include "raylib.h"
#include <fstream>


class Block {
public:
    Rectangle rect;
    Rectangle rectImage;
    float cx, cy;
    float friction;
    Texture2D image;
    int SCALE;
    bool background = false, secret = false;
    std::string name;
    int direction;

    Block(int x, int y, int w, int h, std::string namer, int SCALER, int rotator = 0, bool backgrounder = false, bool secreter = false);
    Block();
};

#endif