#include "../header/Enemy.hpp"


Enemy::Enemy(float x, float y, std::string namer, int imagescale, std::map<int, std::map<int, Block>> Blocks, int ticker, int i, int j) {
    rect.x = x;
    rect.y = y;
    name = namer;
    SCALE = imagescale;
    tick = ticker;
    if (tick == 0) {
        if (name == "bee") {
            images.push_back(LoadTexture("images/enemy-bee.png"));
            rectImage.width = 12;
            rectImage.height = 13;
        } else if (name == "snail") {
            images.push_back(LoadTexture("images/enemy-snail.png"));
            rectImage.width = 12;
            rectImage.height = 13;
        } else if (name == "butterfly") {
            images.push_back(LoadTexture("images/enemy-butterfly.png"));
            rectImage.width = 11;
            rectImage.height = 11;
        } else if (name == "crab") {
            images.push_back(LoadTexture("images/enemy-crab.png"));
            rectImage.width = 13;
            rectImage.height = 13;
        } else if (name == "meldrop") {
            images.push_back(LoadTexture("images/enemy-meldrop.png"));
            rectImage.width = 13;
            rectImage.height = 13;
        }
    } else {
        if (name == "bee") {
            images.push_back(LoadTexture("images/enemy-bee.png"));
            imageSize = 2;
            rectImage.width = 12;
            rectImage.height = 13;
            dmgs[0] = 1;
            rect.y += 1*SCALE;

            id = 1;
            patrol1 = rect.x -30*SCALE;
            patrol2 = rect.x +30*SCALE;
            vx = 1*SCALE;
            vy = 0;

            if (Blocks.count(i) > 0) {
                for (int k = j; k > 0; k--) {
                    if (Blocks[i].count(k) > 0 and !Blocks[i][k].background and Blocks[i][k].rect.x+Blocks[i][k].rect.width > patrol1) {
                        border1 = Blocks[i][k];
                        patrol1 = border1.rect.x+border1.rect.width-SCALE;
                        break;
                    }
                }
            }
            if (Blocks.count(i-1) > 0) {
                for (int k = j; k > 0; k--) {
                    if (Blocks[i-1].count(k) > 0 and !Blocks[i-1][k].background and Blocks[i-1][k].rect.x+Blocks[i-1][k].rect.width > patrol1) {
                        border1 = Blocks[i-1][k];
                        patrol1 = border1.rect.x+border1.rect.width;
                        break;
                    }
                }
            }

            if (Blocks.count(i) > 0) {
                int sizeB = Blocks[i].size();
                for (int k = j+1; sizeB > 0; k++) {
                    if (Blocks[i].count(k) > 0 and !Blocks[i][k].background and Blocks[i][k].rect.x < patrol2) {
                        border2 = Blocks[i][k];
                        patrol2 = border2.rect.x;
                        break;
                    }
                    sizeB--;
                }
            }
            if (Blocks.count(i-1) > 0) {
                int sizeB = Blocks[i-1].size();
                for (int k = j+1; sizeB > 0; k++) {
                    if (Blocks[i-1].count(k) > 0 and !Blocks[i-1][k].background and Blocks[i-1][k].rect.x < patrol2) {
                        border2 = Blocks[i-1][k];
                        patrol2 = border2.rect.x;
                        break;
                    }
                    sizeB--;
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


            if (Blocks.count(i) > 0 and Blocks[i].count(j) > 0) {
                ground = Blocks[i][j];
            } else {
                ground = Blocks[i][j-1];
            }
            HBFeet = {rect.x, rect.y+(rectImage.height+1)*SCALE, rectImage.width*SCALE, (float) 2*SCALE};
            vision = {rect.x+(rectImage.width+1)*SCALE, rect.y+(rectImage.height*SCALE/2+1)*SCALE, (float) 2*SCALE, (float) 2*SCALE};
            behavior = 0; // *90º clock-wise
            rect.y = ground.rect.y - rectImage.height*SCALE + SCALE;
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

            rectImage.width = 13;
            rectImage.height = 13;

            if (Blocks.count(i+1) == 0) {
                tick = 0;
                return;
            }

            border1 = Blocks[i+1][j];
            for (int k = j; k >= 0; k--) {
                if (Blocks[i+1].count(k) > 0 and !Blocks[i+1][k].background) {
                    border1 = Blocks[i+1][k];
                    continue;
                }
                if (Blocks[i+1].count(k-1) and Blocks[i+1][k-1].rect.x+Blocks[i+1][k-1].rect.width > border1.rect.x and !Blocks[i+1][k-1].background) {
                    border1 = Blocks[i+1][k-1];
                    k--;
                    continue;
                }
                break;
            }
            border2 = Blocks[i+1][j];
            int k = j;
            while (true) {
                if (Blocks[i+1].count(k) > 0 and !Blocks[i+1][k].background) {
                    border2 = Blocks[i+1][k];
                    k++;
                    continue;
                }
                if (Blocks[i+1].count(k+1) > 0 and border2.rect.x+border2.rect.width > Blocks[i+1][k+1].rect.x and !Blocks[i+1][k+1].background) {
                    k++;
                    continue;
                }
                break;
            }
            
            patrol1 = border1.rect.x;
            patrol2 = border2.rect.x+border2.rect.width;




            for(auto const &ent1 : Blocks[i]) {
                if (ent1.first > j) {
                    if (ent1.second.rect.x < patrol2 and !ent1.second.background) {
                        patrol2 = ent1.second.rect.x;
                        break;
                    }
                }
            }

            if (Blocks.count(i-1)) {
                for(auto const &ent1 : Blocks[i-1]) {
                    if (ent1.first > j) {
                        if (ent1.second.rect.x < patrol2 and !ent1.second.background and ent1.second.rect.y+ent1.second.rect.height > border2.rect.y) {
                            patrol2 = ent1.second.rect.x;
                            break;
                        }
                    }
                }
            }




            if (Blocks.count(i) > 0) {
                for (k = j; k >= 0; k--) {
                    if (Blocks[i].count(k) > 0 and !Blocks[i][k].background) {
                        if (Blocks[i][k].rect.x+Blocks[i][k].rect.width > patrol1) {
                            patrol1 = Blocks[i][k].rect.x+Blocks[i][k].rect.width;
                            break;
                        }
                        if (Blocks[i][k].rect.x+Blocks[i][k].rect.width < patrol1) {
                            break;
                        }
                    }
                }
            }


            if (Blocks.count(i-1) > 0) {
                for (k = j; k >= 0; k--) {
                    if (Blocks[i-1].count(k) > 0 and Blocks[i-1][k].rect.x+Blocks[i-1][k].rect.width > patrol1 and Blocks[i-1][k].rect.y+Blocks[i-1][k].rect.height > rect.y and !Blocks[i-1][k].background) {
                        patrol1 = Blocks[i-1][k].rect.x+Blocks[i-1][k].rect.width;
                        break;
                    }
                }
            }

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
    }
    
    SetTextureWrap(images[0], TEXTURE_WRAP_CLAMP);
    
    rect.width = rectImage.width*SCALE;
    rect.height = rectImage.height*SCALE;
    cx = rect.x + rect.width/2;
    cy = rect.y + rect.height/2;
}

Enemy::Enemy() {SCALE = 0;}

void Enemy::update(std::vector<Block> Blocks, Flamingo* player, std::vector<Effect> &effects) {
    if (tick == 0) {
        return;
    }
    switch(id) {
        case (1):
            bee();
            break;
        case(2):
            snail(Blocks);
            break;
        case(3):
            butterfly(Blocks, player);
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
}

void Enemy::snail(std::vector<Block> Blocks) {
    getCloseBlocks(Blocks);
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
        Block temp = Blocks[closeBlocks[i]];
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

void Enemy::butterfly(std::vector<Block> Blocks, Flamingo* player) {
    getCloseBlocks(Blocks);
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
            if (GenericColision(Blocks[closeBlocks[i]].rect, rect)) {
                orbit.x -= 1*SCALE*std::cos(radians);
                orbit.y -= 1*SCALE*std::sin(radians);
            }
        }

        if (abs(player->rect.x-rect.x) + abs(player->rect.y-rect.y) < 60*SCALE) { // fun-mode: Butterfly-chase, change < to >
            behavior = 1;
        }
    } else if (behavior == 1) {
        angle -= 3;
        if (angle < 0) {
            behavior = 50;
            angle = 0;
        }
    } else if (behavior >= 2) {
        if (player->rect.x > rect.x) {
            vx = 3*SCALE;
        } else if (rect.x > player->rect.x) {
            vx = -3*SCALE;
        }
        if (player->rect.y > rect.y) {
            vy = 3*SCALE;
        } else if (rect.y > player->rect.y) {
            vy = -3*SCALE;
        }

        int sizeB = closeBlocks.size();
        rect.x += vx;
        cx += vx;
        for (int i = 0; i < sizeB; i++) {
            if (GenericColision(Blocks[closeBlocks[i]].rect, rect)) {
                rect.x -= vx;
                cx -= vx;
                break;
            }
        }
        rect.y += vy;
        cy += vy;
        for (int i = 0; i < sizeB; i++) {
            if (GenericColision(Blocks[closeBlocks[i]].rect, rect)) {
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

void Enemy::crab(Flamingo* player) {
    rect.x += vx;
    cx += vx;
    if (behavior == 0) {
        if (rect.x < patrol1) {
            vx = 2;
        }
        if (rect.x+rect.width > patrol2) {
            vx = -2;
        }
        if (abs(player->rect.x-rect.x) + abs(player->rect.y-rect.y) < 80*SCALE) {
            behavior = 1;
            vx = 4;
        }
    } else if (behavior == 1) {
        if (player->rect.x > rect.x) {
            vx = 4;
        } else {
            vx = -4;
        }
        if (abs(player->rect.x-rect.x) + abs(player->rect.y-rect.y) > 80*SCALE) {
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
}

void Enemy::meldrop(Flamingo* player, std::vector<Effect> &effects) {
    if (behavior == 0) {
        if (abs(cx - player->cx) + abs(cy - player->cy) < 120*SCALE) {
            behavior = 1;
        }
    } else if (behavior < 90) {
        if (abs(cx - player->cx) + abs(cy - player->cy) > 120*SCALE) {
            behavior = 0;
        }
        behavior += 1;
    } else if (behavior >= 90) {
        Vector2 center = {cx, cy};
        Vector2 direction;
        float angle = std::atan2(player->cx - cx, player->cy - cy);
        direction.x = std::sin(angle)*5;
        direction.y = std::cos(angle)*5;
        int damager[5] = {0, 0, 0, 0, 1};
        Effect tiro(center, direction, 120, 1, damager, SCALE);
        effects.push_back(tiro);
        behavior = 0;
    }
}

void Enemy::getCloseBlocks(std::vector<Block> Blocks) {
    if (tick % 5 == 0) {
        closeBlocks.clear();
        int sizeB = Blocks.size();
        for (int i = 0; i < sizeB; i++) {
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
}