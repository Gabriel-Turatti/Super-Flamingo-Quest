#include "raylib.h"
#include <string>
#include <vector>
#include <fstream>
#include <random>


class Block {
public:
    Rectangle rect;
    float cx, cy;
    float friction;
    Texture2D image;
    int SCALE;
    bool background = false, secret = false, rotate = false;
    std::string name;

    Block(int x, int y, int w, int h, std::string namer, int SCALER, bool rotator = false) {
        if (namer == "grass") {
            image = LoadTexture("images/block_grass.png");
            friction = 2.5;
        } else if (namer == "dirt2") {
            image = LoadTexture("images/block_dirt2x2.png");
            friction = 4;
        } else if (namer == "dirt") {
            image = LoadTexture("images/block_dirt.png");
            friction = 4;
        } else if (namer == "gate-hope") {
            image = LoadTexture("images/block_gates.png");
            friction = 1.5;
            rotate = rotator;
        }
        rect.x = x;
        rect.y = y;
        SCALE = SCALER;
        rect.width = w;
        rect.height = h;
        name = namer;
        if (rotate) {
            rect.height = w;
            rect.width = h;
        }
        cx = x+w*SCALE/2;
        cy = y+h*SCALE/2;
    }
    Block() {}
};

class Item {
public:
    Rectangle rect;
    float cx, cy;
    std::string name;
    char category;
    Texture2D image;
    int SCALE;
    Item(int x, int y, std::string namer, int SCALER) {
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
};

class Flamingo {
public:
    Rectangle rect;
    float cx, cy;
    float vx, vy;

    Rectangle Hitbox1, Hitbox2, Hitbox3, HitboxA; // Leg, Chest, Head, Crouch

    std::vector<Texture2D> images = {
        LoadTexture("images/Flamingo1.png"),
        LoadTexture("images/Flamingo2.png"),
        LoadTexture("images/Flamingo3.png"),
        LoadTexture("images/FlamingoS.png"),
        LoadTexture("images/FlamingoF.png"),
        LoadTexture("images/FlamingoA.png"),
    };
    int imageCount = 0;
    int imageSize = 2;

    Texture2D HeartGrid = LoadTexture("Images/heart_health.png"); // Corações de vida, cada coração tem 7 pontos de vida
    int MHH = 4*7; // Hope Health
    int MRH = 3*7; // Resilience Health
    int MPH = 2*7; // Power Health
    int MCH = 2*7; // Courage Health
    int MWH = 1*7; // Wisdom Health

    int HH = 4*7;
    int RH = 3*7;
    int PH = 2*7;
    int CH = 2*7;
    int WH = 1*7;

    int PHH = 0;
    int PRH = 0;
    int PPH = 0;
    int PCH = 0;
    int PWH = 0;

    Rectangle HB1;
    Sound sfxCoin = LoadSound("sfx/coin.wav"); 
    Sound sfxFood = LoadSound("sfx/eat.wav"); 
    Sound sfxJump = LoadSound("sfx/jump.wav");
    Sound sfxHeartPiece = LoadSound("sfx/HeartPiece.wav");
    Sound sfxSecret = LoadSound("sfx/secret.wav");
    Sound sfxKey = LoadSound("sfx/key.wav");
    Sound sfxDoor = LoadSound("sfx/door.wav");


    int WT, HT, SCALE;
    int naturalSpeed = 6;
    int tick = 1;
    int score = 0;

    bool W, A, S, D;
    bool canJump = true;
    bool ground = false;
    Block groundBlock;
    bool lookingRight = true;
    bool crouch = false;
    int jumpQueue = 0;
    bool gameover = false;

    int keyHope = 0;

