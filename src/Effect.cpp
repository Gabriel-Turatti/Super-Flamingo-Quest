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
        rect.width = 6;
        rect.height = 6;
        cx = rect.x + rect.width*SCALE/2;
        cy = rect.y + rect.height*SCALE/2;
    }
}

bool Effect::update(std::vector<Block> map, Flamingo &player) {
    if (tick % 10 == 0) {
        imageCount += 1;
        if (imageCount >= imageSize) {
            imageCount = 0;
        }
    }

    rect.x += vx;
    rect.y += vy;
    cx += vx;
    cy += vy;

    if (timer <= 0) {
        return true;
    }

    if (timer % 5 == 0) {
        int sizeBT = map.size();
        closeBlocks.clear();
        for (int i = 0; i < sizeBT; i++) {
            if (map[i].background) {
                continue;
            }
            int dx = abs(map[i].cx - cx);
            if (dx < map[i].rect.width*2*SCALE) {
                int dy = abs(map[i].cy - cy);
                if (dy < map[i].rect.height*2*SCALE) {
                    closeBlocks.push_back(i);
                }
            }
        }
    }

    int sizeB = closeBlocks.size();
    for (int i = 0; i < sizeB; i++) {
        if (GenericColision(rect, map[closeBlocks[i]].rect, SCALE)) {
            return true;
        }
    }

    if (GenericColision(player.rect, rect, SCALE)) {
        int q = 0;
        for(char type : {'H', 'R', 'P', 'C', 'W'}) {
            if (dmg[q] > 0) {
                player.Health(-dmg[q], type);
            }
            q++;
        }
        return true;
    }

    timer -= 1;
    return false;
}