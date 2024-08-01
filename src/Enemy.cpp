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
        rect.y += 1*SCALE;

        id = 1;
        patrol1 = rect.x -20*SCALE;
        patrol2 = rect.x +20*SCALE;
        vx = 1*SCALE;
        vy = 0;
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


        ground = grounder;
        HBFeet = {rect.x, rect.y+(rect.height+1)*SCALE, rect.width, 2};
        vision = {rect.x+(rect.width+1)*SCALE, rect.y+(rect.height*SCALE/2+1)*SCALE, 2, 2};
        behavior = 0; // *90º clock-wise
        rect.y = ground.rect.y - 1*SCALE - rect.height*SCALE;
    } else if (name == "butterfly") {
        images.push_back(LoadTexture("images/enemy-butterfly.png"));
        imageSize = 2;
        rect.width = 11;
        rect.height = 11;
        dmgs[2] = 1;

        id = 3;
        vx = 0;
        vy = 0;
        angle = 0;
        behavior = 0;
        orbit.x = x;
        orbit.y = y;
    } else if (name == "crab") {
        images.push_back(LoadTexture("images/enemy-crab.png"));
        imageSize = 4;
        dmgs[3] = 1;

        id = 4;
        behavior = 0;

        vx = 2;
        vy = 0;

        rect.width = 9;
        rect.height = 9;
        rect.y += 2*SCALE;
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
        rect.y -= 2*SCALE;
        rect.width = 13;
        rect.height = 13;

        int j = 0;
        for (; j < sizeB; j++) {
            ground = map[j];
            if (ground.rect.x == rect.x and ground.rect.y >= rect.y+(13-1)*SCALE) {
                break;
            }
        }

        Block leftGround = ground;
        patrol1 = ground.rect.x;
        int k = j;
        while (true) {
            k--;
            Block newLeftGround = map[k];
            if (newLeftGround.rect.y == leftGround.rect.y and newLeftGround.rect.x+newLeftGround.rect.width*SCALE >= leftGround.rect.x) {
                leftGround = newLeftGround;
            } else {
                break;
            }
        }
        patrol1 = leftGround.rect.x;


        Block rightGround = ground;
        patrol2 = ground.rect.x+ground.rect.width*SCALE;
        k = j;
        while (true) {
            k++;
            Block newRightGround = map[k];
            if (newRightGround.rect.y == rightGround.rect.y and newRightGround.rect.x <= rightGround.rect.x+rightGround.rect.width*SCALE) {
                rightGround = newRightGround;
            } else {
                break;
            }
        }
        patrol2 = rightGround.rect.x+rightGround.rect.width*SCALE;
    } else if (name == "meldrop") {
        images.push_back(LoadTexture("images/enemy-meldrop.png"));
        imageSize = 2;
        rect.width = 13;
        rect.height = 13;
        dmgs[4] = 1;

        id = 5;
        vx = 0;
        vy = 0;
        angle = 0;
        behavior = 0;
    }
    cx = x + rect.width*SCALE/2;
    cy = y + rect.height*SCALE/2;
}

void Enemy::update(std::vector<Block> map, Flamingo &player, std::vector<Effect> &effects) {
    switch(id) {
        case (1):
            bee();
            break;
        case(2):
            snail(map);
            break;
        case(3):
            butterfly(map, player);
            break;
        case(4):
            crab(player);
            break;
        case(5):
            meldrop(player, effects);
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
    } else if (rect.x+rect.width*SCALE > patrol2) {
        vx = -vx;
    }
    rect.x += vx;
    cx += vx;

    if (GenericColision(border1.rect, rect, SCALE) or GenericColision(border2.rect, rect, SCALE)) {
        vx = -vx;
    }
}

void Enemy::snail(std::vector<Block> map) {
    getCloseBlocks(map);
    if (behavior == 0) {
        rect.y = ground.rect.y - (rect.height)*SCALE;
        rect.x += vx;
        cx += vx;
        HBFeet = {rect.x, rect.y+(rect.height+1)*SCALE, rect.width, 2};
        vision = {rect.x+(rect.width+1)*SCALE, rect.y+(rect.height/2)*SCALE, 2, 2};
    } else if (behavior == 1) {
        rect.y -= vx;
        cy -= vx;
        rect.x = ground.rect.x - (rect.height)*SCALE;
        HBFeet = {rect.x+(rect.height)*SCALE, rect.y, 2, rect.width};
        vision = {rect.x+(rect.height/2)*SCALE, rect.y-1*SCALE, 2, 2};
    } else if (behavior == 2) {
        rect.y = ground.rect.y+(ground.rect.height)*SCALE;
        rect.x -= vx;
        cx -= vx;
        HBFeet = {rect.x, rect.y-2*SCALE, rect.width, 2};
        vision = {rect.x-1*SCALE, rect.y+(rect.height/2)*SCALE, 2, 2};
    } else if (behavior == 3) {
        rect.y += vx;
        cy += vx;
        rect.x = ground.rect.x+(ground.rect.width)*SCALE;
        HBFeet = {rect.x-3*SCALE, rect.y, 2, rect.width};
        vision = {rect.x+(rect.height/2)*SCALE, rect.y+(rect.width+1)*SCALE, 2, 2};
    }

    int sizeB = closeBlocks.size();
    for (int i = 0; i < sizeB; i++) {
        Block temp = map[closeBlocks[i]];
        if (GenericColision(rect, temp.rect, SCALE) and GenericColision(vision, temp.rect, SCALE)) {
            if (behavior == 0) {
                ground = temp;
                behavior = 1;
            } else if (behavior == 1) {
                ground = temp;
                behavior = 2;
            } else if (behavior == 2) {
                ground = temp;
                behavior = 3;
            } else if (behavior == 3) {
                ground = temp;
                behavior = 0;
            } else {
                DrawText("UNEXPECTED SNAIL BEHAVIOR", GetScreenWidth() - 520, 40, 20, RED);
            }
        }
        if (GenericColision(HBFeet, temp.rect, SCALE)) {
            if (behavior == 0 and temp.rect.x > ground.rect.x) {
                ground = temp;
            } else if (behavior == 1 and temp.rect.y < ground.rect.y) {
                ground = temp;
            } else if (behavior == 2 and temp.rect.x < ground.rect.x) {
                ground = temp;
            } else if (behavior == 3 and temp.rect.y > ground.rect.y) {
                ground = temp;
            }
        }
    }
    if (!GenericColision(HBFeet, ground.rect, SCALE)) {
        behavior -= 1;
        if (behavior < 0) {
            behavior = 3;
        }
        if (behavior == 3) {
            rect.y += 2*SCALE;
            cy += 2*SCALE;
        } else if (behavior == 2) {
            rect.x -= 2*SCALE;
            cx -= 2*SCALE;
        } else if (behavior == 1) {
            rect.y -= 2*SCALE;
            cy -= 2*SCALE;
        } else if (behavior == 0) {
            rect.x += 2*SCALE;
            cx += 2*SCALE;
        }
    }

    
}

