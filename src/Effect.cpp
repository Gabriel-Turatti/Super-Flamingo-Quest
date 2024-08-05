#include "../header/Effect.hpp"

Effect::Effect(Vector2 position, Vector2 direction, int lifespan, int identificator, int damager[5], int SCALER) {
    tick = 1;
    rect.x = position.x;
    rect.y = position.y;
    timer = lifespan;
    id = identificator;
    vx = direction.x;
    vy = direction.y;
    imageCount = 0;
    SCALE = SCALER;
    dmg[0] = damager[0];
    dmg[1] = damager[1];
    dmg[2] = damager[2];
    dmg[3] = damager[3];
    dmg[4] = damager[4];

    if (id == 1) {
        PlaySound(LoadSound("sfx/meldrop-shot.wav"));
        image = LoadTexture("images/effect-meldrop-shot.png");
        imageSize = 2;
        rectImage.width = 6;
        rectImage.height = 6;
    } else if (id == 2) {
        // PlaySound(LoadSound("sfx/meldrop-shot.wav"));
        image = LoadTexture("images/effect-transmutation.png");
        imageSize = 1;
        rectImage.width = 15;
        rectImage.height = 15;
    } else if (id == 3) {
        // PlaySound(LoadSound("sfx/meldrop-shot.wav"));
        image = LoadTexture("images/effect-spear.png");
        imageSize = 1;
        rectImage.width = 15;
        rectImage.height = 15;
    }
    
    
    rect.width = rectImage.width*SCALE;
    rect.height = rectImage.height*SCALE;
    cx = rect.x + rect.width/2;
    cy = rect.y + rect.height/2;
}

bool Effect::update(std::vector<Block> Blocks, Flamingo &player, std::vector<Item> &itens, std::vector<Enemy> &enemies) {
    bool value;
    switch(id) {
        case(1):
            value = meldropShot(Blocks, player);
            break;
        case(2):
            value = transmutation(itens);
            break;
        case(3):
            value = spear(enemies, itens);
            break;
    }
    
    rect.x += vx;
    rect.y += vy;
    cx += vx;
    cy += vy;
    if (tick % 10 == 0) {
        imageCount += 1;
        if (imageCount >= imageSize) {
            imageCount = 0;
        }
    }
    
    if (timer <= 0) {
        return true;
    }
    
    timer -= 1;
    tick += 1;
    return value;
}

bool Effect::meldropShot(std::vector<Block> Blocks, Flamingo &player) {
    if (tick % 5 == 0) {
        int sizeBT = Blocks.size();
        closeBlocks.clear();
        for (int i = 0; i < sizeBT; i++) {
            if (Blocks[i].background) {
                continue;
            }
            int dx = abs(Blocks[i].cx - cx);
            if (dx < Blocks[i].rect.width*2) {
                int dy = abs(Blocks[i].cy - cy);
                if (dy < Blocks[i].rect.height*2) {
                    closeBlocks.push_back(i);
                }
            }
        }
    }

    int sizeB = closeBlocks.size();
    for (int i = 0; i < sizeB; i++) {
        if (GenericColision(rect, Blocks[closeBlocks[i]].rect)) {
            return true;
        }
    }

    if (GenericColision(player.rect, rect)) {
        int q = 0;
        for(char type : {'H', 'R', 'P', 'C', 'W'}) {
            if (dmg[q] > 0) {
                player.Health(-dmg[q], type);
            }
            q++;
        }
        return true;
    }

    return false;
}

bool Effect::transmutation(std::vector<Item> &itens) {
    if (tick % 5 == 0) {
        int sizeI = itens.size();
        closeItens.clear();
        for (int i = 0; i < sizeI; i++) {
            int dx = abs(itens[i].cx - cx);
            if (dx < itens[i].rect.width*2) {
                int dy = abs(itens[i].cy - cy);
                if (dy < itens[i].rect.height*2) {
                    closeItens.push_back(i);
                }
            }
        }
    }

    int sizeCI = closeItens.size();
    for (int i = 0; i < sizeCI; i++) {
        Item target = itens[closeItens[i]];
        if (GenericColision(rect, target.rect)) {
            Item result;
            if (target.name == "food-banana") {
                result = Item(target.rect.x, target.rect.y, "food-pear", SCALE, 'F');
            } else if (target.name == "food-pear") {
                result = Item(target.rect.x, target.rect.y, "food-blueberry", SCALE, 'F');
            } else if (target.name == "food-blueberry") {
                result = Item(target.rect.x, target.rect.y, "food-pepper", SCALE, 'F');
            } else if (target.name == "food-pepper") {
                result = Item(target.rect.x, target.rect.y, "food-orange", SCALE, 'F');
            } else if (target.name == "food-orange") {
                result = Item(target.rect.x, target.rect.y, "food-banana", SCALE, 'F');

            } else if (target.name == "Hshard-hope") {
                result = Item(target.rect.x, target.rect.y, "Hshard-resilience", SCALE, 'H');
            } else if (target.name == "Hshard-resilience") {
                result = Item(target.rect.x, target.rect.y, "Hshard-power", SCALE, 'H');
            } else if (target.name == "Hshard-power") {
                result = Item(target.rect.x, target.rect.y, "Hshard-courage", SCALE, 'H');
            } else if (target.name == "Hshard-courage") {
                result = Item(target.rect.x, target.rect.y, "Hshard-wisdom", SCALE, 'H');
            } else if (target.name == "Hshard-wisdom") {
                result = Item(target.rect.x, target.rect.y, "Hshard-hope", SCALE, 'H');

            } else if (target.name == "Pshard-wind") {
                result = Item(target.rect.x, target.rect.y, "Pshard-party", SCALE, 'P');
            } else if (target.name == "Pshard-party") {
                result = Item(target.rect.x, target.rect.y, "Pshard-fun", SCALE, 'P');
            } else if (target.name == "Pshard-fun") {
                result = Item(target.rect.x, target.rect.y, "Pshard-hard", SCALE, 'P');
            } else if (target.name == "Pshard-hard") {
                result = Item(target.rect.x, target.rect.y, "Pshard-eloise", SCALE, 'P');
            } else if (target.name == "Pshard-eloise") {
                result = Item(target.rect.x, target.rect.y, "Pshard-wind", SCALE, 'P');
            }
            itens[closeItens[i]] = result;
            return true;
        }
    }
    return false;
}

bool Effect::spear(std::vector<Enemy> &enemies, std::vector<Item> &itens) {
    if (tick % 5 == 0) {
        int sizeE = enemies.size();
        closeEnemies.clear();
        for (int i = 0; i < sizeE; i++) {
            int dx = abs(enemies[i].cx - cx);
            if (dx < enemies[i].rect.width*2) {
                int dy = abs(enemies[i].cy - cy);
                if (dy < enemies[i].rect.height*2) {
                    closeEnemies.push_back(i);
                }
            }
        }
    }

    int sizeE = closeEnemies.size();
    for (int i = 0; i < sizeE; i++) {
        Enemy temp = enemies[closeEnemies[i]];
        if (GenericColision(temp.rect, rect)) {
            Item deathCoin(temp.rect.x, temp.rect.y, "coin-death", SCALE, 'C');
            itens.push_back(deathCoin);
            auto it = std::next(enemies.begin(), closeEnemies[i]);
            enemies.erase(it);
            return true;
        }
    }
    return false;
}