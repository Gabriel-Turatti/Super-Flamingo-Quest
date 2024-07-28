#include "raylib.h"
#include <string>
#include <vector>
#include <fstream>
#include <random>

#include "Block.cpp"
#include "Item.cpp"
#include "Flamingo.cpp"





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