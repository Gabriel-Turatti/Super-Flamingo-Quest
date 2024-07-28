#include "../header/Flamingo.hpp"

   

Flamingo::Flamingo(float x, float y, float w, float h, int worldWidth, int worldHeight, int imagescale) {
        SetSoundVolume(sfxJump, 0.5);
        SetSoundVolume(sfxSecret, 0.4);
        SCALE = imagescale;

        rect.x = x;
        rect.y = y;
        rect.width = w;
        rect.height = h;

        WT = worldWidth;
        HT = worldHeight;

        vx = 0;
        vy = 0;

        cx = x+w*SCALE/2;
        cy = y+h*SCALE/2;

        Hitbox1 = Rectangle {rect.x+6*SCALE, rect.y+14*SCALE, 6.0f, 9.0f};
        Hitbox2 = Rectangle {rect.x+3*SCALE, rect.y+7*SCALE, 11.0f, 7.0f};
        Hitbox3 = Rectangle {rect.x+9*SCALE, rect.y, 9.0f, 8.0f};
        HitboxA = Rectangle {rect.x, rect.y, 18.0f, 16.0f};
        
        HB1 = {Hitbox1.x, Hitbox1.y+2, 6.0f, 9.0f};
    }

void Flamingo::update(std::vector<int> CBs, std::vector<Block> &map, std::vector<int> CIs, std::vector<Item> &itens) {
    keyPress();
    gravity();
    Physics(CBs, map);
    ItemColision(CIs, itens);
    if (tick % 300 == 0) {
        if (RH < MRH) {
            RH += 1;
        }
    }
    tick += 1;
}

