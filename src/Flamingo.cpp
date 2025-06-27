#include "../include/Flamingo.hpp"



Flamingo::Flamingo(float x, float y, float w, float h, int worldWidth, int worldHeight, int imagescale) {
    SetSoundVolume(sfxJump, 0.25);
    SetSoundVolume(sfxSecret, 0.4);
    SetTextureWrap(images[0], TEXTURE_WRAP_CLAMP);
    SetTextureWrap(images[1], TEXTURE_WRAP_CLAMP);
    SetTextureWrap(images[2], TEXTURE_WRAP_CLAMP);
    SetTextureWrap(images[3], TEXTURE_WRAP_CLAMP);
    SetTextureWrap(images[4], TEXTURE_WRAP_CLAMP);
    SetTextureWrap(images[5], TEXTURE_WRAP_CLAMP);


    SCALE = imagescale;
    rect.x = x;
    rect.y = y;
    rectImage.width = w;
    rectImage.height = h;

    rect.width = rectImage.width*SCALE;
    rect.height = rectImage.height*SCALE;

    WT = worldWidth;
    HT = worldHeight;

    vx = 0;
    vy = 0;

    cx = rect.x+rect.width/2;
    cy = rect.y+rect.height/2;

    Hitbox1 = Rectangle {rect.x+5*SCALE, rect.y+15*SCALE, 6.0f*SCALE, 8.0f*SCALE}; // Legs
    Hitbox2 = Rectangle {rect.x+3*SCALE, rect.y+7*SCALE, 11.0f*SCALE, 7.0f*SCALE}; // Chest
    Hitbox3 = Rectangle {rect.x+9*SCALE, rect.y, 9.0f*SCALE, 8.0f*SCALE}; // Head
    HitboxA = Rectangle {rect.x, rect.y, 23.0f*SCALE, 11.0f*SCALE}; // Crouch
    
    HB1 = {Hitbox1.x-1*SCALE, Hitbox1.y+7*SCALE, 10.0f*SCALE, 2.0f*SCALE}; // Ground Detection
}

Flamingo::Flamingo(int imagescale) {
    SCALE = imagescale;
    SetSoundVolume(sfxJump, 0.25);
    SetSoundVolume(sfxSecret, 0.4);
    SetTextureWrap(images[0], TEXTURE_WRAP_CLAMP);
    SetTextureWrap(images[1], TEXTURE_WRAP_CLAMP);
    SetTextureWrap(images[2], TEXTURE_WRAP_CLAMP);
    SetTextureWrap(images[3], TEXTURE_WRAP_CLAMP);
    SetTextureWrap(images[4], TEXTURE_WRAP_CLAMP);
    SetTextureWrap(images[5], TEXTURE_WRAP_CLAMP);

    Hitbox1 = Rectangle {0, 0, 6.0f*SCALE, 8.0f*SCALE};
    Hitbox2 = Rectangle {0, 0, 11.0f*SCALE, 7.0f*SCALE};
    Hitbox3 = Rectangle {0, 0, 9.0f*SCALE, 8.0f*SCALE};
    HitboxA = Rectangle {0, 0, 23.0f*SCALE, 11.0f*SCALE};
    
    HB1 = {0, 0, 12.0f*SCALE, 2.0f*SCALE};
}

void Flamingo::unload() {
    UnloadTexture(images[5]);
    UnloadTexture(images[4]);
    UnloadTexture(images[3]);
    UnloadTexture(images[2]);
    UnloadTexture(images[1]);
    UnloadTexture(images[0]);

    UnloadSound(sfxCoin);
    UnloadSound(sfxFood);
    UnloadSound(sfxJump);
    UnloadSound(sfxHeartPiece);
    UnloadSound(sfxSecret);
    UnloadSound(sfxKey);
    UnloadSound(sfxDoor);
    UnloadSound(sfxVulnerable);
    UnloadSound(sfxHurt);
    UnloadSound(sfxFall);
    UnloadSound(sfxPearlPiece);
    UnloadSound(sfxSpecial);

    UnloadTexture(P1image);
    UnloadTexture(P2image);
    UnloadTexture(P3image);
    UnloadTexture(P4image);
    UnloadTexture(P5image);


}

