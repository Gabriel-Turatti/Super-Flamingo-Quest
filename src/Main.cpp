#include "raylib.h"
#include <string>
#include <vector>
#include <fstream>


class Block {
public:
    Rectangle rect;
    float cx, cy;
    Texture2D image;
    int SCALE;
    Block(int x, int y, int w, int h, std::string name, int SCALER) {
        if (name == "grass") {
            image = LoadTexture("images/block_grass.png");
        } else if (name == "dirt2") {
            image = LoadTexture("images/block_dirt2x2.png");
        } else if (name == "dirt") {
            image = LoadTexture("images/block_dirt.png");
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

    Rectangle Hitbox1, Hitbox2, Hitbox3; // Leg, Chest, Head

    std::vector<Texture2D> images = {
        LoadTexture("images/Flamingo1.png"),
        LoadTexture("images/Flamingo2.png"),
        LoadTexture("images/Flamingo3.png"),
        LoadTexture("images/FlamingoS.png"),
    };

    int imageCount = 0;
    int imageSize = 3;

    int WT, HT, SCALE;
    int tick = 1;
    
    bool W, A, S, D;
    bool ground = false;
    bool lookingRight = true;
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
        Hitbox3 = Rectangle {rect.x+9*SCALE, rect.y, 9.0f, 9.0f};
    }

    void update(std::vector<int> CBs, std::vector<Block> map) {
        keyPress();
        gravity();
        movement(CBs, map);
        tick += 1;
    }

    void keyPress() {
        W = IsKeyDown(KEY_W);
        A = IsKeyDown(KEY_A);
        S = IsKeyDown(KEY_S);
        D = IsKeyDown(KEY_D);


        if (A) {
            lookingRight = false;
            vx = -3.0f*SCALE;
        } else if (D) {
            lookingRight = true;
            vx = 3.0f*SCALE;
        } else {
            vx = 0;
        }

        if (W) {
            jumpQueue = 3;
        }
        if (ground and jumpQueue > 0) {
            if (jumpQueue == 3) {
                vy = -4.5f*SCALE;
            } else if (jumpQueue == 2) {
                vy -= 4.5f*SCALE;
            } else {
                vy -= 2.0f*SCALE;
            }
            ground = false;
            jumpQueue = 0;
        } else {
            jumpQueue -= 1;
        }

    }

    void gravity() {
        vy += 0.25*SCALE;
    }

    void movement(std::vector<int> CBs, std::vector<Block> map) {
        // Horizontal Axis checing
        rect.x += vx;
        int bsize = CBs.size();
        for (int i = 0; i < bsize; i++) {
            Block temp = map[CBs[i]];
            Vector2 DXspace;
            
            
            Hitbox1.x = rect.x+6*SCALE;
            DXspace = colision(Hitbox1, temp.rect);
            rect.x += DXspace.x;
            Hitbox1.x += DXspace.x;
            if (DXspace.x != 0) {
                vx = -vx/5;
                // vx = 0;
            }
            
            Hitbox2.x = rect.x+3*SCALE;
            DXspace = colision(Hitbox2, temp.rect);
            rect.x += DXspace.x;
            Hitbox2.x += DXspace.x;
            if (DXspace.x != 0) {
                vx = -vx/5;
                // vx = 0;
            }
            
            Hitbox3.x = rect.x+9*SCALE;
            DXspace = colision(Hitbox3, temp.rect);
            rect.x += DXspace.x;
            Hitbox3.x += DXspace.x;
            if (DXspace.x != 0) {
                vx = -vx/5;
                // vx = 0;
            }
        }




        // Vertical Axis checking
        rect.y += vy;

        for (int i = 0; i < bsize; i++) {
            Block temp = map[CBs[i]];
            Vector2 DYspace;
            
            Hitbox1.y = rect.y+14*SCALE;
            DYspace = colision(Hitbox1, temp.rect);
            rect.y += DYspace.y;
            Hitbox1.y += DYspace.y;
            if (DYspace.y != 0) {
                if (DYspace.y < 0) {
                    ground = true;
                }
                vy = -vy/5;
                // vy = 0;
            }

            Hitbox2.y = rect.y+7*SCALE;
            DYspace = colision(Hitbox2, temp.rect);
            rect.y += DYspace.y;
            Hitbox2.y += DYspace.y;
            if (DYspace.y != 0) {
                if (DYspace.y < 0) {
                    ground = true;
                }
                vy = -vy/5;
                // vy = 0;
            }
            
            Hitbox3.y = rect.y;
            DYspace = colision(Hitbox3, temp.rect);
            rect.y += DYspace.y;
            Hitbox3.y += DYspace.y;
            if (DYspace.y != 0) {
                if (DYspace.y < 0) {
                    ground = true;
                }
                vy = -vy/5;
                // vy = 0;
            }
        }





        cx = rect.x + rect.width*SCALE/2;
        cy = rect.y + rect.height*SCALE/2;

        if (tick % 10 == 0) {
            if (vx != 0) {
                imageCount++;
                if (imageCount > imageSize-1) {
                    imageCount = 0;
                }
            } else if (imageCount != 3) {
                if (imageCount == 0 and ground) {
                    imageCount = 3;
                } else {
                    imageCount = 0;
                }
            }
        }
    }

    Vector2 colision(Rectangle hitbox, Rectangle B) {
        float dx = 0, dy = 0;
        if (hitbox.x + hitbox.width*SCALE > B.x and hitbox.x < B.x + B.width*SCALE and hitbox.y < B.y + B.height*SCALE and hitbox.height*SCALE + hitbox.y > B.y) {
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



int main(void) {
    const int SCALE = 2;
    const int BS = 13;
    const int WT = BS*34*SCALE;
    const int HT = BS*25*SCALE;
    const float FW = 18;
    const float FH = 23;
    int tickBlockUpdate = 5;
    int tick = 1;

    InitWindow(WT, HT, "Super Flamingo Quest 0.2 - Aliveness Update");
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
        Rectangle center = {WT/2, HT/2, SCALE*FW, SCALE*FH};
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




        // DrawTexturePro(player.image, player.rect, player.rect, {static_cast<float>(player.rect.w), static_cast<float>(player.rect.h)}, 0, WHITE);
        // DrawTexture(player.image, player.rect.x, player.rect.y, WHITE);
        // DrawText(Texto, Lin, Col, Tam, Color)



        // DEBUG
        // DrawText(TextFormat("CURRENT FPS: %i", (int)(1.0f/deltaTime)), GetScreenWidth() - 220, 40, 20, GREEN);
        if (tick % 30 == 0) {
            maxV = 0;
        }
        if (abs(player.vy) > abs(maxV)) {
            maxV = player.vy;
        }
        DrawText(TextFormat("CURRENT V-Speed: %02.02f", -maxV), 20, 40, 20, GREEN);

        EndDrawing();
        tick++;
    }

    CloseWindow();
    return 0;
}