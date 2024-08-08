#include "../header/Item.hpp"


Item::Item(int x, int y, std::string namer, int SCALER, char categorizer) {
    name = namer;
    rect.x = x;
    rect.y = y;
    SCALE = SCALER;
    category = categorizer;
    image = LoadTexture("images/coin-copper.png");
    // Padrão é 13x13, se for 2 pixels menores que isso de alguma forma, é necessário colocar a posição 1*SCALE pra frente para ficar centralizado
    if (name == "coin-copper") {
        image = LoadTexture("images/coin-copper.png");
        rectImage.width = 9;
        rectImage.height = 11;
        rect.x += 2*SCALE;
        rect.y += 1*SCALE;
    } else if (name == "coin-silver") {
        image = LoadTexture("images/coin-silver.png");
        rectImage.width = 9;
        rectImage.height = 11;
        rect.x += 2*SCALE;
        rect.y += 1*SCALE;
    } else if (name == "coin-gold") {
        image = LoadTexture("images/coin-gold.png");
        rectImage.width = 9;
        rectImage.height = 11;
        rect.x += 2*SCALE;
        rect.y += 1*SCALE;
    } else if (name == "coin-death") {
        image = LoadTexture("images/coin-death.png");
        rectImage.width = 13;
        rectImage.height = 13;
        rect.x += 0*SCALE;
        rect.y += 0*SCALE;
    } else if (name == "food-banana") {
        image = LoadTexture("images/food-banana.png");
        rectImage.width = 11;
        rectImage.height = 11;
        rect.x += 1*SCALE;
        rect.y += 1*SCALE;
    } else if (name == "food-pear") {
        image = LoadTexture("images/food-pear.png");
        rectImage.width = 13;
        rectImage.height = 13;
        rect.x -= 0*SCALE;
        rect.y -= 0*SCALE;
    } else if (name == "food-blueberry") {
        image = LoadTexture("images/food-blueberry.png");
        rectImage.width = 9;
        rectImage.height = 11;
        rect.x += 2*SCALE;
        rect.y += 1*SCALE;
    } else if (name == "food-pepper") {
        image = LoadTexture("images/food-pepper.png");
        rectImage.width = 11;
        rectImage.height = 11;
        rect.x += 1*SCALE;
        rect.y += 1*SCALE;
    } else if (name == "food-orange") {
        image = LoadTexture("images/food-orange.png");
        rectImage.width = 11;
        rectImage.height = 12;
        rect.x += 1*SCALE;
        rect.y += 0*SCALE;
    } else if (name == "Hshard-hope") {
        image = LoadTexture("images/Hshard-hope.png");
        rectImage.width = 7;
        rectImage.height = 9;
        rect.x += 3*SCALE;
        rect.y += 2*SCALE;
    } else if (name == "Hshard-resilience") {
        image = LoadTexture("images/Hshard-resilience.png");
        rectImage.width = 7;
        rectImage.height = 9;
        rect.x += 3*SCALE;
        rect.y += 2*SCALE;
    } else if (name == "Hshard-power") {
        image = LoadTexture("images/Hshard-power.png");
        rectImage.width = 7;
        rectImage.height = 9;
        rect.x += 3*SCALE;
        rect.y += 2*SCALE;
    } else if (name == "Hshard-courage") {
        image = LoadTexture("images/Hshard-courage.png");
        rectImage.width = 7;
        rectImage.height = 9;
        rect.x += 3*SCALE;
        rect.y += 2*SCALE;
    } else if (name == "Hshard-wisdom") {
        image = LoadTexture("images/Hshard-wisdom.png");
        rectImage.width = 7;
        rectImage.height = 9;
        rect.x += 3*SCALE;
        rect.y += 2*SCALE;
    } else if (name == "Pshard-wind") {
        image = LoadTexture("images/Pshard-wind.png");
        rectImage.width = 8;
        rectImage.height = 8;
        rect.x += 2.5*SCALE;
        rect.y += 2.5*SCALE;
    } else if (name == "Pshard-party") {
        image = LoadTexture("images/Pshard-party.png");
        rectImage.width = 8;
        rectImage.height = 8;
        rect.x += 2.5*SCALE;
        rect.y += 2.5*SCALE;
    } else if (name == "Pshard-fun") {
        image = LoadTexture("images/Pshard-fun.png");
        rectImage.width = 8;
        rectImage.height = 8;
        rect.x += 2.5*SCALE;
        rect.y += 2.5*SCALE;
    } else if (name == "Pshard-hard") {
        image = LoadTexture("images/Pshard-hard.png");
        rectImage.width = 8;
        rectImage.height = 8;
        rect.x += 2.5*SCALE;
        rect.y += 2.5*SCALE;
    } else if (name == "Pshard-eloise") {
        image = LoadTexture("images/Pshard-eloise.png");
        rectImage.width = 8;
        rectImage.height = 8;
        rect.x += 2.5*SCALE;
        rect.y += 2.5*SCALE;
    } else if (name == "key-hope") {
        image = LoadTexture("images/key-hope.png");
        rectImage.width = 7;
        rectImage.height = 11;
        rect.x += 3*SCALE;
        rect.y += 1*SCALE;
    } else if (name == "key-resilience") {
        image = LoadTexture("images/key-resilience.png");
        rectImage.width = 7;
        rectImage.height = 11;
        rect.x += 3*SCALE;
        rect.y += 1*SCALE;
    } else if (name == "key-power") {
        image = LoadTexture("images/key-power.png");
        rectImage.width = 7;
        rectImage.height = 12;
        rect.x += 3*SCALE;
        rect.y += 1*SCALE;
    } else if (name == "key-courage") {
        image = LoadTexture("images/key-courage.png");
        rectImage.width = 9;
        rectImage.height = 11;
        rect.x += 2*SCALE;
        rect.y += 1*SCALE;
    } else if (name == "key-wisdom") {
        image = LoadTexture("images/key-wisdom.png");
        rectImage.width = 7;
        rectImage.height = 11;
        rect.x += 3*SCALE;
        rect.y += 1*SCALE;
    } else if (name == "courage-potion") {
        image = LoadTexture("images/courage-potion.png");
        rectImage.width = 9;
        rectImage.height = 11;
        rect.x += 2*SCALE;
        rect.y += 1*SCALE;
    } else if (name == "party-potion") {
        image = LoadTexture("images/party-potion.png");
        rectImage.width = 9;
        rectImage.height = 11;
        rect.x += 2*SCALE;
        rect.y += 1*SCALE;
    } else if (name == "power-dash") {
        image = LoadTexture("images/power-dash.png");
        rectImage.width = 15;
        rectImage.height = 15;
        rect.x -= 1*SCALE;
        rect.y -= 1*SCALE;
    } else if (name == "power-transmutation") {
        image = LoadTexture("images/power-transmutation.png");
        rectImage.width = 15;
        rectImage.height = 15;
        rect.x -= 1*SCALE;
        rect.y -= 1*SCALE;
    } else if (name == "power-boost") {
        image = LoadTexture("images/power-boost.png");
        rectImage.width = 15;
        rectImage.height = 15;
        rect.x -= 1*SCALE;
        rect.y -= 1*SCALE;
    } else if (name == "power-spear") {
        image = LoadTexture("images/power-spear.png");
        rectImage.width = 15;
        rectImage.height = 15;
        rect.x -= 1*SCALE;
        rect.y -= 1*SCALE;
    }

    // if you're adding an item here, don't forget to also add it to:
    // SaveFile (Twice)
    // EditLevel

    rect.width = rectImage.width*SCALE;
    rect.height = rectImage.height*SCALE;
    cx = rect.x+rect.width/2;
    cy = rect.y+rect.height/2;
}

Item::Item() {SCALE = 0;}