void Flamingo::update(std::map<int, std::map<int, Block>> &Blocks, std::map<int, std::map<int, Block>> &BackBlocks, std::vector<Item> &itens, std::vector<Enemy> enemies, std::vector<Effect> &effects) {
    
    #ifdef OPERATIONALDEBUG
    std::ofstream operation2("operationalFile", std::ios::app);
    operation2 << "Flamingo Tries to update...\n";
    operation2.close();
    #endif
    keyPress(Blocks, effects);
    #ifdef OPERATIONALDEBUG
    std::ofstream operation3("operationalFile", std::ios::app);
    operation3 << "Keypress is registered!\n";
    operation3.close();
    #endif
    CheckCloseObjects(itens, enemies);
    #ifdef OPERATIONALDEBUG
    std::ofstream operation4("operationalFile", std::ios::app);
    operation4 << "Checking Close objects also work!\n";
    operation4.close();
    #endif
    gravity();
    #ifdef OPERATIONALDEBUG
    std::ofstream operation5("operationalFile", std::ios::app);
    operation5 << "Flamingo is attracted to the Ground.\n";
    operation5.close();
    #endif
    Physics(Blocks, BackBlocks, effects);
    #ifdef OPERATIONALDEBUG
    std::ofstream operation6("operationalFile", std::ios::app);
    operation6 << "Physics seems to work, which is impressive!\n";
    operation6.close();
    #endif
    ItemColision(itens);
    #ifdef OPERATIONALDEBUG
    std::ofstream operation7("operationalFile", std::ios::app);
    operation7 << "flamingo tries to grab things and is sucessful!\n";
    operation7.close();
    #endif
    EnemyColision(enemies);
    #ifdef OPERATIONALDEBUG
    std::ofstream operation8("operationalFile", std::ios::app);
    operation8 << "Enemies try to grab Flamingo and are sucessful...\n";
    operation8.close();
    #endif

    for(char type : {'H', 'R', 'P', 'C', 'W'}) {
        if (invincibility[type] > 0) {
            invincibility[type] -= 1;
        }
    }

    // if (abs(player->vy) > 8 or abs(player->vx) > 8) {
    //     tickBlockUpdate = 1;
    // } else {
    //     tickBlockUpdate = 5;
    // }



    tick += 1;
    if (tick % PRH == 0) {
        if (RH < MRH) {
            RH += 1;
        }
        if (WP < MWP) {
            WP += 1;
        }
    }

    
    #ifdef OPERATIONALDEBUG
    std::ofstream operation("operationalFile", std::ios::app);
    operation << "All of Flamingo's update function works!\n";
    operation.close();
    #endif
}

void Flamingo::CheckCloseObjects(std::vector<Item> &itens, std::vector<Enemy> enemies) {
    if (tick % tickBlockUpdate == 0) {
        CIs.clear();
        int sizeI = itens.size();
        for (int i = 0; i < sizeI; i++) {
            int dx = abs(itens[i].cx - cx);
            if (dx < rect.width*2) {
                int dy = abs(itens[i].cy - cy);
                if (dy < rect.height*2) {
                    CIs.push_back(i);
                }
            }
        }


        CEs.clear();
        int sizeE = enemies.size();
        for (int i = 0; i < sizeE; i++) {
            int dx = abs(enemies[i].cx - cx);
            if (dx < rect.width*2) {
                int dy = abs(enemies[i].cy - cy);
                if (dy < rect.height*2) {
                    CEs.push_back(i);
                }
            }
        }
    }
}

