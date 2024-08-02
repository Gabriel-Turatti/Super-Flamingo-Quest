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
        rect.width = 9;
        rect.height = 11;
        rect.x += 2*SCALE;
        rect.y += 1*SCALE;
    } else if (name == "coin-silver") {
        image = LoadTexture("images/coin-silver.png");
        rect.width = 9;
        rect.height = 11;
        rect.x += 2*SCALE;
        rect.y += 1*SCALE;
    } else if (name == "coin-gold") {
        image = LoadTexture("images/coin-gold.png");
        rect.width = 9;
        rect.height = 11;
        rect.x += 2*SCALE;
        rect.y += 1*SCALE;
    } else if (name == "coin-death") {
        image = LoadTexture("images/coin-death.png");
        rect.width = 13;
        rect.height = 13;
        rect.x += 0*SCALE;
        rect.y += 0*SCALE;
    } else if (name == "food-banana") {
        image = LoadTexture("images/food-banana.png");
        rect.width = 11;
        rect.height = 11;
        rect.x += 1*SCALE;
        rect.y += 1*SCALE;
    } else if (name == "food-pear") {
        image = LoadTexture("images/food-pear.png");
        rect.width = 13;
        rect.height = 13;
        rect.x -= 1*SCALE;
        rect.y -= 1*SCALE;
    } else if (name == "food-blueberry") {
        image = LoadTexture("images/food-blueberry.png");
        rect.width = 9;
        rect.height = 11;
        rect.x += 2*SCALE;
        rect.y += 1*SCALE;
    } else if (name == "food-pepper") {
        image = LoadTexture("images/food-pepper.png");
        rect.width = 11;
        rect.height = 11;
        rect.x += 1*SCALE;
        rect.y += 1*SCALE;
    } else if (name == "food-orange") {
        image = LoadTexture("images/food-orange.png");
        rect.width = 11;
        rect.height = 12;
        rect.x += 1*SCALE;
        rect.y += 0*SCALE;
    } else if (name == "Hshard-hope") {
        image = LoadTexture("images/Hshard-hope.png");
        rect.width = 7;
        rect.height = 9;
        rect.x += 3*SCALE;
        rect.y += 2*SCALE;
    } else if (name == "Hshard-resilience") {
        image = LoadTexture("images/Hshard-resilience.png");
        rect.width = 7;
        rect.height = 9;
        rect.x += 3*SCALE;
        rect.y += 2*SCALE;
    } else if (name == "Hshard-power") {
        image = LoadTexture("images/Hshard-power.png");
        rect.width = 7;
        rect.height = 9;
        rect.x += 3*SCALE;
        rect.y += 2*SCALE;
    } else if (name == "Hshard-courage") {
        image = LoadTexture("images/Hshard-courage.png");
        rect.width = 7;
        rect.height = 9;
        rect.x += 3*SCALE;
        rect.y += 2*SCALE;
    } else if (name == "Hshard-wisdom") {
        image = LoadTexture("images/Hshard-wisdom.png");
        rect.width = 7;
        rect.height = 9;
        rect.x += 3*SCALE;
        rect.y += 2*SCALE;
    } else if (name == "Pshard-wind") {
        image = LoadTexture("images/Pshard-wind.png");
        rect.width = 8;
        rect.height = 8;
        rect.x += 2.5*SCALE;
        rect.y += 2.5*SCALE;
    } else if (name == "Pshard-party") {
        image = LoadTexture("images/Pshard-party.png");
        rect.width = 8;
        rect.height = 8;
        rect.x += 2.5*SCALE;
        rect.y += 2.5*SCALE;
    } else if (name == "Pshard-fun") {
        image = LoadTexture("images/Pshard-fun.png");
        rect.width = 8;
        rect.height = 8;
        rect.x += 2.5*SCALE;
        rect.y += 2.5*SCALE;
    } else if (name == "Pshard-hard") {
        image = LoadTexture("images/Pshard-hard.png");
        rect.width = 8;
        rect.height = 8;
        rect.x += 2.5*SCALE;
        rect.y += 2.5*SCALE;
    } else if (name == "Pshard-eloise") {
        image = LoadTexture("images/Pshard-eloise.png");
        rect.width = 8;
        rect.height = 8;
        rect.x += 2.5*SCALE;
        rect.y += 2.5*SCALE;
    } else if (name == "key-hope") {
        image = LoadTexture("images/key-hope.png");
        rect.width = 7;
        rect.height = 11;
        rect.x += 3*SCALE;
        rect.y += 1*SCALE;
    } else if (name == "courage-potion") {
        image = LoadTexture("images/courage-potion.png");
        rect.width = 9;
        rect.height = 11;
        rect.x += 2*SCALE;
        rect.y += 1*SCALE;
    } else if (name == "party-potion") {
        image = LoadTexture("images/party-potion.png");
        rect.width = 9;
        rect.height = 11;
        rect.x += 2*SCALE;
        rect.y += 1*SCALE;
    } else if (name == "power-dash") {
        image = LoadTexture("images/power-dash.png");
        rect.width = 15;
        rect.height = 15;
        rect.x -= 1*SCALE;
        rect.y -= 1*SCALE;
    } else if (name == "power-transmutation") {
        image = LoadTexture("images/power-transmutation.png");
        rect.width = 15;
        rect.height = 15;
        rect.x -= 1*SCALE;
        rect.y -= 1*SCALE;
    } else if (name == "power-boost") {
        image = LoadTexture("images/power-boost.png");
        rect.width = 15;
        rect.height = 15;
        rect.x -= 1*SCALE;
        rect.y -= 1*SCALE;
    } else if (name == "power-spear") {
        image = LoadTexture("images/power-spear.png");
        rect.width = 15;
        rect.height = 15;
        rect.x -= 1*SCALE;
        rect.y -= 1*SCALE;
    }
    cx = x+rect.width*SCALE/2;
    cy = y+rect.height*SCALE/2;
}

Item::Item() {}