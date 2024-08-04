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
        rectImage.width = 12;
        rectImage.height = 13;
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
            if (rect.y+rectImage.height*SCALE > bloquinho.rect.y and bloquinho.rect.y+bloquinho.rect.height > rect.y) {
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
        rectImage.width = 12;
        rectImage.height = 13;
        dmgs[1] = 2;

        id = 2;
        vx = 1;
        vy = 0;


        ground = grounder;
        HBFeet = {rect.x, rect.y+(rectImage.height+1)*SCALE, rectImage.width*SCALE, (float) 2*SCALE};
        vision = {rect.x+(rectImage.width+1)*SCALE, rect.y+(rectImage.height*SCALE/2+1)*SCALE, (float) 2*SCALE, (float) 2*SCALE};
        behavior = 0; // *90º clock-wise
        rect.y = ground.rect.y - 1*SCALE - rectImage.height*SCALE;
    } else if (name == "butterfly") {
        images.push_back(LoadTexture("images/enemy-butterfly.png"));
        imageSize = 2;
        rectImage.width = 11;
        rectImage.height = 11;
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

        rectImage.width = 9;
        rectImage.height = 9;
        rect.y += 2*SCALE;
        int sizeB = map.size();
        for (int i = 0; i < sizeB; i++) {
            Block bloquinho = map[i];
            if (rect.y+rectImage.height*SCALE > bloquinho.rect.y and bloquinho.rect.y+bloquinho.rect.height > rect.y) {
                if ((border2.SCALE == 0) or (bloquinho.rect.x > rect.x and bloquinho.rect.x < border2.rect.x)) {
                    border2 = bloquinho;
                }
                if ((border1.SCALE == 0) or (bloquinho.rect.x < rect.x and bloquinho.rect.x > border1.rect.x)) {
                    border1 = bloquinho;
                }
            }
        }
        rect.y -= 2*SCALE;
        rectImage.width = 13;
        rectImage.height = 13;

        ground = grounder;
        int j = 0;
        for (; j < sizeB; j++) { // gambiarra
            Block temp = map[j];
            if (ground.rect.x == temp.rect.x and ground.rect.y == temp.rect.y) {
                break;
            }
        }

        Block leftGround = ground;
        patrol1 = ground.rect.x;
        int k = j;
        while (true) {
            k--;
            Block newLeftGround = map[k];
            if (newLeftGround.rect.y == leftGround.rect.y and newLeftGround.rect.x+newLeftGround.rect.width >= leftGround.rect.x) {
                leftGround = newLeftGround;
            } else {
                break;
            }
        }
        patrol1 = leftGround.rect.x;


        Block rightGround = ground;
        patrol2 = ground.rect.x+ground.rectImage.width*SCALE;
        k = j;
        while (true) {
            k++;
            Block newRightGround = map[k];
            if (newRightGround.rect.y == rightGround.rect.y and newRightGround.rect.x <= rightGround.rect.x+rightGround.rect.width) {
                rightGround = newRightGround;
            } else {
                break;
            }
        }
        patrol2 = rightGround.rect.x+rightGround.rect.width;
    } else if (name == "meldrop") {
        images.push_back(LoadTexture("images/enemy-meldrop.png"));
        imageSize = 2;
        rectImage.width = 13;
        rectImage.height = 13;
        dmgs[4] = 1;

        id = 5;
        vx = 0;
        vy = 0;
        angle = 0;
        behavior = 0;
    }
    
    
    rect.width = rectImage.width*SCALE;
    rect.height = rectImage.height*SCALE;
    cx = rect.x + rect.width/2;
    cy = rect.y + rect.height/2;
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
    } else if (rect.x+rect.width > patrol2) {
        vx = -vx;
    }
    rect.x += vx;
    cx += vx;

    if (GenericColision(border1.rect, rect) or GenericColision(border2.rect, rect)) {
        vx = -vx;
    }
}

void Enemy::snail(std::vector<Block> map) {
    getCloseBlocks(map);
    cx = rect.x+rect.width/2;
    cy = rect.y+rect.height/2;
    if (behavior == 0) {
        rect.y = ground.rect.y - rect.height;
        rect.x += vx;
        HBFeet = {rect.x, rect.y+(rect.height-SCALE), rect.width, (float) 2*SCALE};
        vision.x = rect.x+(rect.width+SCALE);
        vision.y = rect.y+(rect.height/2);
    } else if (behavior == 1) {
        rect.y -= vx;
        rect.x = ground.rect.x - rect.height;
        HBFeet = {rect.x+rect.height, rect.y, (float) 2*SCALE, rect.width};
        vision.x = rect.x+(rect.height/2);
        vision.y = rect.y-SCALE;
    } else if (behavior == 2) {
        rect.y = ground.rect.y+ground.rect.height;
        rect.x -= vx;
        HBFeet = {rect.x, (rect.y-3*SCALE), rect.width, (float) 2*SCALE};
        vision.x = rect.x-SCALE;
        vision.y = rect.y+(rect.height/2);
    } else if (behavior == 3) {
        rect.y += vx;
        rect.x = ground.rect.x+ground.rect.width;
        HBFeet = {(rect.x-3*SCALE), rect.y, (float) 2*SCALE, rect.width};
        vision.x = rect.x+(rect.height/2);
        vision.y = rect.y+(rect.width+SCALE);
    }

    int sizeB = closeBlocks.size();
    for (int i = 0; i < sizeB; i++) {
        Block temp = map[closeBlocks[i]];
        if (temp.name == "spike" or temp.background or temp.secret) {
            continue;
        }
        if (GenericColision(vision, temp.rect)) {
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
            return;
        }
        if (GenericColision(HBFeet, temp.rect)) {
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

    if (!GenericColision(HBFeet, ground.rect)) {
        behavior -= 1;
        if (behavior < 0) {
            behavior = 3;
        }
        if (behavior == 3) {
            rect.y += 2*SCALE;
        } else if (behavior == 2) {
            rect.x -= 2*SCALE;
        } else if (behavior == 1) {
            rect.y -= 2*SCALE;
        } else if (behavior == 0) {
            rect.x += 2*SCALE;
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
            if (GenericColision(map[closeBlocks[i]].rect, rect)) {
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
            if (GenericColision(map[closeBlocks[i]].rect, rect)) {
                rect.x -= vx;
                cx -= vx;
                break;
            }
        }
        rect.y += vy;
        cy += vy;
        for (int i = 0; i < sizeB; i++) {
            if (GenericColision(map[closeBlocks[i]].rect, rect)) {
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
        if (rect.x+rect.width > patrol2) {
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
    if (rect.x+rect.width > patrol2) {
        rect.x = patrol2 - rect.width;
        cx = rect.x+rect.width/2;
    }
    if (rect.x < patrol1) {
        rect.x = patrol1;
        cx = rect.x+rect.width/2;
    }
    if (GenericColision(border1.rect, rect) or GenericColision(border2.rect, rect)) {
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
    if (tick % 5 == 0) {
        closeBlocks.clear();
        int sizeB = map.size();
        for (int i = 0; i < sizeB; i++) {
            if (map[i].background) {
                continue;
            }
            int dx = abs(map[i].cx - cx);
            if (dx < map[i].rect.width*2) {
                int dy = abs(map[i].cy - cy);
                if (dy < map[i].rect.height*2) {
                    closeBlocks.push_back(i);
                }
            }
        }
    }
}