void Flamingo::keyPress(std::map<int, std::map<int, Block>> &Blocks, std::vector<Effect> &effects) {
    W = IsKeyDown(KEY_W);
    A = IsKeyDown(KEY_A);
    S = IsKeyDown(KEY_S);
    D = IsKeyDown(KEY_D);


    if (powers[0] and IsKeyDown(KEY_ONE) and WP >= 3 and invincibility['H'] == 0) {
        WP -= 3;
        if (lookingRight) {
            naturalSpeed += 14;
        } else {
            naturalSpeed -= 14;
        }
        invincibility['H'] += 10;
    }
    if (powers[1] and IsKeyDown(KEY_TWO) and PP >= 7 and invincibility['R'] == 0) {

        
        int Bcx = (Hitbox1.x)/(game->BS-SCALE);
        int Bcy = (Hitbox1.y + 9)/(game->BS-SCALE);
        if (!(Blocks.count(Bcx) and Blocks[Bcx].count(Bcy))) {
            PP -= 7;
            Block temp = Block(Bcx*(game->BS-SCALE), Bcy*(game->BS-SCALE), game->BS, game->BS, "energy", SCALE);
            game->FrontBlocksMap[Bcx][Bcy] = temp;
            invincibility['R'] += 10;
        }
    }
    if (powers[2] and IsKeyDown(KEY_THREE) and FP >= 3 and invincibility['P'] == 0) {
        if (isBoost) {
            isBoost = false;
            invincibility['P'] += 10;
        } else {
            FP -= 1;
            invincibility['P'] += 10;
            isBoost = true;
        }
    }
    if (powers[3] and IsKeyDown(KEY_FOUR) and HP >= 7 and invincibility['C'] == 0) {
        Vector2 direction;
        direction.y = 0;
        if (lookingRight) {
            direction.x = 7;
        } else {
            direction.x = -7;
        }
        int dmg[5] = {0, 0, 0, 0, 0};
        Effect spear({cx, cy-8*SCALE}, direction, 250, 3, dmg, SCALE);

        effects.push_back(spear);
        HP -= 7;
        invincibility['C'] += 10;
    }
    if (powers[4] and IsKeyDown(KEY_FIVE) and EP >= 7 and invincibility['W'] == 0) {
        Vector2 direction;
        direction.y = 0;
        if (lookingRight) {
            direction.x = 2;
        } else {
            direction.x = -2;
        }
        int dmg[5] = {0, 0, 0, 0, 0};
        Effect transmutation({cx, cy}, direction, 250, 2, dmg, SCALE);

        effects.push_back(transmutation);
        EP -= 7;
        invincibility['W'] += 10;
    }





    if (A) {
        if (naturalSpeed > -6) {
            naturalSpeed = -6;
        }
        if (naturalSpeed < -6 and tick % 4 == 0) {
            naturalSpeed += 1;
        }
        if (lookingRight) {
            if (CheckMirror(Blocks)) {
                lookingRight = false;
            }
        }
        if (isBoost) {
            if (naturalSpeed > -12) {
                naturalSpeed = -12;
            }
            if (tick % 45 == 0) {
                FP -= 1;
                if (FP == 0) {
                    isBoost = false;
                }
            }
        }
    } else if (D) {
        if (naturalSpeed < 6) {
            naturalSpeed = 6;
        }
        if (naturalSpeed > 6 and tick % 4 == 0) {
            naturalSpeed -= 1;
        }
        if (!lookingRight) {
            if (CheckMirror(Blocks)) {
                lookingRight = true;
            }
        }
        if (isBoost) {
            if (naturalSpeed < 12) {
                naturalSpeed = 12;
            }
            if (tick % 45 == 0) {
                FP -= 1;
                if (FP == 0) {
                    isBoost = false;
                }
            }
        }
    } else {
        naturalSpeed = naturalSpeed/1.2;
    }

    if (ground) {
        vx = naturalSpeed*SCALE/groundBlock.friction;
    } else {
        vx = naturalSpeed*SCALE/2;
    }



    bool toggleCrouch = crouch;
    bool canCrouch = CrouchCheck(Blocks);
    crouch = false;


    if (W and !toggleCrouch) {
        jumpQueue = 5;
        // strength += 1;
        // if (strength > 5) {
        //     strength = 5;
        // }
        strength = 8;
    } else if (S) {
        if (ground and (canCrouch or toggleCrouch)) {
            if (not toggleCrouch) {
                rect.y += 11*SCALE;
                cy += 11*SCALE;
                rect.height = HitboxA.height;
                rect.width = HitboxA.width;
                rectImage.height = 12;
                rectImage.width = 23;
            }
            crouch = true;
            updateHitbox();
        }
    } else {
        if (jumpQueue == 0) {
            strength -= 2;
            if (strength < 0) {
                strength = 0;
            }
        }
    }


    if (toggleCrouch and not crouch and canCrouch) {
        imageCount = 0;
        rect.y -= 12*SCALE;
        cy -= 12*SCALE;
        rect.width = 18*SCALE;
        rect.height = 23*SCALE;
        rectImage.height = 23;
        rectImage.width = 18;
        updateHitbox();
    } else if (toggleCrouch) {
        crouch = true;
    }
    
    if (crouch) {
        vx = vx/3;
    }

    jumpQueue -= 1;
    if (canJump and jumpQueue > 0) {
        if (ground) {
            if (jumpQueue != 4 or strength == 8) {
                if (jumpQueue == 2) {
                    vy -= strength*0.95*SCALE;
                } else {
                    vy = -strength*0.95*SCALE;
                }
                strength = 0;
                PlaySound(sfxJump);
                canJump = false;
                crouch = false;
                imageCount = 4;
                jumpQueue = 0;
            }
        } else {
            vy = -strength*0.8f*SCALE;
            strength = 0;
            PlaySound(sfxJump);
            canJump = false;
            crouch = false;
            imageCount = 4;
            jumpQueue = 0;
        }
    }
}

void Flamingo::gravity() {
    vy += 0.6*SCALE;
    if (vy > 16*SCALE and tick % 60 == 0) {
        PlaySound(sfxFall);
    }
    if (rect.y > 3000) {
        Health(-7, 'C');
        rect.y = -1000;
    }
    if (vy > 25*SCALE) {
        vy = 25*SCALE;
    }
}

void Flamingo::EnemyColision(std::vector<Enemy> enemies) {
    int Esize = CEs.size();
    for (int i = 0; i < Esize; i++) {
        Enemy temp = enemies[CEs[i]];
        if (crouch) {
            if (GenericColision(HitboxA, temp.rect)) {
                TakeHit(temp);
                break;
            }
        } else {
            if (GenericColision(Hitbox1, temp.rect)) {
                TakeHit(temp);
                break;
            }

            if (GenericColision(Hitbox2, temp.rect)) {
                TakeHit(temp);
                break;
            }

            if (GenericColision(Hitbox3, temp.rect)) {
                TakeHit(temp);
                break;
            }
        }
    }
}

