#include "raylib.h"
#include <string>
#include <vector>
#include <fstream>


class Block {
public:
    Rectangle rect;
    float cx, cy;
    float friction;
    Texture2D image;
    int SCALE;
    Block(int x, int y, int w, int h, std::string name, int SCALER) {
        if (name == "grass") {
            image = LoadTexture("images/block_grass.png");
            friction = 2.5;
        } else if (name == "dirt2") {
            image = LoadTexture("images/block_dirt2x2.png");
            friction = 4;
        } else if (name == "dirt") {
            image = LoadTexture("images/block_dirt.png");
            friction = 4;
        }
        rect.x = x;
        rect.y = y;
        SCALE = SCALER;
        rect.width = w;
        rect.height = h;
        cx = x+w*SCALE/2;
        cy = y+h*SCALE/2;
    }
    Block() {}
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
    int MRH = 8*7; // Resilience Health
    int MPH = 2*7; // Power Health
    int MCH = 2*7; // Courage Health
    int MWH = 1*7; // Wisdom Health

    int HH = 4*7;
    int RH = 3*7;
    int PH = 2*7;
    int CH = 2*7;
    int WH = 1*7;

    Rectangle HB1;



    int WT, HT, SCALE;
    int naturalSpeed = 3;
    int tick = 1;

    bool W, A, S, D;
    bool canJump = true;
    bool ground = false;
    Block groundBlock;
    bool lookingRight = true;
    bool crouch = false;
    int jumpQueue = 0;

