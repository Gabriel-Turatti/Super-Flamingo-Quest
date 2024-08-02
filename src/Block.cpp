#include "../header/Block.hpp"

Block::Block(int x, int y, int w, int h, std::string namer, int SCALER, int rotator = 0) {
    rect.x = x;
    rect.y = y;
    rect.width = w;
    rect.height = h;
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
    } else if (namer == "platform") {
        image = LoadTexture("images/platform.png");
        friction = 2;
        rect.height = 1;
    } else if (namer == "altar") {
        image = LoadTexture("images/block_altar.png");
        friction = 8.5;
    } else if (namer == "spike") {
        image = LoadTexture("images/block_spike.png");
        friction = 0.9;
        rect.width = 13;
        rect.height = 8;
        if (rotator == 0) {
            rect.y += 5*SCALE;
        } else if (rotator == 1) {
            rect.width = 8;
            rect.height = 13;
            rect.x += (13-rect.width)*SCALE;
        } else if (rotator == 2) {
            rect.y += (8-rect.height)*SCALE;
        } else if (rotator == 3) {
            rect.width = 8;
            rect.height = 13;
        }
    }
    direction = rotator;
    SCALE = SCALER;
    name = namer;
    cx = x+w*SCALE/2;
    cy = y+h*SCALE/2;
}

Block::Block() {
    SCALE = 0;
}