void Flamingo::keyPress() {
    W = IsKeyDown(KEY_W);
    A = IsKeyDown(KEY_A);
    S = IsKeyDown(KEY_S);
    D = IsKeyDown(KEY_D);


    if (A) {
        lookingRight = false;
        if (ground) {
            vx = -naturalSpeed*SCALE/groundBlock.friction;
        } else {
            vx = -naturalSpeed*SCALE/2;
        }
    } else if (D) {
        lookingRight = true;
        if (ground) {
            vx = naturalSpeed*SCALE/groundBlock.friction;
        } else {
            vx = naturalSpeed*SCALE/2;
        }
    } else {
        vx = 0;
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
                HB1.height = HitboxA.height;
                HB1.width = HitboxA.width;
                rect.height = HitboxA.height;
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
        HB1.height = Hitbox1.height;
        HB1.width = Hitbox1.width;
        rect.height = 23;
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
}

void Flamingo::Physics(std::vector<int> CBs, std::vector<Block> &map) {
    // Horizontal Axis checing
    rect.x += vx;
    if (rect.y > 3000) {
        rect.y = -1000;
    }
    updateHitbox();
    int bsize = CBs.size();
    for (int i = 0; i < bsize; i++) {
        Block temp = map[CBs[i]];
        Vector2 DXspace;


        if (crouch) {
            DXspace = colision(HitboxA, temp.rect);
            rect.x += DXspace.x;
            if (DXspace.x != 0) {
                if (temp.secret) {
                    PlaySound(sfxSecret);
                    temp.secret = false;
                    temp.background = true;
                    map[CBs[i]] = temp;
                    continue;
                }
                if (temp.name == "gate-hope" and keyHope > 0) {
                    keyHope -= 1;
                    temp.background = true;
                    map[CBs[i]] = temp;
                    PlaySound(sfxDoor);
                }
                HitboxA.x += DXspace.x;
                vx = -vx/temp.friction;
                break;
            }
        } else {
            DXspace = colision(Hitbox1, temp.rect);
            rect.x += DXspace.x;
            if (DXspace.x != 0) {
                if (temp.secret) {
                    PlaySound(sfxSecret);
                    temp.secret = false;
                    temp.background = true;
                    map[CBs[i]] = temp;
                    continue;
                }
                if (temp.name == "gate-hope" and keyHope > 0) {
                    keyHope -= 1;
                    temp.background = true;
                    map[CBs[i]] = temp;
                    PlaySound(sfxDoor);
                }
                Hitbox1.x += DXspace.x;
                Hitbox2.x += DXspace.x;
                Hitbox3.x += DXspace.x;
                vx = -vx/temp.friction;
                break;
            }
            
            DXspace = colision(Hitbox2, temp.rect);
            rect.x += DXspace.x;
            if (DXspace.x != 0) {
                if (temp.secret) {
                    PlaySound(sfxSecret);
                    temp.secret = false;
                    temp.background = true;
                    map[CBs[i]] = temp;
                    continue;
                }
                if (temp.name == "gate-hope" and keyHope > 0) {
                    keyHope -= 1;
                    temp.background = true;
                    map[CBs[i]] = temp;
                    PlaySound(sfxDoor);
                }
                Hitbox1.x += DXspace.x;
                Hitbox2.x += DXspace.x;
                Hitbox3.x += DXspace.x;
                vx = -vx/temp.friction;
                break;
            }
            
            DXspace = colision(Hitbox3, temp.rect);
            rect.x += DXspace.x;
            if (DXspace.x != 0) {
                if (temp.secret) {
                    PlaySound(sfxSecret);
                    temp.secret = false;
                    temp.background = true;
                    map[CBs[i]] = temp;
                    continue;
                }
                if (temp.name == "gate-hope" and keyHope > 0) {
                    keyHope -= 1;
                    temp.background = true;
                    map[CBs[i]] = temp;
                    PlaySound(sfxDoor);
                }
                Hitbox1.x += DXspace.x;
                Hitbox2.x += DXspace.x;
                Hitbox3.x += DXspace.x;
                vx = -vx/temp.friction;
                break;
            }

        }
    }




    // Vertical Axis checking
    rect.y += vy;
    updateHitbox();
    

    ground = false;
    for (int i = 0; i < bsize; i++) {
        Block temp = map[CBs[i]];
        Vector2 DYspace;

        if (groundCheck(temp)) {
            ground = true;
            groundBlock = temp;
        }

        if (crouch) {
            DYspace = colision(HitboxA, temp.rect);
            rect.y += DYspace.y;
            if (DYspace.y != 0) {
                if (temp.secret) {
                    PlaySound(sfxSecret);
                    temp.secret = false;
                    temp.background = true;
                    map[CBs[i]] = temp;
                    continue;
                }
                if (temp.name == "gate-hope" and keyHope > 0) {
                    keyHope -= 1;
                    temp.background = true;
                    map[CBs[i]] = temp;
                    PlaySound(sfxDoor);
                }
                HitboxA.y += DYspace.y;
                vy = -vy/temp.friction;
                if (abs(vy) > 7*SCALE) {
                    Health(-(((int)abs(vy) - 7*SCALE)/2), 'R');
                }
                break;
            }
        } else {
            DYspace = colision(Hitbox1, temp.rect);
            rect.y += DYspace.y;
            if (DYspace.y != 0) {
                if (temp.secret) {
                    PlaySound(sfxSecret);
                    temp.secret = false;
                    temp.background = true;
                    map[CBs[i]] = temp;
                    continue;
                }
                if (temp.name == "gate-hope" and keyHope > 0) {
                    keyHope -= 1;
                    temp.background = true;
                    map[CBs[i]] = temp;
                    PlaySound(sfxDoor);
                }
                Hitbox1.y += DYspace.y;
                Hitbox2.y += DYspace.y;
                Hitbox3.y += DYspace.y;
                if (DYspace.y < 0) {
                    canJump = true;
                }
                if (abs(vy) > 7*SCALE) {
                    Health(-(((int)abs(vy) - 7*SCALE)/2), 'R');
                }
                vy = -vy/temp.friction;
                break;
            }

            DYspace = colision(Hitbox2, temp.rect);
            rect.y += DYspace.y;
            if (DYspace.y != 0) {
                if (temp.secret) {
                    PlaySound(sfxSecret);
                    temp.secret = false;
                    temp.background = true;
                    map[CBs[i]] = temp;
                    continue;
                }
                if (temp.name == "gate-hope" and keyHope > 0) {
                    keyHope -= 1;
                    temp.background = true;
                    map[CBs[i]] = temp;
                    PlaySound(sfxDoor);
                }
                Hitbox1.y += DYspace.y;
                Hitbox2.y += DYspace.y;
                Hitbox3.y += DYspace.y;
                if (DYspace.y < 0) {
                    canJump = true;
                }
                if (abs(vy) > 7*SCALE) {
                    Health(-(((int)abs(vy) - 7*SCALE)/2), 'R');
                }
                vy = -vy/temp.friction;
                break;
            }
            
            DYspace = colision(Hitbox3, temp.rect);
            rect.y += DYspace.y;
            if (DYspace.y != 0) {
                if (temp.secret) {
                    PlaySound(sfxSecret);
                    temp.secret = false;
                    temp.background = true;
                    map[CBs[i]] = temp;
                    continue;
                }
                if (temp.name == "gate-hope" and keyHope > 0) {
                    keyHope -= 1;
                    temp.background = true;
                    map[CBs[i]] = temp;
                    PlaySound(sfxDoor);
                }
                Hitbox1.y += DYspace.y;
                Hitbox2.y += DYspace.y;
                Hitbox3.y += DYspace.y;
                if (DYspace.y < 0) {
                    canJump = true;
                }
                if (abs(vy) > 7*SCALE) {
                    Health(-(((int)abs(vy) - 7*SCALE)/2), 'R');
                }
                vy = -vy/temp.friction;
                break;
            }
        }
    }

    
    cx = rect.x + rect.width*SCALE/2;
    cy = rect.y + rect.height*SCALE/2;
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
    if (crouch) {
        HB1.x = HitboxA.x;
        HB1.y = HitboxA.y+2;
    } else {
        HB1.x = Hitbox1.x;
        HB1.y = Hitbox1.y+2;
    }
    Vector2 C1 = colision(HB1, ground.rect);
    if (abs(C1.y)+abs(C1.x) > 0) {
        return true;
    }
    return false;
}

void Flamingo::updateHitbox() {
    if (crouch) {
        HitboxA.x = rect.x;
        HitboxA.y = rect.y;
    } else {
        if (lookingRight) {
            Hitbox1.x = rect.x+6*SCALE;
            Hitbox2.x = rect.x+3*SCALE;
            Hitbox3.x = rect.x+9*SCALE;
        } else {
            Hitbox1.x = rect.x+7*SCALE;
            Hitbox2.x = rect.x+4*SCALE;
            Hitbox3.x = rect.x;
        }
        Hitbox1.y = rect.y+14*SCALE;
        Hitbox2.y = rect.y+7*SCALE;
        Hitbox3.y = rect.y+1*SCALE;
    }
}

void Flamingo::ItemColision (std::vector<int> CIs, std::vector<Item> &itens) {
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
    }

    if (item.name == "copper-coin") {
        score += 5;
    } else if (item.name == "silver-coin") {
        score += 25;
    } else if (item.name == "gold-coin") {
        score += 100;
    } else if (item.name == "food-banana") {
        score += 2;
    } else if (item.name == "food-pear") {
        score += 3;
    } else if (item.name == "food-blueberry") {
        score += 4;
    } else if (item.name == "food-pepper") {
        score += 6;
    } else if (item.name == "food-orange") {
        score += 8;
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
    } else if (item.name == "key-hope") {
        keyHope += 1;
    }
}

Vector2 Flamingo::colision(Rectangle hitbox, Rectangle B) {
    float dx = 0, dy = 0;
    if (
        (hitbox.x + hitbox.width*SCALE) > (B.x) and
        (hitbox.x) < (B.x + B.width*SCALE) and
        (hitbox.y) < (B.y + B.height*SCALE) and
        (hitbox.height*SCALE + hitbox.y) > (B.y)
    ) {
        if (hitbox.x < B.x) {
            dx = B.x - (hitbox.x+hitbox.width*SCALE);
        } else if (hitbox.x > B.x) {
            dx = (B.width*SCALE + B.x) - hitbox.x;
        }
        if (hitbox.y < B.y) {
            dy = B.y - (hitbox.y+hitbox.height*SCALE);
        } else if (hitbox.y > B.y) {
            dy = (B.height*SCALE + B.y) - hitbox.y;
        }
    }
    return {dx, dy};
}

void Flamingo::Health(int qtd, char type) {
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
        return;
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