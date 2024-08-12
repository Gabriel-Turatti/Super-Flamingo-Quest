#ifndef ITEM_H
#define ITEM_H

#include "raylib.h"
#include <fstream>

class Item {
public:
    Rectangle rect;
    Rectangle rectImage;
    float cx, cy;
    std::string name;
    char category;
    Texture2D image;
    int SCALE;
    // int imageSize;
    // int imageCount;
    // int tickImage = 0;

    Item(int x, int y, std::string namer, int SCALER, char categorizer);
    Item();
    // ~Item();
};

#endif