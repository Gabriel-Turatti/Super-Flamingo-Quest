#include "../header/Item.hpp"


Item::Item(int x, int y, std::string namer, int SCALER) {
    name = namer;
    rect.x = x;
    rect.y = y;
    SCALE = SCALER;
    if (name == "copper-coin") {
        image = LoadTexture("images/copper-coin.png");
        rect.width = 9;
        rect.height = 11;
        rect.x += 2*SCALE;
        rect.y += 1*SCALE;
        category = 'C';
    } else if (name == "silver-coin") {
        image = LoadTexture("images/silver-coin.png");
        rect.width = 9;
        rect.height = 11;
        rect.x += 2*SCALE;
        rect.y += 1*SCALE;
        category = 'C';
    } else if (name == "gold-coin") {
        image = LoadTexture("images/gold-coin.png");
        rect.width = 9;
        rect.height = 11;
        rect.x += 2*SCALE;
        rect.y += 1*SCALE;
        category = 'C';
    } else if (name == "food-banana") {
        image = LoadTexture("images/food-banana.png");
        rect.width = 11;
        rect.height = 11;
        rect.x += 1*SCALE;
        rect.y += 1*SCALE;
        category = 'F';
    } else if (name == "food-pear") {
        image = LoadTexture("images/food-pear.png");
        rect.width = 13;
        rect.height = 13;
        rect.x += 0*SCALE;
        rect.y += 0*SCALE;
        category = 'F';
    } else if (name == "food-blueberry") {
        image = LoadTexture("images/food-blueberry.png");
        rect.width = 9;
        rect.height = 11;
        rect.x += 2*SCALE;
        rect.y += 1*SCALE;
        category = 'F';
    } else if (name == "food-pepper") {
        image = LoadTexture("images/food-pepper.png");
        rect.width = 11;
        rect.height = 11;
        rect.x += 1*SCALE;
        rect.y += 1*SCALE;
        category = 'F';
    } else if (name == "food-orange") {
        image = LoadTexture("images/food-orange.png");
        rect.width = 11;
        rect.height = 12;
        rect.x += 1*SCALE;
        rect.y += 0*SCALE;
        category = 'F';
    } else if (name == "Hshard-hope") {
        image = LoadTexture("images/Hshard-hope.png");
        rect.width = 7;
        rect.height = 9;
        rect.x += 3*SCALE;
        rect.y += 2*SCALE;
        category = 'H';
    } else if (name == "Hshard-resilience") {
        image = LoadTexture("images/Hshard-resilience.png");
        rect.width = 7;
        rect.height = 9;
        rect.x += 3*SCALE;
        rect.y += 2*SCALE;
        category = 'H';
    } else if (name == "Hshard-power") {
        image = LoadTexture("images/Hshard-power.png");
        rect.width = 7;
        rect.height = 9;
        rect.x += 3*SCALE;
        rect.y += 2*SCALE;
        category = 'H';
    } else if (name == "Hshard-courage") {
        image = LoadTexture("images/Hshard-courage.png");
        rect.width = 7;
        rect.height = 9;
        rect.x += 3*SCALE;
        rect.y += 2*SCALE;
        category = 'H';
    } else if (name == "Hshard-wisdom") {
        image = LoadTexture("images/Hshard-wisdom.png");
        rect.width = 7;
        rect.height = 9;
        rect.x += 3*SCALE;
        rect.y += 2*SCALE;
        category = 'H';
    } else if (name == "key-hope") {
        image = LoadTexture("images/key-hope.png");
        rect.width = 7;
        rect.height = 11;
        rect.x += 3*SCALE;
        rect.y += 1*SCALE;
        category = 'K';
    }
    cx = x+rect.width*SCALE/2;
    cy = y+rect.height*SCALE/2;
}