#include "raylib.h"
#include <fstream>

class Block {
public:
    Rectangle rect;
    float cx, cy;
    float friction;
    Texture2D image;
    int SCALE;
    bool background = false, secret = false, rotate = false;
    std::string name;

    Block(int x, int y, int w, int h, std::string namer, int SCALER, bool rotator = false) {}
    Block() {}
};