void Flamingo::TakeHit(Enemy enemy) {
    for (int i = 0; i < 5; i++) {
        if (enemy.dmgs[i] > 0 and invincibility[enemy.types[i]] == 0) {
            Health(-enemy.dmgs[i], enemy.types[i]);
        }
    }
}



int Flamingo::blockReaction(Rectangle HBox, Block &temp, bool vert, std::vector<Effect> &effects) {
    if (temp.name == "platform") {
        if (!(vert and vy > 0)) {
            return 0;
        }
    }
    if (temp.name == "nextLevel" or temp.name == "startLevel") {
        return 0;
    }
    if (GenericColision(HBox, temp.rect)) {
        int doReturn = 2;
        if (temp.secret) {
            PlaySound(sfxSecret);
            game->revealSecret(temp, 0, 0);
            return 4;
        }
        if (temp.name == "gate-hope" and keyHope > 0) {
            keyHope -= 1;
            temp.background = true;
            PlaySound(sfxDoor);
            temp.id += 5;
            doReturn = 3;
        } else if (temp.name == "gate-resilience" and keyResilience > 0) {
            keyResilience -= 1;
            temp.background = true;
            PlaySound(sfxDoor);
            temp.id += 5;
            doReturn = 3;
        } else if (temp.name == "gate-power" and keyPower > 0) {
            keyPower -= 1;
            temp.background = true;
            PlaySound(sfxDoor);
            temp.id += 5;
            doReturn = 3;
        } else if (temp.name == "gate-courage" and keyCourage > 0) {
            keyCourage -= 1;
            temp.background = true;
            PlaySound(sfxDoor);
            temp.id += 5;
            doReturn = 3;
        } else if (temp.name == "gate-wisdom" and keyWisdom > 0) {
            keyWisdom -= 1;
            temp.background = true;
            PlaySound(sfxDoor);
            temp.id += 5;
            doReturn = 3;
        } else if (temp.name == "spike") {
            if (invincibility['R'] <= 0) {
                if (
                (temp.direction == 0 and vert and vy > 0) or
                (temp.direction == 1 and !vert and vx > 0) or
                (temp.direction == 2 and vert and vy < 0) or
                (temp.direction == 3 and !vert and vx < 0)
                ) {
                    Health(-7, 'R');
                }
            }
        } else if (temp.name == "cage") {
            if (abs(vx) + abs(vy) > 9*SCALE) {
                int color = ((int)temp.rect.x+(int)temp.rect.y) % 5;
                int colorArray[5] = {color, 0, 0, 0, 0};
                effects.push_back(Effect({temp.cx-5*SCALE, temp.cy-5*SCALE}, {0, 0}, 5000, 4, colorArray, SCALE));
                temp.background = true;
                birdsToSave[color] -= 1;
                totalBirdsSaved[color] += 1;
                doReturn = 5;
            }
        } else if (temp.name == "switch_green") {
            if (abs(vy) > 3*SCALE) {
                temp.parameter += 1;
                doReturn = 1;
            }
        } else if (temp.name == "ivy") {
            if (invincibility['P'] == 0) {
                Health(-2, 'P');
            }
        }
        if (vert) {
            if (vy > 0) {
                canJump = true;
            }
            if (abs(vy) > 12*SCALE) {
                Health(-(((int)abs(vy) - 12*SCALE)/2), 'R');
            }
            if (temp.name == "altar" and tick % 14 == 0) {
                if (temp.friction > 1.5 and CH < MCH) {
                    doReturn = 3;
                    CH += 1;
                    temp.friction -= 0.5;
                    if (temp.friction <= 1.6f) { // to-do
                        temp.image = LoadTexture("assets/images/block_altar0at2.png");
                    } else if (temp.friction <= 5.0f) {
                        temp.image = LoadTexture("assets/images/block_altar1at2.png");
                    }
                }
            }
            vy = -vy/temp.friction;
            if (abs(vy) < 1) {
                vy = 0;
            }
        } else {
            vx = -vx/temp.friction;
            if (abs(vx) < 1) {
                vx = 0;
            }
            naturalSpeed = 0;
        }



        
        return doReturn;
    }
    return 0;
}
 
