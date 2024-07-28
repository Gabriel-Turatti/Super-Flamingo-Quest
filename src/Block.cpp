#include "../header/Block.hpp"

Block::Block(int x, int y, int w, int h, std::string namer, int SCALER, bool rotator = false) {
    if (namer == "grass") {
        image = LoadTexture("images/block_grass.png");
        friction = 2.5;
    } else if (namer == "dirt2") {
        image = LoadTexture("images/block_dirt2x2.png");
        friction = 4;
    } else if (namer == "dirt") {
        image = LoadTexture("images/block_dirt.png");
        friction = 4;
    } else if (namer == "gate-hope") {
        image = LoadTexture("images/block_gates.png");
        friction = 1.5;
        rotate = rotator;
    }
    rect.x = x;
    rect.y = y;
    SCALE = SCALER;
    rect.width = w;
    rect.height = h;
    name = namer;
    if (rotate) {
        rect.height = w;
        rect.width = h;
    }
    cx = x+w*SCALE/2;
    cy = y+h*SCALE/2;
}

Block::Block() {}
