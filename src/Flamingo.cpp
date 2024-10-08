#include "../header/Flamingo.hpp"



Flamingo::Flamingo(float x, float y, float w, float h, int worldWidth, int worldHeight, int imagescale) {
    SetSoundVolume(sfxJump, 0.25);
    SetSoundVolume(sfxSecret, 0.4);
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

    Hitbox1 = Rectangle {rect.x+7*SCALE, rect.y+15*SCALE, 6.0f*SCALE, 8.0f*SCALE};
    Hitbox2 = Rectangle {rect.x+3*SCALE, rect.y+7*SCALE, 11.0f*SCALE, 7.0f*SCALE};
    Hitbox3 = Rectangle {rect.x+9*SCALE, rect.y, 9.0f*SCALE, 8.0f*SCALE};
    HitboxA = Rectangle {rect.x, rect.y, 18.0f*SCALE, 16.0f*SCALE};
    
    HB1 = {Hitbox1.x-1*SCALE, Hitbox1.y+7*SCALE, 10.0f*SCALE, 2.0f*SCALE};
}

Flamingo::Flamingo() {}

void Flamingo::unload() {
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
}

void Flamingo::update(std::vector<Block> &Blocks, std::vector<Item> &itens, std::vector<Enemy> enemies, std::vector<Effect> &effects) {
    keyPress(Blocks, effects);
    gravity();
    Physics(Blocks);
    ItemColision(itens);
    EnemyColision(enemies);
    CheckCloseObjects(Blocks, itens, enemies);

    for(char type : {'H', 'R', 'P', 'C', 'W'}) {
        if (invincibility[type] > 0) {
            invincibility[type] -= 1;
        }
    }
    if (tick % 300 == 0) {
        if (RH < MRH) {
            RH += 1;
        }
    }
    tick += 1;
}