void Flamingo::Physics(std::map<int, std::map<int, Block>> &Blocks, std::map<int, std::map<int, Block>> &BackBlocks, std::vector<Effect> &effects) { // Working on...

    
    #ifdef OPERATIONALDEBUG
    std::ofstream operation("operationalFile", std::ios::app);
    operation << "Physics start at least, right? \n";
    operation.close();
    #endif

    // Vertical Axis checking
    float dy = vy/6;
    float dx = vx/6;
    for (int step = 1; step <= 6 and (vy != 0 or vx != 0); step++) {
        rect.y += dy;
        updateHitbox();
        int Gx = cx/(game->BS-SCALE);
        int Gy = cy/(game->BS-SCALE);

        #ifdef OPERATIONALDEBUG
        std::ofstream operation2("operationalFile", std::ios::app);
        operation2 << "Steps also start? \n";
        operation2.close();
        #endif

        for (int i = -2; i < 3 and vy != 0; i++) {
            for (int j = -2; j < 3 and vy != 0; j++) {
                if (Blocks.count(Gy+i) > 0 and Blocks[Gy+i].count(Gx+j) > 0) {
                    Block temp = Blocks[Gy+i][Gx+j];
                    int doColide = 0, returned = 0;
    
                    if (crouch) {
                        doColide = blockReaction(HitboxA, temp, true, effects);
                    } else {
                        doColide = blockReaction(Hitbox3, temp, true, effects);
                        returned = blockReaction(Hitbox2, temp, true, effects);
                        if (returned > doColide) {
                            doColide = returned;
                        }
                        returned = blockReaction(Hitbox1, temp, true, effects);
                        if (returned > doColide) {
                            doColide = returned;
                        }
                    }
                    if (doColide == 1) {
                        Blocks[Gy+i][Gx+j] = temp;
                        continue;
                    } else if (doColide == 2) {
                        // break;
                    } else if (doColide == 3) {
                        Blocks[Gy+i].erase(Gx+j);
                        BackBlocks[Gy+i][Gx+j] = temp;
                        break;
                    } else if (doColide == 4) {
                        break;
                    } else if (doColide == 5) {
                        Blocks[Gy+i].erase(Gx+j);
                        continue;
                    }
                    // for (int m = 0; m < 4 and doColide != 0; m++) {
                    if (doColide != 0) {
                        rect.y -= dy;
                        updateHitbox();
                        dy = 0;
                        vy = 0;
                    }
                        // doColide = blockReaction(Hitbox1, temp, true, effects) + blockReaction(Hitbox2, temp, true, effects) + blockReaction(Hitbox3, temp, true, effects);
                    // }
                }
            }
        }
        ground = false;
        
        for (int i = -2; i < 3; i++) {
            for (int j = -2; j < 3; j++) {
                if (Blocks.count(Gy+i) > 0 and Blocks[Gy+i].count(Gx+j) > 0) {
                    Block temp = Blocks[Gy+i][Gx+j];
                    if (groundCheck(temp)) {
                        ground = true;
                        groundBlock = temp;
                        break;
                    }
                }
            }
        }
        
        
        
        
        
        // Horizontal Axis checing
        rect.x += dx;
        updateHitbox();
        for (int i = -2; i < 3 and vx != 0; i++) {
            for (int j = -2; j < 3 and vx != 0; j++) {
                if (Blocks.count(Gy+i) > 0 and Blocks[Gy+i].count(Gx+j) > 0) {
                    Block temp = Blocks[Gy+i][Gx+j];
                    int doColide = 0, returned = 0;
    
                    if (crouch) {
                        doColide = blockReaction(HitboxA, temp, false, effects);
                    } else {
                        doColide = blockReaction(Hitbox3, temp, false, effects);
                        returned = blockReaction(Hitbox2, temp, false, effects);
                        if (returned > doColide) {
                            doColide = returned;
                        }
                        returned = blockReaction(Hitbox1, temp, false, effects);
                        if (returned > doColide) {
                            doColide = returned;
                        }
                    }
                    if (doColide == 1) {
                        Blocks[Gy+i][Gx+j] = temp;
                        continue;
                    } else if (doColide == 2) {
                        // break;
                    } else if (doColide == 3) {
                        Blocks[Gy+i].erase(Gx+j);
                        BackBlocks[Gy+i][Gx+j] = temp;
                        break;
                    } else if (doColide == 4) {
                        break;
                    } else if (doColide == 5) {
                        Blocks[Gy+i].erase(Gx+j);
                        break;
                    }
                    if (doColide != 0) {
                        rect.x -= dx;
                        updateHitbox();
                        dx = 0;
                        vx = 0;
                    }
                }
            }
        }
    }
     
    



    if (crouch) {
        imageCount = 5;
    } else if (tick % 10 == 0) {
        if (not canJump) {
            imageCount = 4;
        } else if (vx != 0) {
            imageCount++;
            if (imageCount > imageSize) {
                imageCount = 0;
            }
        } else if (imageCount != 3) {
            if (imageCount == 0 and canJump) {
                imageCount = 3;
            } else {
                imageCount = 0;
            }
        }
    }

    
    #ifdef OPERATIONALDEBUG
    std::ofstream operation2("operationalFile", std::ios::app);
    operation2 << "All of Physics work!\n";
    operation2.close();
    #endif
}

