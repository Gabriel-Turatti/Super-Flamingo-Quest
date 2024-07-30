#include "../header/Enemy.hpp"


Enemy::Enemy(float x, float y, std::string namer, int imagescale, std::vector<Block> map, int ticker, Block grounder = Block()) {
    rect.x = x;
    rect.y = y;
    name = namer;
    SCALE = imagescale;
    tick = ticker;
    if (name == "bee") {
        images.push_back(LoadTexture("images/enemy-bee.png"));
        imageSize = 2;
        rect.width = 11;
        rect.height = 11;
        dmgs[0] = 1;


        id = 1;
        patrol1 = rect.x -20*SCALE;
        patrol2 = rect.x +20*SCALE;
        vx = 1*SCALE;
        vy = 0;
        cx = x + rect.width*SCALE/2;
        cy = y + rect.height*SCALE/2;
        int sizeB = map.size();
        for (int i = 0; i < sizeB; i++) {
            Block bloquinho = map[i];
            if (rect.y+rect.height*SCALE > bloquinho.rect.y and bloquinho.rect.y+bloquinho.rect.height*SCALE > rect.y) {
                if ((border2.SCALE == 0) or (bloquinho.rect.x > rect.x and bloquinho.rect.x < border2.rect.x)) {
                    border2 = bloquinho;
                }
                if ((border1.SCALE == 0) or (bloquinho.rect.x < rect.x and bloquinho.rect.x > border1.rect.x)) {
                    border1 = bloquinho;
                }
            }
        }
    } else if (name == "snail") {
        images.push_back(LoadTexture("images/enemy-snail.png"));
        imageSize = 3;
        rect.width = 12;
        rect.height = 13;
        dmgs[1] = 2;

        id = 2;
        vx = 1;
        vy = 0;
        cx = x + rect.width*SCALE/2;
        cy = y + rect.height*SCALE/2;


        ground = grounder;
        HBFeet = {rect.x, rect.y+(rect.height+1)*SCALE, rect.width, 2};
        vision = {rect.x+(rect.width+1)*SCALE, rect.y+(rect.height*SCALE/2+1)*SCALE, 2, 2};
        direction = 0; // *90º clock-wise
        rect.y = ground.rect.y - 1*SCALE - rect.height*SCALE;
    }
}

void Enemy::update(std::vector<Block> map) {
    switch(id) {
        case (1):
            bee();
            break;
        case(2):
            snail(map);
            break;
    }
    tick += 1;
    if (tick % 10 == 0) {
        imageCount += 1;
        if (imageCount >= imageSize) {
            imageCount = 0;
        }
    }
}

void Enemy::bee() {
    if (rect.x < patrol1) {
        vx = -vx;
    } else if (rect.x > patrol2) {
        vx = -vx;
    }
    rect.x += vx;
    cx += vx;

    if (GenericColision(border1.rect, rect, SCALE) or GenericColision(border2.rect, rect, SCALE)) {
        vx = -vx;
    }
}

void Enemy::snail(std::vector<Block> map) {
    if (tick % 10 == 0) {
        closeBlocks.clear();
        int sizeB = map.size();
        for (int i = 0; i < sizeB; i++) {
            if (map[i].background) {
                continue;
            }
            int dx = abs(map[i].cx - cx);
            if (dx < rect.width*2*SCALE) {
                int dy = abs(map[i].cy - cy);
                if (dy < rect.height*2*SCALE) {
                    closeBlocks.push_back(i);
                }
            }
        }
    }

    if (direction == 0) {
        rect.y = ground.rect.y - (rect.height+1)*SCALE;
        rect.x += vx;
        cx += vx;
        HBFeet = {rect.x, rect.y+(rect.height+1)*SCALE, rect.width, 2};
        vision = {rect.x+(rect.width+1)*SCALE, rect.y+(rect.height/2)*SCALE, 2, 2};
    } else if (direction == 1) {
        rect.y -= vx;
        cy -= vx;
        rect.x = ground.rect.x - (rect.height+1)*SCALE;
        HBFeet = {rect.x+(rect.height)*SCALE, rect.y, 2, rect.width};
        vision = {rect.x+(rect.height/2)*SCALE, rect.y-1*SCALE, 2, 2};
    } else if (direction == 2) {
        rect.y = ground.rect.y+(ground.rect.height+1)*SCALE;
        rect.x -= vx;
        cx -= vx;
        HBFeet = {rect.x, rect.y-2*SCALE, rect.width, 2};
        vision = {rect.x-1*SCALE, rect.y+(rect.height/2)*SCALE, 2, 2};
    } else if (direction == 3) {
        rect.y += vx;
        cy += vx;
        rect.x = ground.rect.x+(ground.rect.width+1)*SCALE;
        HBFeet = {rect.x-3*SCALE, rect.y, 2, rect.width};
        vision = {rect.x+(rect.height/2)*SCALE, rect.y+(rect.width+1)*SCALE, 2, 2};
    }

    int sizeB = closeBlocks.size();
    for (int i = 0; i < sizeB; i++) {
        Block temp = map[closeBlocks[i]];
        if (GenericColision(rect, temp.rect, SCALE) and GenericColision(vision, temp.rect, SCALE)) {
            if (direction == 0) {
                ground = temp;
                direction = 1;
            } else if (direction == 1) {
                ground = temp;
                direction = 2;
            } else if (direction == 2) {
                ground = temp;
                direction = 3;
            } else if (direction == 3) {
                ground = temp;
                direction = 0;
            } else {
                DrawText("UNEXPECTED SNAIL BEHAVIOR", GetScreenWidth() - 520, 40, 20, RED);
            }
        }
        if (GenericColision(HBFeet, temp.rect, SCALE)) {
            if (direction == 0 and temp.rect.x > ground.rect.x) {
                ground = temp;
            } else if (direction == 1 and temp.rect.y < ground.rect.y) {
                ground = temp;
            } else if (direction == 2 and temp.rect.x < ground.rect.x) {
                ground = temp;
            } else if (direction == 3 and temp.rect.y > ground.rect.y) {
                ground = temp;
            }
        }
    }
    if (!GenericColision(HBFeet, ground.rect, SCALE)) {
        direction -= 1;
        if (direction < 0) {
            direction = 3;
        }
        if (direction == 3) {
            rect.y += 2*SCALE;
            cy += 2*SCALE;
        } else if (direction == 2) {
            rect.x -= 2*SCALE;
            cx -= 2*SCALE;
        } else if (direction == 1) {
            rect.y -= 2*SCALE;
            cy -= 2*SCALE;
        } else if (direction == 0) {
            rect.x += 2*SCALE;
            cx += 2*SCALE;
        }
    }

    
}