#include "../header/Block.hpp"

Block::Block(int x, int y, int w, int h, std::string namer, int SCALER, int rotator, bool backgrounder) {
    rect.x = x;
    rect.y = y;
    SCALE = SCALER;
    rectImage.width = w/SCALE;
    rectImage.height = h/SCALE;
    if (namer == "grass") {
        image = LoadTexture("images/block_grass.png");
        friction = 2.5;
    } else if (namer == "dirt2") {
        image = LoadTexture("images/block_dirt2x2.png");
        friction = 4;
    } else if (namer == "dirt") {
        image = LoadTexture("images/block_dirt.png");
        friction = 4;
    } else if (namer == "brick") {
        image = LoadTexture("images/block_brick.png");
        friction = 1.8;
    } else if (namer == "gate-hope") {
        image = LoadTexture("images/block_gate_hope_closed.png");
        friction = 1.5;
    } else if (namer == "gate-resilience") {
        image = LoadTexture("images/block_gate_resilience_closed.png");
        friction = 1.5;
    } else if (namer == "gate-power") {
        image = LoadTexture("images/block_gate_power_closed.png");
        friction = 1.5;
    } else if (namer == "gate-courage") {
        image = LoadTexture("images/block_gate_courage_closed.png");
        friction = 1.5;
    } else if (namer == "gate-wisdom") {
        image = LoadTexture("images/block_gate_wisdom_closed.png");
        friction = 1.5;
    } else if (namer == "platform") {
        image = LoadTexture("images/platform.png");
        friction = 2;
    } else if (namer == "altar") {
        image = LoadTexture("images/block_altar.png");
        friction = 8.5;
    } else if (namer == "spike") {
        image = LoadTexture("images/block_spike.png");
        friction = 0.9;
        rectImage.width = 13;
        rectImage.height = 8;
        if (rotator == 0) {
            rect.y += 5*SCALE;
        } else if (rotator == 1) {
            rect.x += 5*SCALE;
        } else if (rotator == 2) {
            rect.y += (8-rectImage.height)*SCALE;
        } else if (rotator == 3) {
        }
    } else if (namer == "nextLevel") {
        image = LoadTexture("images/block_nextLevel.png");
        friction = 1;
    } else if (namer == "startLevel") {
        image = LoadTexture("images/block_StartLevel.png");
        friction = 1;
    }
    // If you're adding a new block, make sure to also add it to:
    // editLevel
    // SaveFile
    // LoadFile


    if (rotator != 0) {
        float WBucket = rectImage.height;
        float HBucket = rectImage.width;
        if (rotator == 1 or rotator == 3) {
            rectImage.height = HBucket;
            rectImage.width = WBucket;
        }
    }

    background = backgrounder;
    rect.width = rectImage.width*SCALE;
    rect.height = rectImage.height*SCALE;
    if (namer == "platform") {
        rect.height = SCALE;
    }
    direction = rotator;
    name = namer;
    cx = rect.x+rect.width/2;
    cy = rect.y+rect.height/2;
}

Block::Block() {
    SCALE = 0;
}