void Flamingo::updateHitbox() {
    HitboxA.x = rect.x;
    HitboxA.y = rect.y;
    if (lookingRight) {
        Hitbox1.x = rect.x+5*SCALE;
        Hitbox2.x = rect.x+3*SCALE;
        Hitbox3.x = rect.x+9*SCALE;
    } else {
        Hitbox1.x = rect.x+7*SCALE;
        Hitbox2.x = rect.x+4*SCALE;
        Hitbox3.x = rect.x;
    }
    Hitbox1.y = rect.y+15*SCALE;
    Hitbox2.y = rect.y+7*SCALE;
    Hitbox3.y = rect.y+1*SCALE;
    cx = rect.x + rect.width/2;
    cy = rect.y + rect.height/2;
}

void Flamingo::ItemColision(std::vector<Item> &itens) {
    int isize = CIs.size();
    for (int i = 0; i < isize; i++) {
        Item temp = itens[CIs[i]];
        Vector2 Dspace;
        Vector2 DspaceNew;
        std::vector<Item>::iterator pos = itens.begin();
        std::vector<int>::iterator posCI = CIs.begin();
        pos += CIs[i];
        posCI += i;
        // if (CIs[i]+1 == itens.size()) {
        //     break;
        // }

        bool colided;
        if (crouch) {
            colided = GenericColision(HitboxA, temp.rect);
        } else {
            colided = GenericColision(Hitbox1, temp.rect) or GenericColision(Hitbox2, temp.rect) or GenericColision(Hitbox3, temp.rect);
        }
        if (colided) {
            collect(temp);
            itens.erase(pos);
            CIs.erase(posCI); // to-do This is probably the source of the item not grab problem
            isize--;
            continue;
        }
    }
}

void Flamingo::collect(Item item) {
    switch(item.category) {
        case 'C':
            PlaySound(sfxCoin);
            break;
        case 'F':
            PlaySound(sfxFood);
            break;
        case 'H':
            PlaySound(sfxHeartPiece);
            break;
        case 'K':
            PlaySound(sfxKey);
            break;
        case 'P':
            PlaySound(sfxPearlPiece);
            break;
        case 'S':
            PlaySound(sfxSpecial);
            break;
    }

    if (item.name == "coin-copper") {
        score += 5;
    } else if (item.name == "coin-silver") {
        score += 20;
    } else if (item.name == "coin-gold") {
        score += 75;
    } else if (item.name == "coin-death") {
        score += 150;
    } else if (item.name == "coin-poison") {
        Health(-4, 'H');
        score += 25;
    } else if (item.name == "food-banana") { // Fun-mode
        score += 2;
        pWP += 5;
        pPH += 7;
        if (pWP > PWP) {
            if (WP < MWP) {
                WP += 1;
            }
            pWP -= PWP;
        }
    } else if (item.name == "food-pear") { 
        score += 3;
        pPP += 2;
        pPH += 9;
        if (pPP > PPP) {
            if (PP < MPP) {
                PP += 1;
            }
            pPP -= PPP;
        }
    } else if (item.name == "food-blueberry") {
        score += 4;
        pFP += 3;
        pPH += 11;
        if (pFP > PFP) {
            if (FP < MFP) {
                FP += 1;
            }
            pFP -= PFP;
        }
    } else if (item.name == "food-pepper") {
        score += 6;
        pHP += 3;
        pPH += 13;
        if (pHP > PHP) {
            if (HP < MHP) {
                HP += 1;
            }
            pHP -= PHP;
        }
    } else if (item.name == "food-orange") {
        score += 8;
        pEP += 2;
        pPH += 15;
        if (pEP > PEP) {
            if (EP < MEP) {
                EP += 1;
            }
            pEP -= PEP;
        }
    } else if (item.name == "Hshard-hope") {
        SHH += 1;
        if (SHH == 3) {
            MHH += 7;
            HH += 7;
            SHH = 0;
        }
    } else if (item.name == "Hshard-resilience") {
        SRH += 1;
        if (SRH == 3) {
            MRH += 7;
            RH += 7;
            SRH = 0;
        }
    } else if (item.name == "Hshard-power") {
        PPH += 1;
        if (PPH == 3) {
            MPH += 7;
            PH += 7;
            PPH = 0;
        }
    } else if (item.name == "Hshard-courage") {
        SCH += 1;
        if (SCH == 3) {
            MCH += 7;
            CH += 7;
            SCH = 0;
        }
    } else if (item.name == "Hshard-wisdom") {
        SWH += 1;
        if (SWH == 3) {
            MWH += 7;
            WH += 7;
            SWH = 0;
        }
    } else if (item.name == "Pshard-wind") {
        SWP += 1;
        if (SWP == 3) {
            MWP += 7;
            WP += 7;
            SWP = 0;
        }
    } else if (item.name == "Pshard-party") {
        SPP += 1;
        if (SPP == 3) {
            MPP += 7;
            PP += 7;
            SPP = 0;
        }
    } else if (item.name == "Pshard-fun") {
        SFP += 1;
        if (SFP == 3) {
            MFP += 7;
            FP += 7;
            SFP = 0;
        }
    } else if (item.name == "Pshard-hard") {
        SHP += 1;
        if (SHP == 3) {
            MHP += 7;
            HP += 7;
            SHP = 0;
        }
    } else if (item.name == "Pshard-eloise") {
        SEP += 1;
        if (SEP == 3) {
            MEP += 7;
            EP += 7;
            SEP = 0;
        }
    } else if (item.name == "key-hope") {
        keyHope += 1;
    } else if (item.name == "key-resilience") {
        keyResilience += 1;
    } else if (item.name == "key-power") {
        keyPower += 1;
    } else if (item.name == "key-courage") {
        keyCourage += 1;
    } else if (item.name == "key-wisdom") {
        keyWisdom += 1;
    } else if (item.name == "courage-potion") {
        pCH += 56;
        while (pCH > PCH) {
            Health(1, 'C');
            pCH -= PCH;
        }
    } else if (item.name == "party-potion") {
        pPP += 196;
        while (pPP > PPP) {
            MPP += 1;
            pPP -= PPP;
        }
    } else if (item.name == "power-dash") {
        powers[0] = true;
    } else if (item.name == "power-toast") {
        powers[1] = true;
    } else if (item.name == "power-boost") {
        powers[2] = true;
    } else if (item.name == "power-spear") {
        powers[3] = true;
    } else if (item.name == "power-transmutation") {
        powers[4] = true;
    }

    if (pPH > PPH) {
        pPH -= PPH;
        Health(1, 'P');
    }
    if (item.category != 'C') {
        game->DustBringer(item.cx, item.cy, BLACK, game->RNG100(game->rng), true);
        game->DustBringer(item.cx, item.cy, BLACK, game->RNG100(game->rng), true);
        game->DustBringer(item.cx, item.cy, BLACK, game->RNG100(game->rng), true);
        game->DustBringer(item.cx, item.cy, BLACK, game->RNG100(game->rng), true);
        game->DustBringer(item.cx, item.cy, BLACK, game->RNG100(game->rng), true);
    }
}

