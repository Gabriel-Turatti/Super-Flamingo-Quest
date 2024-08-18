#pragma once

#include <string>
#include "raylib.h"

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
    int parameter;
    int id;

    Block(int x,
          int y,
          int w,
          int h,
          std::string namer,
          int SCALER,
          int rotator = 0,
          bool backgrounder = false,
          bool secreter = false);
    Block();
};