void Enemy::butterfly(std::vector<Block> map, Flamingo &player) {
    getCloseBlocks(map);
    if (behavior == 0) {
        angle += 3;
        if (angle >= 360) {
            angle = 0;
        }
        float radians = angle*3.14159/180; 
        rect.x = orbit.x + 25*SCALE*std::cos(radians);
        rect.y = orbit.y + 25*SCALE*std::sin(radians);
        cx = rect.x + rect.width*SCALE/2;
        cy = rect.y + rect.height*SCALE/2;

        int sizeB = closeBlocks.size();
        for (int i = 0; i < sizeB; i++) {
            if (GenericColision(map[closeBlocks[i]].rect, rect, SCALE)) {
                orbit.x -= 1*SCALE*std::cos(radians);
                orbit.y -= 1*SCALE*std::sin(radians);
            }
        }

        if (abs(player.rect.x-rect.x) + abs(player.rect.y-rect.y) < 60*SCALE) { // fun-mode: Butterfly-chase, change < to >
            behavior = 1;
        }
    } else if (behavior == 1) {
        angle -= 3;
        if (angle < 0) {
            behavior = 50;
            angle = 0;
        }
    } else if (behavior >= 2) {
        if (player.rect.x > rect.x) {
            vx = 3*SCALE;
        } else if (rect.x > player.rect.x) {
            vx = -3*SCALE;
        }
        if (player.rect.y > rect.y) {
            vy = 3*SCALE;
        } else if (rect.y > player.rect.y) {
            vy = -3*SCALE;
        }

        int sizeB = closeBlocks.size();
        rect.x += vx;
        cx += vx;
        for (int i = 0; i < sizeB; i++) {
            if (GenericColision(map[closeBlocks[i]].rect, rect, SCALE)) {
                rect.x -= vx;
                cx -= vx;
                break;
            }
        }
        rect.y += vy;
        cy += vy;
        for (int i = 0; i < sizeB; i++) {
            if (GenericColision(map[closeBlocks[i]].rect, rect, SCALE)) {
                rect.y -= vy;
                cy -= vy;
                break;
            }
        }
        behavior -= 1;
        if (behavior == 2) {
            orbit.x = rect.x;
            orbit.y = rect.y-25*SCALE;
            angle = 90;
            behavior = 0;
        }
    }
    
}

void Enemy::crab(Flamingo &player) {
    rect.x += vx;
    cx += vx;
    if (behavior == 0) {
        if (rect.x < patrol1) {
            vx = 2;
        }
        if (rect.x+rect.width*SCALE > patrol2) {
            vx = -2;
        }
        if (abs(player.rect.x-rect.x) + abs(player.rect.y-rect.y) < 80*SCALE) {
            behavior = 1;
            vx = 4;
        }
    } else if (behavior == 1) {
        if (player.rect.x > rect.x) {
            vx = 4;
        } else {
            vx = -4;
        }
        if (abs(player.rect.x-rect.x) + abs(player.rect.y-rect.y) > 80*SCALE) {
            behavior = 0;
            vx = 2;
        }
    }
    if (rect.x+rect.width*SCALE > patrol2) {
        rect.x = patrol2 - rect.width*SCALE;
    }
    if (rect.x < patrol1) {
        rect.x = patrol1;
    }
    if (GenericColision(border1.rect, rect, SCALE) or GenericColision(border2.rect, rect, SCALE)) {
        vx = -vx;
    }
}

void Enemy::meldrop(Flamingo &player, std::vector<Effect> &effects) {
    if (behavior == 0) {
        if (abs(cx - player.cx) + abs(cy - player.cy) < 120*SCALE) {
            behavior = 1;
        }
    } else if (behavior < 90) {
        if (abs(cx - player.cx) + abs(cy - player.cy) > 120*SCALE) {
            behavior = 0;
        }
        behavior += 1;
    } else if (behavior >= 90) {
        Vector2 center = {cx, cy};
        Vector2 direction;
        float angle = std::atan2(player.cx - cx, player.cy - cy);
        direction.x = std::sin(angle)*5;
        direction.y = std::cos(angle)*5;
        int damager[5] = {0, 0, 0, 0, 1};
        Effect tiro(center, direction, 120, 1, damager, SCALE);
        effects.push_back(tiro);
        behavior = 0;
    }
}

void Enemy::getCloseBlocks(std::vector<Block> map) {
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
}