void Flamingo::Health(int qtd, char type) {
    if (qtd < 0) {
        invincibility[type] += 60;
        pHP += qtd*4;
        if (pHP > PHP) {
            if (HP < MHP) {
                HP += 1;
            }
            pHP -= PHP;
        }
        PlaySound(sfxHurt);
        if (lookingRight) {
            naturalSpeed += 4;
        } else {
            naturalSpeed -= 4;
        }
    }

    switch(type) {
        case 'H':
            HH += qtd;
            break;
        case 'R':
            RH += qtd;
            break;
        case 'P':
            PH += qtd;
            break;
        case 'C':
            CH += qtd;
            break;
        case 'W':
            WH += qtd;
            break;
    }

    if (HH <= 0 and RH <= 0 and PH <= 0 and CH <= 0 and WH <= 0) {
        gameover = true;
        HH = 0;
        RH = 0;
        PH = 0;
        CH = 0;
        WH = 0;
        PlaySound(sfxVulnerable);
        return;
    }
    if (gameover) {
        if (HH > 4 and RH > 4 and PH > 4 and CH > 4 and WH > 4)  {
            gameover = false;
            HH -= 4;
            RH -= 4;
            PH -= 4;
            CH -= 4;
            WH -= 4;
        }
    }

    if (HH > MHH) {
        HH = MHH;
    }
    if (RH > MRH) {
        RH = MRH;
    }
    if (PH > MPH) {
        PH = MPH;
    }
    if (CH > MCH) {
        CH = MCH;
    }
    if (WH > MWH) {
        WH = MWH;
    }

    if (HH < 0) {
        int extraDmg = 2*HH;
        HH = 0;
        Health(extraDmg, 'R');
    }
    if (RH < 0) {
        int extraDmg = 2*RH;
        RH = 0;
        Health(extraDmg, 'P');
    }
    if (PH < 0) {
        int extraDmg = 2*PH;
        PH = 0;
        Health(extraDmg, 'C');
    }
    if (CH < 0) {
        int extraDmg = 2*CH;
        CH = 0;
        Health(extraDmg, 'W');
    }
    if (WH < 0) {
        int extraDmg = 2*WH;
        WH = 0;
        Health(extraDmg, 'H');
    }
}