    Flamingo(float x, float y, float w, float h, int worldWidth, int worldHeight, int imagescale) {
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

    void update(std::vector<int> CBs, std::vector<Block> &map, std::vector<int> CIs, std::vector<Item> &itens) {
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

    void keyPress() {
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

    void gravity() {
        vy += 0.25*SCALE;
    }

    void Physics(std::vector<int> CBs, std::vector<Block> &map) {
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

    bool groundCheck(Block ground) {
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

    void updateHitbox() {
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

    void ItemColision (std::vector<int> CIs, std::vector<Item> &itens) {
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

    void collect(Item item) {
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

    Vector2 colision(Rectangle hitbox, Rectangle B) {
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

    void Health(int qtd, char type) {
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
};

void DesenharHeart(Flamingo player) {
    int SCALE = player.SCALE;
    Rectangle PHud = {10.0f, 10.0f, 11.0f*SCALE, 11.0f*SCALE};
    // Hope
    int HHTemp = player.HH/7;
    int HHPart = player.HH % 7;
    int HHEmptyTemp = (player.MHH - player.HH)/7;
    while (HHTemp > 0) {
        DrawTexturePro(player.HeartGrid, {0.0f, 0.0f, 11.0f, 11.0f}, PHud, {0, 0}, 0, WHITE);
        PHud.x += 12*SCALE;
        HHTemp--;
    }
    if (HHPart > 0) {
        DrawTexturePro(player.HeartGrid, {(12.0f*(7-HHPart)), 0.0f, 11.0f, 11.0f}, PHud, {0, 0}, 0, WHITE);
        PHud.x += 12*SCALE;
    }
    while (HHEmptyTemp > 0) {
        DrawTexturePro(player.HeartGrid, {12.0f*7, 0.0f, 11.0f, 11.0f}, PHud, {0, 0}, 0, WHITE);
        PHud.x += 12*SCALE;
        HHEmptyTemp--;
    }
    if (player.PHH > 0) {
        DrawText(TextFormat("+%d", player.PHH), PHud.x, PHud.y, 35, YELLOW);
    }

    PHud.x = 10.0f;
    PHud.y += 12.0f*SCALE;
    
    
    
    // Resilience
    int RHTemp = player.RH/7;
    int RHPart = player.RH % 7;
    int RHEmptyTemp = (player.MRH - player.RH)/7;
    while (RHTemp > 0) {
        DrawTexturePro(player.HeartGrid, {0.0f, 12.0f, 11.0f, 11.0f}, PHud, {0, 0}, 0, WHITE);
        PHud.x += 12*SCALE;
        RHTemp--;
    }
    if (RHPart > 0) {
        DrawTexturePro(player.HeartGrid, {(12.0f*(7-RHPart)), 12.0f, 11.0f, 11.0f}, PHud, {0, 0}, 0, WHITE);
        PHud.x += 12*SCALE;
    }
    while (RHEmptyTemp > 0) {
        DrawTexturePro(player.HeartGrid, {12.0f*7, 12.0f, 11.0f, 11.0f}, PHud, {0, 0}, 0, WHITE);
        PHud.x += 12*SCALE;
        RHEmptyTemp--;
    }
    if (player.PRH > 0) {
        DrawText(TextFormat("+%d", player.PRH), PHud.x, PHud.y, 35, GREEN);
    }

    PHud.x = 10.0f;
    PHud.y += 12.0f*SCALE;
    
    
    
    // Power
    int PHTemp = player.PH/7;
    int PHPart = player.PH % 7;
    int PHEmptyTemp = (player.MPH - player.PH)/7;
    while (PHTemp > 0) {
        DrawTexturePro(player.HeartGrid, {0.0f, 12.0f*2, 11.0f, 11.0f}, PHud, {0, 0}, 0, WHITE);
        PHud.x += 12*SCALE;
        PHTemp--;
    }
    if (PHPart > 0) {
        DrawTexturePro(player.HeartGrid, {(12.0f*(7-PHPart)), 12.0f*2, 11.0f, 11.0f}, PHud, {0, 0}, 0, WHITE);
        PHud.x += 12*SCALE;
    }
    while (PHEmptyTemp > 0) {
        DrawTexturePro(player.HeartGrid, {12.0f*7, 12.0f*2, 11.0f, 11.0f}, PHud, {0, 0}, 0, WHITE);
        PHud.x += 12*SCALE;
        PHEmptyTemp--;
    }
    if (player.PPH > 0) {
        DrawText(TextFormat("+%d", player.PPH), PHud.x, PHud.y, 35, DARKBLUE);
    }

    PHud.x = 10.0f;
    PHud.y += 12.0f*SCALE;
    
    
    
    // Courage
    int CHTemp = player.CH/7;
    int CHPart = player.CH % 7;
    int CHEmptyTemp = (player.MCH - player.CH)/7;
    while (CHTemp > 0) {
        DrawTexturePro(player.HeartGrid, {0.0f, 12.0f*3, 11.0f, 11.0f}, PHud, {0, 0}, 0, WHITE);
        PHud.x += 12*SCALE;
        CHTemp--;
    }
    if (CHPart > 0) {
        DrawTexturePro(player.HeartGrid, {(12.0f*(7-CHPart)), 12.0f*3, 11.0f, 11.0f}, PHud, {0, 0}, 0, WHITE);
        PHud.x += 12*SCALE;
    }
    while (CHEmptyTemp > 0) {
        DrawTexturePro(player.HeartGrid, {12.0f*7, 12.0f*3, 11.0f, 11.0f}, PHud, {0, 0}, 0, WHITE);
        PHud.x += 12*SCALE;
        CHEmptyTemp--;
    }
    if (player.PCH > 0) {
        DrawText(TextFormat("+%d", player.PCH), PHud.x, PHud.y, 35, RED);
    }

    PHud.x = 10.0f;
    PHud.y += 12.0f*SCALE;
    
    
    
    // Wisdom
    int WHTemp = player.WH/7;
    int WHPart = player.WH % 7;
    int WHEmptyTemp = (player.MWH - player.WH)/7;
    while (WHTemp > 0) {
        DrawTexturePro(player.HeartGrid, {0.0f, 12.0f*4, 11.0f, 11.0f}, PHud, {0, 0}, 0, WHITE);
        PHud.x += 12*SCALE;
        WHTemp--;
    }
    if (WHPart > 0) {
        DrawTexturePro(player.HeartGrid, {(12.0f*(7-WHPart)), 12.0f*4, 11.0f, 11.0f}, PHud, {0, 0}, 0, WHITE);
        PHud.x += 12*SCALE;
    }
    while (WHEmptyTemp > 0) {
        DrawTexturePro(player.HeartGrid, {12.0f*7, 12.0f*4, 11.0f, 11.0f}, PHud, {0, 0}, 0, WHITE);
        PHud.x += 12*SCALE;
        WHEmptyTemp--;
    }
    if (player.PWH > 0) {
        DrawText(TextFormat("+%d", player.PWH), PHud.x, PHud.y, 35, ORANGE);
    }
}


int main(void) {
    const int SCALE = 3;
    const int BS = 13;
    const int WT = BS*34*SCALE;
    const int HT = BS*25*SCALE;
    const float FW = 18;
    const float FH = 23;
    int tickBlockUpdate = 5;
    int tick = 1;
    int seconds = 0;

    InitWindow(WT, HT, "Super Flamingo Quest 0.3 - Flamingos Have Five-Lives");


    InitAudioDevice();
    Music songMainTheme = LoadMusicStream("songs/MainTheme.wav");

    Flamingo player(400, 400, FW, FH, WT, HT, SCALE);

    std::vector<Block> map;
    std::vector<Item> itens;
    std::ifstream level("levels/teste.txt");
    // std::ifstream level("levels/testeSimplao.txt");
    if (!level) {
        level.close();
        return 1;
    }

    std::string line;
    int CHL; // Current Height Level (AKA. what column of blocks we are currently looking during the map load)
    int widthLevel;
    int heightLevel;
    std::getline(level, line);
    heightLevel = std::stoi(line);
    std::getline(level, line);
    widthLevel = std::stoi(line);

    int RenderPhase = 0; // 1 = Blocks; 2 = Itens;
    while (!level.eof()) {
        std::getline(level, line);
        if (line[0] == 'P') {
            CHL = 0;
            RenderPhase += 1;
            continue;
        }
        if (RenderPhase == 1) {
            for (int CWL = 0; CWL < widthLevel; CWL++) { // Current Width Level
                if (line[CWL] == '-' or line[CWL] == '|') {
                    continue;
                }
                if (line[CWL] == 'F') {
                    player.rect.x = CWL*(BS-1)*SCALE;
                    player.rect.y = CHL*(BS-1)*SCALE;
                    continue;
                }
                Block tile;
                if (line[CWL] == 'G') {
                    tile = Block(CWL*(BS-1)*SCALE, CHL*(BS-1)*SCALE, BS, BS, "grass", SCALE);
                } else if (line[CWL] == 'D') {
                    if (line[CWL+1] == '2') {
                        tile = Block(CWL*(BS-1)*SCALE, CHL*(BS-1)*SCALE, BS*2-1, BS*2-1, "dirt2", SCALE);
                        CWL++;
                    } else {
                        tile = Block(CWL*(BS-1)*SCALE, CHL*(BS-1)*SCALE, BS, BS, "dirt", SCALE);
                    }
                } else if (line[CWL] = 'H') {
                    bool rotation = false;
                    std::string type;
                    if (line[CWL-1] == '|') {
                        rotation = true;
                    }
                    if (line[CWL+1] == 'h') {
                        type = "hope";
                    }
                    tile = Block(CWL*(BS-1)*SCALE, CHL*(BS-1)*SCALE, BS, BS*2-1, "gate-" + type, SCALE, rotation);
                    CWL++;
                }
                map.push_back(tile);
            }
            CHL++;
        } else if (RenderPhase == 2) {
            int i = 0;
            int CWL;
            std::string text = "";
            std::string name = "";
            for (; line[i] != '-'; i++) {
                if (isdigit(line[i])) {
                    text += line[i];
                }
            }
            i++;
            CWL = std::stoi(text);
            text = "";


            for (; line[i] != '-'; i++) {
                if (isdigit(line[i])) {
                    text += line[i];
                }
            }
            i++;
            CHL = std::stoi(text);
            text = "";


            for (; line[i] != '\0'; i++) {
                if (line[i] == '\"') {
                    continue;
                }
                text += line[i];
            }
            name = text;

            Item novoItem(CHL*(BS-1)*SCALE, CWL*(BS-1)*SCALE, name, SCALE);
            itens.push_back(novoItem);
        }

    }
    level.close();

    int sizeB = map.size();
    int sizeI = itens.size();
    Vector2 mousePosition;
    std::vector<int> colisionBlocks; // List of blocks that can collide with player
    std::vector<int> colisionItens; // List of itens that can collide with player
    float maxV = 0;
    SetTargetFPS(30);
    PlayMusicStream(songMainTheme);




    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> RNG100(0, 100);
    std::uniform_int_distribution<std::mt19937::result_type> RNGWidth(0, widthLevel);
    std::uniform_int_distribution<std::mt19937::result_type> RNGHeight(0, heightLevel);
    while (!WindowShouldClose()) {
        UpdateMusicStream(songMainTheme);
        // Player Collision
        if (tick % tickBlockUpdate == 0) {
            colisionBlocks.clear();
            for (int i = 0; i < sizeB; i++) {
                if (map[i].background) {
                    continue;
                }
                int dx = abs(map[i].cx - player.cx);
                if (dx < player.rect.width*2*SCALE) {
                    int dy = abs(map[i].cy - player.cy);
                    if (dy < player.rect.height*2*SCALE) {
                        colisionBlocks.push_back(i);
                    }
                }
            }


            colisionItens.clear();
            for (int i = 0; i < sizeI; i++) {
                int dx = abs(itens[i].cx - player.cx);
                if (dx < player.rect.width*2*SCALE) {
                    int dy = abs(itens[i].cy - player.cy);
                    if (dy < player.rect.height*2*SCALE) {
                        colisionItens.push_back(i);
                    }
                }
            }
        }


        // Entities Updates
        player.update(colisionBlocks, map, colisionItens, itens);

        if (abs(player.vy) > 12) {
            tickBlockUpdate = 2;
        } else {
            tickBlockUpdate = 5;
        }

        mousePosition = GetMousePosition();

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            player.rect.x = mousePosition.x;
            player.rect.y = mousePosition.y;
        }

        if (tick % 30 == 0) {
            seconds += 1;
        }




        // Desenhando coisas
        BeginDrawing();
        ClearBackground(BLUE);



        Rectangle center = {WT/2, HT/2, SCALE*player.rect.width, SCALE*player.rect.height};
        // Desenhando blocos Background
        for (int i = 0; i < sizeB; i++) {
            if (!map[i].background) {
                continue;
            }
            Vector2 relativePos;
            relativePos.x = center.x +map[i].rect.x -player.rect.x;
            relativePos.y = center.y +map[i].rect.y -player.rect.y;
            
            if (map[i].name == "gate-hope") {
                Rectangle cut, dest;
                dest.x = relativePos.x;
                dest.y = relativePos.y;
                dest.width = 13*SCALE;
                dest.height = 25*SCALE;

                cut.x = 0;
                cut.y = 0;
                cut.width = 13;
                cut.height = 25;
                DrawTexturePro(map[i].image, cut, dest, {0, 0}, 0, GRAY);
            } else {
                DrawTextureEx(map[i].image, relativePos, 0, SCALE, GRAY);
            }
        }

        // Desenhando Player
        Color playerColor = WHITE;
        if (player.gameover) {
            playerColor = GRAY;
        }
        if (player.lookingRight) {
            DrawTexturePro(player.images[player.imageCount], {0.0f, 0.0f, player.rect.width, player.rect.height}, center, {0, 0}, 0, playerColor);
        } else {
            DrawTexturePro(player.images[player.imageCount], {0.0f, 0.0f, -player.rect.width, player.rect.height}, center, {0, 0}, 0, playerColor);
        }
        // Desenhando blocos Ground
        for (int i = 0; i < sizeB; i++) {
            if (map[i].background) {
                continue;
            }
            Vector2 relativePos;
            relativePos.x = center.x +map[i].rect.x -player.rect.x;
            relativePos.y = center.y +map[i].rect.y -player.rect.y;
            if (map[i].name == "gate-hope") {
                Rectangle cut, dest;
                dest.x = relativePos.x;
                dest.y = relativePos.y;
                dest.width = 13*SCALE;
                dest.height = 25*SCALE;

                cut.x = 0;
                cut.y = 24;
                cut.width = 13;
                cut.height = 25;
                DrawTexturePro(map[i].image, cut, dest, {0, 0}, 0, playerColor);
            } else {
                DrawTextureEx(map[i].image, relativePos, 0, SCALE, WHITE);
            }
        }
        // Desenhando itens
        sizeI = itens.size();
        for (int i = 0; i < sizeI; i++) {
            Vector2 relativePos;
            relativePos.x = center.x +itens[i].rect.x -player.rect.x;
            relativePos.y = center.y +itens[i].rect.y -player.rect.y;
            DrawTextureEx(itens[i].image, relativePos, 0, SCALE, WHITE);
        }



        // fun-mode
        if (tick % 50 == 0 and sizeI < 100) {
            int RNG_X = (RNGWidth(rng))*(BS-1)*SCALE;
            int RNG_Y = (RNGHeight(rng))*(BS-1)*SCALE;
            bool freespace = true;
            for (int i = 0; i < sizeB; i++) {
                Block temp = map[i];
                if (temp.rect.x == RNG_X and temp.rect.y == RNG_Y) { 
                    freespace = false;
                    break;
                }
            }
            if (freespace) {
                int value = RNG100(rng);
                if (value <= 1) {
                    itens.push_back(Item(RNG_X, RNG_Y, "Hshard-wisdom", SCALE));
                } else if (value <= 4) {
                    itens.push_back(Item(RNG_X, RNG_Y, "Hshard-harder", SCALE));
                } else if (value <= 7) {
                    itens.push_back(Item(RNG_X, RNG_Y, "Hshard-power", SCALE));
                } else if (value <= 10) {
                    itens.push_back(Item(RNG_X, RNG_Y, "Hshard-resilience", SCALE));
                } else if (value <= 14) {
                    itens.push_back(Item(RNG_X, RNG_Y, "Hshard-hope", SCALE));
                } else if (value <= 16) {
                    itens.push_back(Item(RNG_X, RNG_Y, "gold-coin", SCALE));
                } else if (value <= 18) {
                    itens.push_back(Item(RNG_X, RNG_Y, "silver-coin", SCALE));
                } else if (value <= 25) {
                    itens.push_back(Item(RNG_X, RNG_Y, "copper-coin", SCALE));
                } else if (value <= 33) {
                    itens.push_back(Item(RNG_X, RNG_Y, "food-orange", SCALE));
                } else if (value <= 48) {
                    itens.push_back(Item(RNG_X, RNG_Y, "food-pepper", SCALE));
                } else if (value <= 65) {
                    itens.push_back(Item(RNG_X, RNG_Y, "food-blueberry", SCALE));
                } else if (value <= 80) {
                    itens.push_back(Item(RNG_X, RNG_Y, "food-pear", SCALE));
                } else if (value <= 100) {
                    itens.push_back(Item(RNG_X, RNG_Y, "food-banana", SCALE));
                }
                sizeI += 1;
            }
        }


        // Desenhando HUD
        DesenharHeart(player);
        DrawText(TextFormat("Score: %d", player.score), GetScreenWidth()-200, 0, 20, WHITE);
        DrawText(TextFormat("Time: %d", seconds), GetScreenWidth()/2-100, 0, 20, WHITE);
        if (player.keyHope > 0) {
            DrawText(TextFormat("Yellow Keys - %d", player.keyHope), GetScreenWidth() - 200, 50, 20, WHITE);
        }






        // DrawTexturePro(player.image, player.rect, player.rect, {static_cast<float>(player.rect.w), static_cast<float>(player.rect.h)}, 0, WHITE);
        // DrawTexture(player.image, player.rect.x, player.rect.y, WHITE);
        // DrawText(Texto, Lin, Col, Tam, Color)






        // DEBUG
        // if (colisionItens.size() > 0) {
        //     DrawText(TextFormat("item Prox: %d", colisionItens[0]), GetScreenWidth()-300, 220, 20, WHITE);
        //     DrawText(TextFormat("Tamanho itens: %d", itens.size()), GetScreenWidth()-300, 280, 20, WHITE);
        // }
        DrawText(TextFormat("itens no mapa: %d", itens.size()), GetScreenWidth()-300, 220, 20, WHITE);
        // DrawText(TextFormat("CURRENT FPS: %i", (int)(1.0f/deltaTime)), GetScreenWidth() - 220, 40, 20, GREEN);
        
        // DrawRectangle(250, 250, 120, 60, RED);
        
        // Vector2 relativePos;
        // relativePos.x = center.x +player.HitboxA.x -player.rect.x;
        // relativePos.y = center.y +player.HitboxA.y -player.rect.y;
        // DrawRectangle(relativePos.x, relativePos.y, player.HitboxA.width*SCALE, player.HitboxA.height*SCALE, GREEN);
        // relativePos.x = center.x +player.Hitbox1.x -player.rect.x;
        // relativePos.y = center.y +player.Hitbox1.y -player.rect.y;
        // DrawRectangle(relativePos.x, relativePos.y, player.Hitbox1.width*SCALE, player.Hitbox1.height*SCALE, RED);
        // relativePos.x = center.x +player.Hitbox2.x -player.rect.x;
        // relativePos.y = center.y +player.Hitbox2.y -player.rect.y;
        // DrawRectangle(relativePos.x, relativePos.y, player.Hitbox2.width*SCALE, player.Hitbox2.height*SCALE, RED);
        // relativePos.x = center.x +player.Hitbox3.x -player.rect.x;
        // relativePos.y = center.y +player.Hitbox3.y -player.rect.y;
        // DrawRectangle(relativePos.x, relativePos.y, player.Hitbox3.width*SCALE, player.Hitbox3.height*SCALE, RED);
        // relativePos.x = center.x +player.HB1.x -player.rect.x;
        // relativePos.y = center.y +player.HB1.y -player.rect.y;
        // DrawRectangle(relativePos.x, relativePos.y, player.HB1.width*SCALE, player.HB1.height*SCALE, DARKBLUE);

        // relativePos.x = center.x;
        // relativePos.y = center.y;
        // DrawRectangle(relativePos.x, relativePos.y, 1*SCALE, 1*SCALE, PURPLE);
        // if (tick % 30 == 0) {
        //     maxV = 0;
        // }
        // if (abs(player.vy) > abs(maxV)) {
        //     maxV = player.vy;
        // }
        // DrawText(TextFormat("CURRENT V-Speed: %02.02f", -maxV), 20, 40, 20, GREEN);

        EndDrawing();
        tick++;
    }


    UnloadMusicStream(songMainTheme);
    CloseAudioDevice();

    CloseWindow();
    return 0;
}