void Flamingo::CheckCloseObjects(std::vector<Block> &Blocks, std::vector<Item> &itens, std::vector<Enemy> enemies) {
    if (tick % tickBlockUpdate == 0) {
        CBs.clear();
        int sizeB = Blocks.size();
        for (int i = 0; i < sizeB; i++) {
            if (Blocks[i].background) {
                continue;
            }
            int dx = abs(Blocks[i].cx - cx);
            if (dx < rect.width*3) {
                int dy = abs(Blocks[i].cy - cy);
                if (dy < rect.height*3) {
                    CBs.push_back(i);
                }
            }
        }


        CIs.clear();
        int sizeI = itens.size();
        for (int i = 0; i < sizeI; i++) {
            int dx = abs(itens[i].cx - cx);
            if (dx < rect.width*3) {
                int dy = abs(itens[i].cy - cy);
                if (dy < rect.height*3) {
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

void Flamingo::keyPress(std::vector<Block> &Blocks, std::vector<Effect> &effects) {
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
    crouch = false;
    if (W) {
        jumpQueue = 3;
    } else if (S) {
        if (ground) {
            if (not toggleCrouch) {
                rect.y += 7*SCALE;
                cy += 7*SCALE;
                rect.height = HitboxA.height;
                rectImage.height = 16;
            }
            crouch = true;
            updateHitbox();
            vx = vx/3;
        }
    }
    if (toggleCrouch and not crouch) {
        imageCount = 0;
        rect.y -= 7*SCALE;
        cy -= 7*SCALE;
        rect.height = 23*SCALE;
        rectImage.height = 23;
        updateHitbox();
    }

    if (canJump and jumpQueue > 0) {
        if (jumpQueue == 3) {
            vy = -4.5f*SCALE;
        } else if (jumpQueue == 2) {
            vy -= 4.5f*SCALE;
        } else {
            vy -= 2.0f*SCALE;
        }
        PlaySound(sfxJump);
        canJump = false;
        crouch = false;
        imageCount = 4;
        jumpQueue = 0;
    } else {
        jumpQueue -= 1;
    }

}

void Flamingo::gravity() {
    vy += 0.25*SCALE;
    if (vy > 9*SCALE and tick % 60 == 0) {
        PlaySound(sfxFall);
    }
    if (rect.y > 3000) {
        Health(-7, 'C');
        rect.y = -1000;
    }
}

void Flamingo::EnemyColision(std::vector<Enemy> enemies) {
    int Esize = CEs.size();
    Vector2 Dspace;
    for (int i = 0; i < Esize; i++) {
        Enemy temp = enemies[CEs[i]];
        if (crouch) {
            Dspace = colision(HitboxA, temp.rect);
            if ((Dspace.x+Dspace.y) != 0) {
                TakeHit(temp);
                break;
            }
        } else {
            Dspace = colision(Hitbox1, temp.rect);
            if ((Dspace.x+Dspace.y) != 0) {
                TakeHit(temp);
                break;
            }

            Dspace = colision(Hitbox2, temp.rect);
            if ((Dspace.x+Dspace.y) != 0) {
                TakeHit(temp);
                break;
            }

            Dspace = colision(Hitbox3, temp.rect);
            if ((Dspace.x+Dspace.y) != 0) {
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

int Flamingo::blockColision(Rectangle HBox, Block &temp, bool vert) {
    Vector2 Dspace;
    if (temp.background) {
        return 0;
    }
    if (temp.name == "platform") {
        if (!(vert and vy > 0)) {
            return 0;
        }
    }
    if (temp.name == "nextLevel" or temp.name == "startLevel") {
        return 0;
    }
    Dspace = colision(HBox, temp.rect);
    if (vert) {
        rect.y += Dspace.y;
    } else {
        rect.x += Dspace.x;
    }
    if ((!vert and Dspace.x != 0) or (vert and Dspace.y != 0)) {
        int doReturn = 2;
        if (temp.secret) {
            PlaySound(sfxSecret);
            temp.secret = false;
            temp.background = true;
            return 1;
        }
        if (temp.name == "gate-hope" and keyHope > 0) {
            keyHope -= 1;
            temp.background = true;
            PlaySound(sfxDoor);
            doReturn = 3;
        } else if (temp.name == "gate-resilience" and keyResilience > 0) {
            keyResilience -= 1;
            temp.background = true;
            PlaySound(sfxDoor);
            doReturn = 3;
        } else if (temp.name == "gate-power" and keyPower > 0) {
            keyPower -= 1;
            temp.background = true;
            PlaySound(sfxDoor);
            doReturn = 3;
        } else if (temp.name == "gate-courage" and keyCourage > 0) {
            keyCourage -= 1;
            temp.background = true;
            PlaySound(sfxDoor);
            doReturn = 3;
        } else if (temp.name == "gate-wisdom" and keyWisdom > 0) {
            keyWisdom -= 1;
            temp.background = true;
            PlaySound(sfxDoor);
            doReturn = 3;
        } else if (temp.name == "spike") {
            if (invincibility['R'] <= 0) {
                if (
                (temp.direction == 0 and vert and vy > 0) or
                (temp.direction == 1 and !vert and vx > 0) or
                (temp.direction == 2 and vert and vy < 0) or
                (temp.direction == 3 and !vert and vx < 0)
                ){
                    Health(-7, 'R');
                }
            }
        }
        
        if (vert) {
            if (Dspace.y < 0) {
                canJump = true;
            }
            if (abs(vy) > 9*SCALE) {
                Health(-(((int)abs(vy) - 9*SCALE)/2), 'R');
            }
            if (temp.name == "altar" and tick % 14 == 0) {
                if (temp.friction > 1.5 and CH < MCH) {
                    doReturn = 3;
                    CH += 1;
                    temp.friction -= 0.5;
                    if (temp.friction <= 1.6f) {
                        temp.image = LoadTexture("images/block_altar0at2.png");
                    } else if (temp.friction <= 5.0f) {
                        temp.image = LoadTexture("images/block_altar1at2.png");
                    }
                }
            }

            Hitbox1.y += Dspace.y;
            Hitbox2.y += Dspace.y;
            Hitbox3.y += Dspace.y;
            HitboxA.y += Dspace.y;
            vy = -vy/temp.friction;
        } else {
            Hitbox1.x += Dspace.x;
            Hitbox2.x += Dspace.x;
            Hitbox3.x += Dspace.x;
            HitboxA.x += Dspace.x;
            vx = -vx/temp.friction;
            naturalSpeed = 0;
        }
        return doReturn;
    }
    return 0;
}

void Flamingo::Physics(std::vector<Block> &Blocks) {
    // Vertical Axis checking
    rect.y += vy;
    updateHitbox();
    
    int bsize = CBs.size();
    for (int i = 0; i < bsize; i++) {
        Block temp = Blocks[CBs[i]];
        int doColide = 0, returned = 0;

        if (crouch) {
            doColide = blockColision(HitboxA, temp, true);
        } else {
            doColide = blockColision(Hitbox1, temp, true);
            returned = blockColision(Hitbox2, temp, true);
            if (returned > doColide) {
                doColide = returned;
            }
            returned = blockColision(Hitbox3, temp, true);
            if (returned > doColide) {
                doColide = returned;
            }
        }
        if (doColide == 1) {
            Blocks[CBs[i]] = temp;
            continue;
        } else if (doColide == 2) {
            // break;
        } else if (doColide == 3) {
            Blocks[CBs[i]] = temp;
            break;
        }
    }


    ground = false;
    for (int i = 0; i < bsize; i++) {
        Block temp = Blocks[CBs[i]];
        if (groundCheck(temp)) {
            ground = true;
            groundBlock = temp;
            break;
        }
    }

    // Horizontal Axis checing
    rect.x += vx;
    updateHitbox();
    for (int i = 0; i < bsize; i++) {
        Block temp = Blocks[CBs[i]];
        int doColide = 0, returned = 0;

        if (crouch) {
            doColide = blockColision(HitboxA, temp, false);
        } else {
            doColide = blockColision(Hitbox1, temp, false);
            returned = blockColision(Hitbox2, temp, false);
            if (returned > doColide) {
                doColide = returned;
            }
            returned = blockColision(Hitbox3, temp, false);
            if (returned > doColide) {
                doColide = returned;
            }
        }
        if (doColide == 1) {
            Blocks[CBs[i]] = temp;
            continue;
        } else if (doColide == 2) {
            // break;
        } else if (doColide == 3) {
            Blocks[CBs[i]] = temp;
            break;
        }
    
    }




    cx = rect.x + rect.width/2;
    cy = rect.y + rect.height/2;
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
}

bool Flamingo::groundCheck(Block ground) {
    if (ground.name == "startLevel" or ground.name == "nextLevel") {
        return false;
    }
    if (crouch) {
        HB1.x = HitboxA.x+4*SCALE;
        HB1.y = HitboxA.y+16*SCALE;
    } else {
        HB1.x = Hitbox1.x-2*SCALE;
        HB1.y = Hitbox1.y+7*SCALE;
    }
    Vector2 C1 = colision(HB1, ground.rect);
    if (abs(C1.y)+abs(C1.x) > 0) {
        return true;
    }
    return false;
}

void Flamingo::updateHitbox() {
    HitboxA.x = rect.x;
    HitboxA.y = rect.y;
    if (lookingRight) {
        Hitbox1.x = rect.x+6*SCALE;
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
}

void Flamingo::ItemColision(std::vector<Item> &itens) {
    int isize = CIs.size();
    for (int i = 0; i < isize; i++) {
        Item temp = itens[CIs[i]];
        Vector2 Dspace;
        std::vector<Item>::iterator pos = itens.begin();
        pos += CIs[i];
        if (CIs[i]+1 == itens.size()) {
            break;
        }

        if (crouch) {
            Dspace = colision(HitboxA, temp.rect);
            if ((Dspace.x+Dspace.y) != 0) {
                collect(temp);
                itens.erase(pos);
                // DrawText(TextFormat("Removendo item: %d", CIs[i]), GetScreenWidth()-300, 350, 20, WHITE);
                break;
            }
        } else {
            Dspace = colision(Hitbox1, temp.rect);
            if ((Dspace.x+Dspace.y) != 0) {
                collect(temp);
                itens.erase(pos);
                // DrawText(TextFormat("Removendo item: %d", CIs[i]), GetScreenWidth()-300, 350, 20, WHITE);
                break;
            }

            Dspace = colision(Hitbox2, temp.rect);
            if ((Dspace.x+Dspace.y) != 0) {
                collect(temp);
                itens.erase(pos);
                // DrawText(TextFormat("Removendo item: %d", CIs[i]), GetScreenWidth()-300, 350, 20, WHITE);
                break;
            }

            Dspace = colision(Hitbox3, temp.rect);
            if ((Dspace.x+Dspace.y) != 0) {
                collect(temp);
                itens.erase(pos);
                // DrawText(TextFormat("Removendo item: %d", CIs[i]), GetScreenWidth()-300, 350, 20, WHITE);
                break;
            }
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
            Health(1, 'P');
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
    } else if (item.name == "food-banana") { // Fun-mode
        score += 2;
        if (WP < MWP) {
            WP += 1;
        }
    } else if (item.name == "food-pear") { 
        score += 3;
        if (PP < MPP) {
            PP += 1;
        }
    } else if (item.name == "food-blueberry") {
        score += 4;
        if (FP < MFP) {
            FP += 1;
        }
    } else if (item.name == "food-pepper") {
        score += 6;
        if (HP < MHP) {
            HP += 1;
        }
    } else if (item.name == "food-orange") {
        score += 8;
        if (EP < MEP) {
            EP += 1;
        }
    } else if (item.name == "Hshard-hope") {
        PHH += 1;
        if (PHH == 3) {
            MHH += 7;
            HH += 7;
            PHH = 0;
        }
    } else if (item.name == "Hshard-resilience") {
        PRH += 1;
        if (PRH == 3) {
            MRH += 7;
            RH += 7;
            PRH = 0;
        }
    } else if (item.name == "Hshard-power") {
        PPH += 1;
        if (PPH == 3) {
            MPH += 7;
            PH += 7;
            PPH = 0;
        }
    } else if (item.name == "Hshard-courage") {
        PCH += 1;
        if (PCH == 3) {
            MCH += 7;
            CH += 7;
            PCH = 0;
        }
    } else if (item.name == "Hshard-wisdom") {
        PWH += 1;
        if (PWH == 3) {
            MWH += 7;
            WH += 7;
            PWH = 0;
        }
    } else if (item.name == "Pshard-wind") {
        PWP += 1;
        if (PWP == 3) {
            MWP += 7;
            WP += 7;
            PWP = 0;
        }
    } else if (item.name == "Pshard-party") {
        PPP += 1;
        if (PPP == 3) {
            MPP += 7;
            PP += 7;
            PPP = 0;
        }
    } else if (item.name == "Pshard-fun") {
        PFP += 1;
        if (PFP == 3) {
            MFP += 7;
            FP += 7;
            PFP = 0;
        }
    } else if (item.name == "Pshard-hard") {
        PHP += 1;
        if (PHP == 3) {
            MHP += 7;
            HP += 7;
            PHP = 0;
        }
    } else if (item.name == "Pshard-eloise") {
        PEP += 1;
        if (PEP == 3) {
            MEP += 7;
            EP += 7;
            PEP = 0;
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
        Health(7, 'C');
    } else if (item.name == "power-dash") {
        powers[0] = true;
    } else if (item.name == "power-transmutation") {
        powers[4] = true;
    } else if (item.name == "power-boost") {
        powers[2] = true;
    } else if (item.name == "power-spear") {
        powers[3] = true;
    }
}

Vector2 Flamingo::colision(Rectangle hitbox, Rectangle B) {
    float dx = 0, dy = 0;
    if (
        (hitbox.x + hitbox.width) > (B.x) and
        (hitbox.x) < (B.x + B.width) and
        (hitbox.y) < (B.y + B.height) and
        (hitbox.height + hitbox.y) > (B.y)
    ) {
        if (hitbox.x < B.x) {
            dx = B.x - (hitbox.x+hitbox.width);
        } else if (hitbox.x > B.x) {
            dx = (B.width + B.x) - hitbox.x;
        }
        if (hitbox.y < B.y) {
            dy = B.y - (hitbox.y+hitbox.height);
        } else if (hitbox.y > B.y) {
            dy = (B.height + B.y) - hitbox.y;
        }
    }
    return {dx, dy};
}

void Flamingo::Health(int qtd, char type) {
    if (qtd < 0) {
        invincibility[type] += 60;
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
*   Might cause bug: If blockColision does alterations to player that shouldn't be done out of the Physics check 
*/
bool Flamingo::CheckMirror(std::vector<Block> &Blocks) {
    Hitbox1.y = rect.y+15*SCALE;
    Hitbox2.y = rect.y+7*SCALE;
    Hitbox3.y = rect.y+1*SCALE;
    if (crouch) {
        return true;
    } else {
        int bsize = CBs.size();
        bool returning;
        if (lookingRight) {
            Hitbox1.x = rect.x+7*SCALE;
            Hitbox2.x = rect.x+4*SCALE;
            Hitbox3.x = rect.x;

            for (int i = 0; i < bsize; i++) {
                Block temp = Blocks[CBs[i]];

                if (blockColision(Hitbox1, temp, false) != 0) {
                    return false;
                }
                if (blockColision(Hitbox2, temp, false) != 0) {
                    return false;
                }
                if (blockColision(Hitbox3, temp, false) != 0) {
                    return false;
                }
            }
            Hitbox1.x = rect.x+6*SCALE;
            Hitbox2.x = rect.x+3*SCALE;
            Hitbox3.x = rect.x+9*SCALE;
        } else {
            Hitbox1.x = rect.x+6*SCALE;
            Hitbox2.x = rect.x+3*SCALE;
            Hitbox3.x = rect.x+9*SCALE;
            for (int i = 0; i < bsize; i++) {
                Block temp = Blocks[CBs[i]];

                if (blockColision(Hitbox1, temp, false) != 0) {
                    return false;
                }
                if (blockColision(Hitbox2, temp, false) != 0) {
                    return false;
                }
                if (blockColision(Hitbox3, temp, false) != 0) {
                    return false;
                }
            }
            Hitbox1.x = rect.x+7*SCALE;
            Hitbox2.x = rect.x+4*SCALE;
            Hitbox3.x = rect.x;
        }
    }
    return true;
}