/*
*   Function called when you want to change sides
*   If player is currently looking right, and looking left will trigger its hitbox into a wall, this function stops player from looking left.
*   Might cause bug: If blockReaction does alterations to player that shouldn't be done out of the Physics check 
*/
bool Flamingo::CheckMirror(std::map<int, std::map<int, Block>> &Blocks) {
    Hitbox1.y = rect.y+15*SCALE;
    Hitbox2.y = rect.y+7*SCALE;
    Hitbox3.y = rect.y+1*SCALE;
    if (crouch) {
        return true;
    } else {
        int Gx = cx/(game->BS-SCALE);
        int Gy = cy/(game->BS-SCALE);
        if (lookingRight) {
            Hitbox1.x = rect.x+7*SCALE;
            Hitbox2.x = rect.x+4*SCALE;
            Hitbox3.x = rect.x;

            for (int i = -2; i < 3; i++) {
                for (int j = -2; j < 3; j++) {
                    if (Blocks.count(Gy+i) > 0 and Blocks[Gy+i].count(Gx+j) > 0) {
                        Block temp = Blocks[Gy+i][Gx+j];

                        if (GenericColision(Hitbox1, temp.rect)) {
                            return false;
                        }
                        if (GenericColision(Hitbox2, temp.rect)) {
                            return false;
                        }
                        if (GenericColision(Hitbox3, temp.rect)) {
                            return false;
                        }
                    }
                }
            }
            
            Hitbox1.x = rect.x+5*SCALE;
            Hitbox2.x = rect.x+3*SCALE;
            Hitbox3.x = rect.x+9*SCALE;
        } else {
            Hitbox1.x = rect.x+5*SCALE;
            Hitbox2.x = rect.x+3*SCALE;
            Hitbox3.x = rect.x+9*SCALE;

            for (int i = -2; i < 3; i++) {
                for (int j = -2; j < 3; j++) {
                    if (Blocks.count(Gy+i) > 0 and Blocks[Gy+i].count(Gx+j) > 0) {
                        Block temp = Blocks[Gy+i][Gx+j];

                        if (GenericColision(Hitbox1, temp.rect)) {
                            return false;
                        }
                        if (GenericColision(Hitbox2, temp.rect)) {
                            return false;
                        }
                        if (GenericColision(Hitbox3, temp.rect)) {
                            return false;
                        }
                    }
                }
            }

            Hitbox1.x = rect.x+7*SCALE;
            Hitbox2.x = rect.x+4*SCALE;
            Hitbox3.x = rect.x;
        }
    }
    return true;
}

bool Flamingo::CrouchCheck(std::map<int, std::map<int, Block>> &Blocks) {
    bool returned = true;
    int Gx = cx/(game->BS-SCALE);
    int Gy = cy/(game->BS-SCALE);
    if (crouch) {
        rect.y -= 13*SCALE;
        updateHitbox();

        for (int i = -2; i < 3; i++) {
            for (int j = -2; j < 3; j++) {
                if (Blocks.count(Gy+i) > 0 and Blocks[Gy+i].count(Gx+j) > 0) {
                    Block temp = Blocks[Gy+i][Gx+j];

                    if (GenericColision(Hitbox1, temp.rect)) {
                        returned = false;
                        break;
                    }
                    if (GenericColision(Hitbox2, temp.rect)) {
                        returned = false;
                        break;
                    }
                    if (GenericColision(Hitbox3, temp.rect)) {
                        returned = false;
                        break;
                    }
                }
            }
        }
        rect.y += 13*SCALE;
    } else {
        HitboxA.x = rect.x;
        HitboxA.y = rect.y + 11*SCALE;
        for (int i = -2; i < 3; i++) {
            for (int j = -2; j < 3; j++) {
                if (Blocks.count(Gy+i) > 0 and Blocks[Gy+i].count(Gx+j) > 0) {
                    Block temp = Blocks[Gy+i][Gx+j];
                    if (GenericColision(HitboxA, temp.rect)) {
                        returned = false;
                        break;
                    }
                }
            }
        }
        HitboxA.y = rect.y;
    }
    updateHitbox();
    return returned;
}

bool Flamingo::groundCheck(Block ground) {
    // This block is different from the one being printed out there.
    // DrawText(TextFormat("Ptr=%d", ground), GetScreenWidth()/2 - 200, 200, 30, WHITE);
    // DrawText(TextFormat("X=%02.02f, Y=%02.02f, W=%02.02f, H=%02.02f", ground.rect.x, ground.rect.y, ground.rect.width, ground.rect.height), GetScreenWidth()/2 - 200, 200, 30, WHITE);
    if (ground.name == "startLevel" or ground.name == "nextLevel") {
        return false;
    }
    if (crouch) {
        HB1.x = HitboxA.x+3*SCALE;
        HB1.y = HitboxA.y+11*SCALE;
    } else {
        HB1.x = Hitbox1.x-3*SCALE;
        HB1.y = Hitbox1.y+8*SCALE;
    }

    return GenericColision(HB1, ground.rect);
}



