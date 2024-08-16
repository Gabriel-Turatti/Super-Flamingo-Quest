#include "../header/Item.hpp"


Item::Item(int x, int y, std::string namer, int SCALER, char categorizer) {
    name = namer;
    rect.x = x;
    rect.y = y;
    SCALE = SCALER;
    category = categorizer;
    imageSize = 0;
    imageCount = ((int) rect.x + (int) rect.y) % 30;
    // Padrão é 13x13, se for 2 pixels menores que isso de alguma forma, é necessário colocar a posição 1*SCALE pra frente para ficar centralizado
    if (name == "coin-copper") {
        imageSize = 9;
        imageCount = ((int)rect.x + (int)rect.y) % 10;
        animation[0] = 0;
        animation[1] = 0;
        animation[2] = 0;
        animation[3] = 0;
        animation[4] = 1;
        animation[5] = 2;
        animation[6] = 3;
        animation[7] = 2;
        animation[8] = 1;
        id = 1;
        rectImage.width = 9;
        rectImage.height = 11;
        rect.x += 2*SCALE;
        rect.y += 1*SCALE;
    } else if (name == "coin-silver") {
        id = 2;
        imageSize = 9;
        imageCount = ((int)rect.x + (int)rect.y) % 10;
        animation[0] = 0;
        animation[1] = 0;
        animation[2] = 0;
        animation[3] = 0;
        animation[4] = 1;
        animation[5] = 2;
        animation[6] = 3;
        animation[7] = 2;
        animation[8] = 1;
        rectImage.width = 9;
        rectImage.height = 11;
        rect.x += 2*SCALE;
        rect.y += 1*SCALE;
    } else if (name == "coin-gold") {
        id = 3;
        imageSize = 9;
        imageCount = ((int)rect.x + (int)rect.y) % 10;
        animation[0] = 0;
        animation[1] = 0;
        animation[2] = 0;
        animation[3] = 0;
        animation[4] = 1;
        animation[5] = 2;
        animation[6] = 3;
        animation[7] = 2;
        animation[8] = 1;
        rectImage.width = 9;
        rectImage.height = 11;
        rect.x += 2*SCALE;
        rect.y += 1*SCALE;
    } else if (name == "coin-death") {
        id = 4;
        imageSize = 10;
        imageCount = ((int)rect.x + (int)rect.y) % 10;
        animation[0] = 0;
        animation[1] = 0;
        animation[2] = 1;
        animation[3] = 2;
        animation[4] = 3;
        animation[5] = 4;
        animation[6] = 3;
        animation[7] = 2;
        animation[8] = 1;
        animation[9] = 0;
        rectImage.width = 13;
        rectImage.height = 13;
        rect.x += 0*SCALE;
        rect.y += 0*SCALE;
    } else if (name == "food-banana") {
        id = 5;
        rectImage.width = 11;
        rectImage.height = 11;
        rect.x += 1*SCALE;
        rect.y += 1*SCALE;
    } else if (name == "food-pear") {
        id = 6;
        rectImage.width = 13;
        rectImage.height = 13;
        rect.x -= 1*SCALE;
        rect.y -= 1*SCALE;
    } else if (name == "food-blueberry") {
        id = 7;
        rectImage.width = 9;
        rectImage.height = 11;
        rect.x += 2*SCALE;
        rect.y += 1*SCALE;
    } else if (name == "food-pepper") {
        id = 8;
        rectImage.width = 11;
        rectImage.height = 11;
        rect.x += 1*SCALE;
        rect.y += 1*SCALE;
    } else if (name == "food-orange") {
        id = 9;
        rectImage.width = 11;
        rectImage.height = 12;
        rect.x += 1*SCALE;
        rect.y += 0*SCALE;
    } else if (name == "Hshard-hope") {
        id = 10;
        rectImage.width = 7;
        rectImage.height = 9;
        rect.x += 3*SCALE;
        rect.y += 2*SCALE;
    } else if (name == "Hshard-resilience") {
        id = 11;
        rectImage.width = 7;
        rectImage.height = 9;
        rect.x += 3*SCALE;
        rect.y += 2*SCALE;
    } else if (name == "Hshard-power") {
        id = 12;
        rectImage.width = 7;
        rectImage.height = 9;
        rect.x += 3*SCALE;
        rect.y += 2*SCALE;
    } else if (name == "Hshard-courage") {
        id = 13;
        rectImage.width = 7;
        rectImage.height = 9;
        rect.x += 3*SCALE;
        rect.y += 2*SCALE;
    } else if (name == "Hshard-wisdom") {
        id = 14;
        rectImage.width = 7;
        rectImage.height = 9;
        rect.x += 3*SCALE;
        rect.y += 2*SCALE;
    } else if (name == "Pshard-wind") {
        id = 15;
        rectImage.width = 8;
        rectImage.height = 8;
        rect.x += 2.5*SCALE;
        rect.y += 2.5*SCALE;
    } else if (name == "Pshard-party") {
        id = 16;
        rectImage.width = 8;
        rectImage.height = 8;
        rect.x += 2.5*SCALE;
        rect.y += 2.5*SCALE;
    } else if (name == "Pshard-fun") {
        id = 17;
        rectImage.width = 8;
        rectImage.height = 8;
        rect.x += 2.5*SCALE;
        rect.y += 2.5*SCALE;
    } else if (name == "Pshard-hard") {
        id = 18;
        rectImage.width = 8;
        rectImage.height = 8;
        rect.x += 2.5*SCALE;
        rect.y += 2.5*SCALE;
    } else if (name == "Pshard-eloise") {
        id = 19;
        rectImage.width = 8;
        rectImage.height = 8;
        rect.x += 2.5*SCALE;
        rect.y += 2.5*SCALE;
    } else if (name == "key-hope") {
        id = 20;
        rectImage.width = 7;
        rectImage.height = 11;
        rect.x += 3*SCALE;
        rect.y += 1*SCALE;
    } else if (name == "key-resilience") {
        id = 21;
        rectImage.width = 7;
        rectImage.height = 11;
        rect.x += 3*SCALE;
        rect.y += 1*SCALE;
    } else if (name == "key-power") {
        id = 22;
        rectImage.width = 7;
        rectImage.height = 12;
        rect.x += 3*SCALE;
        rect.y += 1*SCALE;
    } else if (name == "key-courage") {
        id = 23;
        rectImage.width = 9;
        rectImage.height = 11;
        rect.x += 2*SCALE;
        rect.y += 1*SCALE;
    } else if (name == "key-wisdom") {
        id = 24;
        rectImage.width = 7;
        rectImage.height = 11;
        rect.x += 3*SCALE;
        rect.y += 1*SCALE;
    } else if (name == "courage-potion") {
        id = 25;
        rectImage.width = 9;
        rectImage.height = 11;
        rect.x += 2*SCALE;
        rect.y += 1*SCALE;
    } else if (name == "party-potion") {
        id = 26;
        rectImage.width = 9;
        rectImage.height = 11;
        rect.x += 2*SCALE;
        rect.y += 1*SCALE;
    } else if (name == "power-dash") {
        id = 27;
        rectImage.width = 15;
        rectImage.height = 15;
        rect.x -= 1*SCALE;
        rect.y -= 1*SCALE;
    } else if (name == "power-toast") {
        id = 28;
        rectImage.width = 15;
        rectImage.height = 15;
        rect.x -= 1*SCALE;
        rect.y -= 1*SCALE;
    } else if (name == "power-boost") {
        id = 29;
        rectImage.width = 15;
        rectImage.height = 15;
        rect.x -= 1*SCALE;
        rect.y -= 1*SCALE;
    } else if (name == "power-spear") {
        id = 30;
        rectImage.width = 15;
        rectImage.height = 15;
        rect.x -= 1*SCALE;
        rect.y -= 1*SCALE;
    } else if (name == "power-transmutation") {
        id = 31;
        rectImage.width = 15;
        rectImage.height = 15;
        rect.x -= 1*SCALE;
        rect.y -= 1*SCALE;
    } else if (name == "coin-poison") {
        id = 32;
        imageSize = 9;
        imageCount = ((int)rect.x + (int)rect.y) % 10;
        animation[0] = 0;
        animation[1] = 0;
        animation[2] = 0;
        animation[3] = 0;
        animation[4] = 1;
        animation[5] = 2;
        animation[6] = 3;
        animation[7] = 2;
        animation[8] = 1;
        rectImage.width = 9;
        rectImage.height = 11;
        rect.x += 2*SCALE;
        rect.y += 1*SCALE;
    }

    // if you're adding an item here, don't forget to also add it to:
    // SaveLevel (Twice)
    // LoadLevel
    // EditLevel
    // ItemHandler
    // Flamingo's Collect

    rect.width = rectImage.width*SCALE;
    rect.height = rectImage.height*SCALE;
    cx = rect.x+rect.width/2;
    cy = rect.y+rect.height/2;
}

Item::Item() {SCALE = 0;}