    Flamingo(float x, float y, float w, float h, int worldWidth, int worldHeight, int imagescale) {
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

    void update(std::vector<int> CBs, std::vector<Block> map) {
        keyPress();
        gravity();
        Physics(CBs, map);
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

    void Physics(std::vector<int> CBs, std::vector<Block> map) {
        // Horizontal Axis checing
        rect.x += vx;
        updateHitbox();
        int bsize = CBs.size();
        for (int i = 0; i < bsize; i++) {
            Block temp = map[CBs[i]];
            Vector2 DXspace;
            
            if (crouch) {
                DXspace = colision(HitboxA, temp.rect);
                rect.x += DXspace.x;
                if (DXspace.x != 0) {
                    HitboxA.x += DXspace.x;
                    vx = -vx/temp.friction;
                    break;
                }
            } else {
                // DrawText(TextFormat("Calculating X Colision for non-crouching sprite"), 60, 90, 20, RED);
                DXspace = colision(Hitbox1, temp.rect);
                rect.x += DXspace.x;
                if (DXspace.x != 0) {
                    // Hitbox1.x -= vx;
                    // Hitbox2.x -= vx;
                    // Hitbox3.x -= vx;
                    Hitbox1.x += DXspace.x;
                    Hitbox2.x += DXspace.x;
                    Hitbox3.x += DXspace.x;
                    vx = -vx/temp.friction;
                    break;
                }
                
                DXspace = colision(Hitbox2, temp.rect);
                rect.x += DXspace.x;
                if (DXspace.x != 0) {
                    // Hitbox1.x -= vx;
                    // Hitbox2.x -= vx;
                    // Hitbox3.x -= vx;
                    Hitbox1.x += DXspace.x;
                    Hitbox2.x += DXspace.x;
                    Hitbox3.x += DXspace.x;
                    vx = -vx/temp.friction;
                    break;
                }
                
                DXspace = colision(Hitbox3, temp.rect);
                rect.x += DXspace.x;
                if (DXspace.x != 0) {
                    // Hitbox1.x -= vx;
                    // Hitbox2.x -= vx;
                    // Hitbox3.x -= vx;
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
                    HitboxA.y += DYspace.y;
                    vy = -vy/temp.friction;
                    // break;
                }
            } else {
                DYspace = colision(Hitbox1, temp.rect);
                rect.y += DYspace.y;
                if (DYspace.y != 0) {
                    // Hitbox1.y -= vy;
                    // Hitbox2.y -= vy;
                    // Hitbox3.y -= vy;
                    Hitbox1.y += DYspace.y;
                    Hitbox2.y += DYspace.y;
                    Hitbox3.y += DYspace.y;
                    if (DYspace.y < 0) {
                        canJump = true;
                    }
                    if (abs(vy) > 7*SCALE) {
                        RH -= ((int)abs(vy) - 7*SCALE)/2;
                    }
                    vy = -vy/temp.friction;
                    break;
                }

                DYspace = colision(Hitbox2, temp.rect);
                rect.y += DYspace.y;
                if (DYspace.y != 0) {
                    // Hitbox1.y -= vy;
                    // Hitbox2.y -= vy;
                    // Hitbox3.y -= vy;
                    Hitbox1.y += DYspace.y;
                    Hitbox2.y += DYspace.y;
                    Hitbox3.y += DYspace.y;
                    if (DYspace.y < 0) {
                        canJump = true;
                    }
                    if (abs(vy) > 7*SCALE) {
                        RH -= ((int)abs(vy) - 7*SCALE)/2;
                    }
                    vy = -vy/temp.friction;
                    break;
                }
                
                DYspace = colision(Hitbox3, temp.rect);
                rect.y += DYspace.y;
                if (DYspace.y != 0) {
                    // Hitbox1.y -= vy;
                    // Hitbox2.y -= vy;
                    // Hitbox3.y -= vy;
                    Hitbox1.y += DYspace.y;
                    Hitbox2.y += DYspace.y;
                    Hitbox3.y += DYspace.y;
                    if (DYspace.y < 0) {
                        canJump = true;
                    }
                    if (abs(vy) > 7*SCALE) {
                        RH -= ((int)abs(vy) - 7*SCALE)/2;
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

    Vector2 colision(Rectangle hitbox, Rectangle B) {
        float dx = 0, dy = 0;
        if (
            (hitbox.x + hitbox.width*SCALE) > (B.x) and
            (hitbox.x) < (B.x + B.width*SCALE) and
            (hitbox.y) < (B.y + B.height*SCALE) and
            (hitbox.height*SCALE + hitbox.y) > (B.y)
        ) {
        // if ((int)(hitbox.x + hitbox.width*SCALE) > (int)(B.x) and
        // (int)(hitbox.x) < (int)(B.x + B.width*SCALE) and
        // (int)(hitbox.y) < (int)(B.y + B.height*SCALE) and
        // (int)(hitbox.height*SCALE + hitbox.y) > (int)(B.y)) {
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
            // return true;
        }
        // return false;
        return {dx, dy};
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

    InitWindow(WT, HT, "Super Flamingo Quest 0.3 - Flamingos Have Five-Lives");
    SetTargetFPS(30);

    Flamingo player(400, 400, FW, FH, WT, HT, SCALE);



    std::vector<Block> map;
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

    while (!level.eof()) {
        std::getline(level, line);
        if (line[0] == 'P') {
            CHL = 0;
            continue;
        }
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
            }
            if (line[CWL] == 'D') {
                if (line[CWL+1] == '2') {
                    tile = Block(CWL*(BS-1)*SCALE, CHL*(BS-1)*SCALE, BS*2-1, BS*2-1, "dirt2", SCALE);
                    CWL++;
                } else {
                    tile = Block(CWL*(BS-1)*SCALE, CHL*(BS-1)*SCALE, BS, BS, "dirt", SCALE);
                }
            }
            map.push_back(tile);
        }
        CHL++;
    }
    level.close();


    int sizeB = map.size();
    Vector2 mousePosition;
    std::vector<int> colisionBlocks; // List of blocks that can collide with player
    float maxV = 0;
    while (!WindowShouldClose()) {
        // Player Collision
        if (tick % tickBlockUpdate == 0) {
            colisionBlocks.clear();
            for (int i = 0; i < sizeB; i++) {
                int dx = abs(map[i].cx - player.cx);
                if (dx < player.rect.width*2*SCALE) {
                    int dy = abs(map[i].cy - player.cy);
                    if (dy < player.rect.height*2*SCALE) {
                        colisionBlocks.push_back(i);
                    }
                }
            }
        }

        // Entities Updates
        player.update(colisionBlocks, map);

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





        // Desenhando coisas
        BeginDrawing();
        ClearBackground(BLUE);

        // Desenhando Player
        Rectangle center = {WT/2, HT/2, SCALE*player.rect.width, SCALE*player.rect.height};
        if (player.lookingRight) {
            DrawTexturePro(player.images[player.imageCount], {0.0f, 0.0f, player.rect.width, player.rect.height}, center, {0, 0}, 0, WHITE);
        } else {
            DrawTexturePro(player.images[player.imageCount], {0.0f, 0.0f, -player.rect.width, player.rect.height}, center, {0, 0}, 0, WHITE);
        }
        // Desenhando blocos
        for (int i = 0; i < sizeB; i++) {
            Vector2 relativePos;
            relativePos.x = center.x +map[i].rect.x -player.rect.x;
            relativePos.y = center.y +map[i].rect.y -player.rect.y;
            DrawTextureEx(map[i].image, relativePos, 0, SCALE, WHITE);
        }
        




        // Desenhando HUD
        DesenharHeart(player);






        // DrawTexturePro(player.image, player.rect, player.rect, {static_cast<float>(player.rect.w), static_cast<float>(player.rect.h)}, 0, WHITE);
        // DrawTexture(player.image, player.rect.x, player.rect.y, WHITE);
        // DrawText(Texto, Lin, Col, Tam, Color)






        // DEBUG
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

    CloseWindow();
    return 0;
}