#ifndef ITEM_H
#define ITEM_H

#include "raylib.h"
#include <fstream>

class Item {
public:
    Rectangle rect;
    float cx, cy;
    std::string name;
    char category;
    Texture2D image;
    int SCALE;

    Item(int x, int y, std::string namer, int SCALER, char categorizer);
};

#endif