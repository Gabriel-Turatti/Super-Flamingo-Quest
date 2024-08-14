#ifndef ITEM_H
#define ITEM_H

#include "raylib.h"
#include <fstream>
#include <vector>

class Item {
public:
    Rectangle rect;
    Rectangle rectImage;
    float cx, cy;
    std::string name;
    char category;
    int SCALE;
    int id;
    int imageSize;
    int imageCount;
    int tickImage = 0;
    int animation[10];

    Item(int x, int y, std::string namer, int SCALER, char categorizer);
    Item();
};

#endif