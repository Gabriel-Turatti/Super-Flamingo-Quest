#include "../include/Block.hpp"

Block::Block(int x, int y, int w, int h, std::string namer, int SCALER, int rotator, bool backgrounder, bool secreter) {
    rect.x = x;
    rect.y = y;
    SCALE = SCALER;
    rectImage.width = w/SCALE;
    rectImage.height = h/SCALE;
    if (namer == "grass") {
        id = 1;
        friction = 2;
    } else if (namer == "dirt") {
        id = 2;
        friction = 2.1;
    } else if (namer == "dirt2") {
        id = 3;
        friction = 2.1;
    } else if (namer == "brick") {
        id = 4;
        friction = 1.8;
    } else if (namer == "gate-hope") {
        id = 5;
        friction = 1.5;
    } else if (namer == "gate-resilience") {
        id = 6;
        friction = 1.5;
    } else if (namer == "gate-power") {
        id = 7;
        friction = 1.5;
    } else if (namer == "gate-courage") {
        id = 8;
        friction = 1.5;
    } else if (namer == "gate-wisdom") {
        id = 9;
        friction = 1.5;
    } else if (namer == "platform") {
        id = 30;
        friction = 2;
    } else if (namer == "altar") {
        id = 15;
        friction = 8.5;
    } else if (namer == "spike") {
        id = 16;
        friction = 0.9;
        rectImage.width = 13;
        rectImage.height = 8;
        if (rotator == 0) {
            rect.y += 5*SCALE;
        } else if (rotator == 1) {
            rect.x += 5*SCALE;
        } else if (rotator == 2) {
            rect.y += (3-rectImage.height)*SCALE;
        } else if (rotator == 3) {
            rect.x += (3-rectImage.height)*SCALE;
        }
    } else if (namer == "nextLevel") {
        id = 17;
        friction = 1;
    } else if (namer == "startLevel") {
        id = 18;
        friction = 1;
    } else if (namer == "cage") {
        int type = (x+y) % 5;
        switch (type) {
            case 0:
                id = 19;
                break;
            case 1:
                id = 20;
                break;
            case 2:
                id = 21;
                break;
            case 3:
                id = 22;
                break;
            case 4:
                id = 23;
                break;
        }
        friction = 2;
    } else if (namer == "honey") {
        id = 24;
        friction = 5.5;
    } else if (namer == "vines") {
        id = 25;
        friction = 2.5;
    } else if (namer == "ivy") {
        id = 26;
        friction = 3;
    } else if (namer == "switch_green") {
        id = 27;
        friction = 1.8;
    } else if (namer == "green") {
        id = 28;
        friction = 2;
    } else if (namer == "energy") {
        id = 29;
        friction = 3;
        parameter = 450;
    }
    // If you're adding a new block, make sure to also add it to:
    // BlockHandler
    // editLevel
    // SaveFile
    // LoadFile
    SetTextureWrap(image, TEXTURE_WRAP_CLAMP);

    if (rotator == 0) {
    
    } else if (rotator == 1) {
        float WBucket = rectImage.height;
        float HBucket = rectImage.width;
        rectImage.height = HBucket;
        rectImage.width = WBucket;
        rect.y += -rectImage.height*SCALE + 39;
    } else if (rotator == 2) {
        rect.x += -rectImage.width*SCALE + 39;
        rect.y += -rectImage.height*SCALE + 39;
    } else if (rotator == 3) {
        float WBucket = rectImage.height;
        float HBucket = rectImage.width;
        rectImage.height = HBucket;
        rectImage.width = WBucket;
        rect.x += -rectImage.width*SCALE + 39;
    }

    background = backgrounder;
    secret = secreter;
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
