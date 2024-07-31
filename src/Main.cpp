#include "raylib.h"
#include <string>
#include <vector>
#include <fstream>
#include <random>

#include "Block.cpp"
#include "Item.cpp"
#include "Flamingo.cpp"
#include "Enemy.cpp"
#include "Functions.cpp"



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
    const bool DEBUG = false;
    const int BS = 13;
    const int WT = BS*34*SCALE;
    const int HT = BS*25*SCALE;
    const float FW = 18;
    const float FH = 23;
    int tickBlockUpdate = 5;
    int tick = 1;
    int seconds = 0;

    InitWindow(WT, HT, "Super Flamingo Quest 0.6 - Enemies to Lovers Update");


    InitAudioDevice();

    Flamingo player(400, 400, FW, FH, WT, HT, SCALE);

    std::vector<Block> map;
    std::vector<Item> itens;
    std::vector<Enemy> enemies;
    std::ifstream level("levels/teste.txt");
    // std::ifstream level("levels/testeSimplao.txt");
    if (!level) {
        level.close();
        return 1;
    }

    std::string line;
    std::string previousLine;
    int CHL; // Current Height Level (AKA. what column of blocks we are currently looking during the map load)
    int widthLevel;
    int heightLevel;
    std::getline(level, line);
    heightLevel = std::stoi(line);
    std::getline(level, line);
    widthLevel = std::stoi(line);


    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> RNG100(0, 100);
    std::uniform_int_distribution<std::mt19937::result_type> RNGWidth(0, widthLevel);
    std::uniform_int_distribution<std::mt19937::result_type> RNGHeight(0, heightLevel);

    int RenderPhase = 0; // 1 = Blocks; 2 = Itens;
    while (!level.eof()) {
        std::getline(level, line);
        if (line == "endmap") {
            break;
        }
        if (line[0] == 'P') {
            CHL = 0;
            RenderPhase += 1;
            continue;
        }
        if (RenderPhase == 1) {
            for (int CWL = 0; CWL < widthLevel; CWL++) { // Current Width Level
                if (line[CWL] == '-' or line[CWL] == '|' or line[CWL] == 'p' or line[CWL] == 'h') {
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
                } else if (line[CWL] == 'K') {
                    bool rotation = false;
                    std::string type;
                    if (line[CWL-1] == '|') {
                        rotation = true;
                    }
                    if (line[CWL+1] == 'h') {
                        type = "hope";
                    }
                    tile = Block(CWL*(BS-1)*SCALE, CHL*(BS-1)*SCALE, BS, BS*2-1, "gate-" + type, SCALE, rotation);
                } else if (line[CWL] == 'P') {
                    if (line[CWL+1] == 'p') {
                        tile = Block(CWL*(BS-1)*SCALE, CHL*(BS-1)*SCALE, BS*2-1, BS, "platform", SCALE, false);
                    } else {
                        tile = Block(CWL*(BS-1)*SCALE, CHL*(BS-1)*SCALE, BS, BS*2-1, "platform", SCALE, true);
                    }
                } else if (line[CWL] == 'A') {
                    tile = Block(CWL*(BS-1)*SCALE, CHL*(BS-1)*SCALE, BS, BS, "altar", SCALE);
                } else if (line[CWL] == 'S') {
                    int orientation = 0;
                    if (line[CWL-1] != 'S' and line[CWL+1] != 'S') {
                        if (previousLine[CWL] != '-' and previousLine[CWL] != 'S') {
                            orientation = 2;
                        } else if (line[CWL-1] != '-') {
                            orientation = 3;
                        } else if (line[CWL+1] != '-') {
                            orientation = 1;
                        }
                    }
                    tile = Block(CWL*(BS-1)*SCALE, CHL*(BS-1)*SCALE, BS, BS, "spike", SCALE, orientation);
                }
                map.push_back(tile);
            }
            CHL++;
            previousLine = line;
        } else if (RenderPhase == 2) {
            int i = 0;
            int CWL;
            std::string text = "";
            std::string name = "";
            char category;

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
                if (line[i] == '-') {
                    if (text == "coin") {
                        category = 'C';
                    } else if (text == "food") {
                        category = 'F';
                    } else if (text == "Hshard") {
                        category = 'H';
                    } else if (text == "key") {
                        category = 'K';
                    }
                }
                text += line[i];
            }
            name = text;

            Item novoItem(CHL*(BS-1)*SCALE, CWL*(BS-1)*SCALE, name, SCALE, category);
            itens.push_back(novoItem);
        } else if (RenderPhase == 3) {
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

            if (name == "snail") {
                Block ground;
                int sizeB = map.size();
                for (int j = 0; j < sizeB; j++) {
                    ground = map[j];
                    if (ground.rect.x == (float)(CHL)*(BS-1)*SCALE and ground.rect.y == (float)CWL*(BS-1)*SCALE) {
                        break;
                    }
                }
                enemies.push_back(Enemy((CHL-1)*(BS-1)*SCALE, CWL*(BS-1)*SCALE, name, SCALE, map, RNG100(rng), ground));
            } else if (name == "butterfly") {
                enemies.push_back(Enemy(CHL*(BS-1)*SCALE, CWL*(BS-1)*SCALE, name, SCALE, map, RNG100(rng)));
            } else if (name == "crab") {
                enemies.push_back(Enemy(CHL*(BS-1)*SCALE, CWL*(BS-1)*SCALE, name, SCALE, map, RNG100(rng)));
            } else {
                enemies.push_back(Enemy(CHL*(BS-1)*SCALE, CWL*(BS-1)*SCALE, name, SCALE, map, RNG100(rng)));
            }
        }
    }
    level.close();

    int sizeB = map.size();
    int sizeI = itens.size();
    int sizeE = enemies.size();
    Vector2 mousePosition;
    std::vector<int> colisionBlocks; // List of blocks that can collide with player
    std::vector<int> colisionItens; // List of itens that can collide with player
    std::vector<int> colisionEnemies; // List of Enemies that can collide with player
    SetTargetFPS(30);


    int song = RNG100(rng);
    Music Theme;
    if (song <= 3) {
        Theme = LoadMusicStream("songs/PowerTheme.wav");
    } else if (song <= 12) {
        Theme = LoadMusicStream("songs/ResilienceTheme.wav");
    } else if (song <= 28) {
        Theme = LoadMusicStream("songs/HopeTheme.wav");
    } else {
        Theme = LoadMusicStream("songs/MainTheme.wav");
    }
    PlayMusicStream(Theme);
    
    
    while (!WindowShouldClose()) {
        UpdateMusicStream(Theme);
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


            colisionEnemies.clear();
            for (int i = 0; i < sizeE; i++) {
                int dx = abs(enemies[i].cx - player.cx);
                if (dx < player.rect.width*2*SCALE) {
                    int dy = abs(enemies[i].cy - player.cy);
                    if (dy < player.rect.height*2*SCALE) {
                        colisionEnemies.push_back(i);
                    }
                }
            }
        }


        // Entities Updates
        for (int i = 0; i < sizeE; i++) {
            enemies[i].update(map, player);
        }
        player.update(colisionBlocks, map, colisionItens, itens, colisionEnemies, enemies);

        if (abs(player.vy) > 12) {
            tickBlockUpdate = 1;
        } else {
            tickBlockUpdate = 5;
        }

        Rectangle center = {WT/2, HT/2, SCALE*player.rect.width, SCALE*player.rect.height};

        mousePosition = GetMousePosition();
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            player.rect.x = mousePosition.x +player.rect.x - center.x;
            player.rect.y = mousePosition.y +player.rect.y - center.y;
        }

        if (tick % 30 == 0) {
            seconds += 1;
        }




        // Desenhando coisas
        BeginDrawing();
        ClearBackground(BLUE);



        
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
            playerColor = {0, 255, 255, 127};
        }

        // invincibility for damage
        if (player.invincibility['H'] > 0 and player.tick % 10 <= 1) {
            playerColor = {255, 255, 0, 255};
        } else if (player.invincibility['R'] > 0 and player.tick % 10 <= 3) {
            playerColor = GREEN;
        } else if (player.invincibility['P'] > 0 and player.tick % 10 <= 5) {
            playerColor = BLUE;
        } else if (player.invincibility['C'] > 0 and player.tick % 10 <= 7) {
            playerColor = RED;
        } else if (player.invincibility['W'] > 0 and player.tick % 10 <= 9) {
            playerColor = {255, 255, 0, 255};
        }



        if (player.lookingRight) {
            DrawTexturePro(player.images[player.imageCount], {0.0f, 0.0f, player.rect.width, player.rect.height}, center, {0, 0}, 0, playerColor);
        } else {
            DrawTexturePro(player.images[player.imageCount], {0.0f, 0.0f, -player.rect.width, player.rect.height}, center, {0, 0}, 0, playerColor);
        }

        // Desenhando inimigos
        for (int i = 0; i < sizeE; i++) {
            Vector2 relativePos;
            Rectangle source, dest;

            relativePos.x = center.x +enemies[i].rect.x -player.rect.x;
            relativePos.y = center.y +enemies[i].rect.y -player.rect.y;

            source.x = 0 + enemies[i].imageCount*(enemies[i].rect.width+1);
            source.y = 0;
            source.width = enemies[i].rect.width;
            source.height = enemies[i].rect.height;

            dest.x = relativePos.x;
            dest.y = relativePos.y;
            dest.width = source.width*SCALE;
            dest.height = source.height*SCALE;

            if (enemies[i].name == "bee") {
                DrawTexturePro(enemies[i].images[0], source, dest, {0, 0}, 0, WHITE);
            } else if (enemies[i].name == "snail") {
                if (enemies[i].behavior == 1) {
                    dest.y += enemies[i].rect.width*SCALE;
                } else if (enemies[i].behavior == 2) {
                    dest.y += enemies[i].rect.height*SCALE;
                    dest.x += enemies[i].rect.width*SCALE;
                } else if (enemies[i].behavior == 3) {
                    dest.x += enemies[i].rect.height*SCALE;
                }
                DrawTexturePro(enemies[i].images[0], source, dest, {0, 0}, enemies[i].behavior*-90, WHITE);
            } else if (enemies[i].name == "butterfly") {
                DrawTexturePro(enemies[i].images[0], source, dest, {0, 0}, 0, WHITE);
            } else if (enemies[i].name == "crab") {
                // DrawRectangle(relativePos.x, relativePos.y, enemies[i].rect.width, enemies[i].rect.height, RED);
                DrawTexturePro(enemies[i].images[0], source, dest, {0, 0}, 0, WHITE);
            } else {
                DrawRectangle(relativePos.x, relativePos.y, enemies[i].rect.width, enemies[i].rect.height, BLACK);
            }
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
                DrawTexturePro(map[i].image, cut, dest, {0, 0}, 0, WHITE);
            } else if (map[i].name == "spike") {
                if (map[i].direction == 1) {
                    relativePos.y += map[i].rect.height*SCALE;
                } else if (map[i].direction == 2) {
                    relativePos.x += map[i].rect.width*SCALE;
                    relativePos.y += map[i].rect.height*SCALE;
                } else if (map[i].direction == 3) {
                    relativePos.x += map[i].rect.width*SCALE;
                }

                DrawTextureEx(map[i].image, relativePos, map[i].direction*-90, SCALE, WHITE);
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
        if (tick % 30 == 0 and sizeI < 100) {
            int RNG_X = (RNGWidth(rng))*(BS-1)*SCALE;
            int RNG_Y = (RNGHeight(rng)-1)*(BS-1)*SCALE;
            bool freespace = true;
            Rectangle tempItem = {(float) RNG_X, (float) RNG_Y, 13, 13};
            for (int i = 0; i < sizeB; i++) {
                Block temp = map[i];
                if (GenericColision(tempItem, temp.rect, SCALE)) { 
                    freespace = false;
                    break;
                }
            }
            if (freespace) {
                int value = RNG100(rng);
                if (value <= 0) {
                    itens.push_back(Item(RNG_X, RNG_Y, "Hshard-wisdom", SCALE, 'H'));
                } else if (value <= 2) {
                    itens.push_back(Item(RNG_X, RNG_Y, "Hshard-courage", SCALE, 'H'));
                } else if (value <= 5) {
                    itens.push_back(Item(RNG_X, RNG_Y, "Hshard-power", SCALE, 'H'));
                } else if (value <= 9) {
                    itens.push_back(Item(RNG_X, RNG_Y, "Hshard-resilience", SCALE, 'H'));
                } else if (value <= 14) {
                    itens.push_back(Item(RNG_X, RNG_Y, "Hshard-hope", SCALE, 'H'));
                } else if (value <= 15) {
                    itens.push_back(Item(RNG_X, RNG_Y, "courage-potion", SCALE, 'I'));
                } else if (value <= 16) {
                    itens.push_back(Item(RNG_X, RNG_Y, "coin-gold", SCALE, 'C'));
                } else if (value <= 18) {
                    itens.push_back(Item(RNG_X, RNG_Y, "coin-silver", SCALE, 'C'));
                } else if (value <= 25) {
                    itens.push_back(Item(RNG_X, RNG_Y, "coin-copper", SCALE, 'C'));
                } else if (value <= 33) {
                    itens.push_back(Item(RNG_X, RNG_Y, "food-orange", SCALE, 'F'));
                } else if (value <= 48) {
                    itens.push_back(Item(RNG_X, RNG_Y, "food-pepper", SCALE, 'F'));
                } else if (value <= 65) {
                    itens.push_back(Item(RNG_X, RNG_Y, "food-blueberry", SCALE, 'F'));
                } else if (value <= 80) {
                    itens.push_back(Item(RNG_X, RNG_Y, "food-pear", SCALE, 'F'));
                } else if (value <= 100) {
                    itens.push_back(Item(RNG_X, RNG_Y, "food-banana", SCALE, 'F'));
                } else {
                    itens.push_back(Item(RNG_X, RNG_Y, "key-hope", SCALE, 'K'));
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
        DrawText(TextFormat("itens no mapa: %d", itens.size()), GetScreenWidth()-300, 220, 20, WHITE);









 

        if (DEBUG) {
            Vector2 relativePos;
            relativePos.x = WT/2 +player.groundBlock.rect.x -player.rect.x;
            relativePos.y = HT/2 +player.groundBlock.rect.y -player.rect.y;
            DrawRectangle(relativePos.x, relativePos.y, player.groundBlock.rect.width*SCALE, player.groundBlock.rect.height*SCALE, YELLOW);
            if (player.crouch) {
                relativePos.x = center.x +player.HitboxA.x -player.rect.x;
                relativePos.y = center.y +player.HitboxA.y -player.rect.y;
                DrawRectangle(relativePos.x, relativePos.y, player.HitboxA.width*SCALE, player.HitboxA.height*SCALE, RED);
            } else {
                relativePos.x = center.x +player.Hitbox1.x -player.rect.x;
                relativePos.y = center.y +player.Hitbox1.y -player.rect.y;
                DrawRectangle(relativePos.x, relativePos.y, player.Hitbox1.width*SCALE, player.Hitbox1.height*SCALE, RED);
                relativePos.x = center.x +player.Hitbox2.x -player.rect.x;
                relativePos.y = center.y +player.Hitbox2.y -player.rect.y;
                DrawRectangle(relativePos.x, relativePos.y, player.Hitbox2.width*SCALE, player.Hitbox2.height*SCALE, RED);
                relativePos.x = center.x +player.Hitbox3.x -player.rect.x;
                relativePos.y = center.y +player.Hitbox3.y -player.rect.y;
                DrawRectangle(relativePos.x, relativePos.y, player.Hitbox3.width*SCALE, player.Hitbox3.height*SCALE, RED);
            }
            relativePos.x = center.x +player.HB1.x -player.rect.x;
            relativePos.y = center.y +player.HB1.y -player.rect.y;
            DrawRectangle(relativePos.x, relativePos.y, player.HB1.width*SCALE, player.HB1.height*SCALE, DARKBLUE);


            for (int i = 0; i < sizeE; i++) {
                Vector2 relativePos;
                if (enemies[i].name == "crab") {
                    relativePos.x = center.x +enemies[i].rect.x -player.rect.x;
                    relativePos.y = center.y +enemies[i].rect.y -player.rect.y;
                    DrawRectangle(relativePos.x, relativePos.y, enemies[i].rect.width*SCALE, enemies[i].rect.height*SCALE, RED);
                    relativePos.x = center.x +enemies[i].patrol1 -player.rect.x;
                    relativePos.y = center.y +enemies[i].ground.rect.y -player.rect.y;
                    DrawCircle(relativePos.x, relativePos.y, 5, YELLOW);
                    relativePos.x = center.x +enemies[i].patrol2 -player.rect.x;
                    relativePos.y = center.y +enemies[i].ground.rect.y -player.rect.y;
                    DrawCircle(relativePos.x, relativePos.y, 5, YELLOW);
                    relativePos.x = center.x +enemies[i].ground.rect.x -player.rect.x;
                    relativePos.y = center.y +enemies[i].ground.rect.y -player.rect.y;
                    DrawRectangle(relativePos.x, relativePos.y, enemies[i].ground.rect.width*SCALE, enemies[i].ground.rect.height*SCALE, YELLOW);
                    relativePos.x = center.x +enemies[i].border1.rect.x -player.rect.x;
                    relativePos.y = center.y +enemies[i].border1.rect.y -player.rect.y;
                    DrawRectangle(relativePos.x, relativePos.y, enemies[i].border1.rect.width*SCALE, enemies[i].border1.rect.height*SCALE, GREEN);
                    relativePos.x = center.x +enemies[i].border2.rect.x -player.rect.x;
                    relativePos.y = center.y +enemies[i].border2.rect.y -player.rect.y;
                    DrawRectangle(relativePos.x, relativePos.y, enemies[i].border2.rect.width*SCALE, enemies[i].border2.rect.height*SCALE, GREEN);
                } else if (enemies[i].name == "butterfly") {
                    relativePos.x = center.x +enemies[i].rect.x -player.rect.x;
                    relativePos.y = center.y +enemies[i].rect.y -player.rect.y;
                    DrawRectangle(relativePos.x, relativePos.y, enemies[i].rect.width*SCALE, enemies[i].rect.height*SCALE, RED);
                    relativePos.x = center.x +enemies[i].orbit.x -player.rect.x;
                    relativePos.y = center.y +enemies[i].orbit.y -player.rect.y;
                    DrawCircle(relativePos.x, relativePos.y, 5, YELLOW);
                } else if (enemies[i].name == "snail") {
                    relativePos.x = center.x +enemies[i].HBFeet.x -player.rect.x;
                    relativePos.y = center.y +enemies[i].HBFeet.y -player.rect.y;
                    DrawRectangle(relativePos.x, relativePos.y, enemies[i].HBFeet.width*SCALE, enemies[i].HBFeet.height*SCALE, RED);
                    relativePos.x = center.x +enemies[i].vision.x -player.rect.x;
                    relativePos.y = center.y +enemies[i].vision.y -player.rect.y;
                    DrawRectangle(relativePos.x, relativePos.y, enemies[i].vision.width*SCALE, enemies[i].vision.height*SCALE, BLACK);
                    if (enemies[i].ground.SCALE == 0) {
                        DrawText("UNEXPECTED SNAIL BEHAVIOR 2", GetScreenWidth() - 520, 40, 20, RED);
                    } else {
                        relativePos.x = center.x +enemies[i].ground.rect.x -player.rect.x;
                        relativePos.y = center.y +enemies[i].ground.rect.y -player.rect.y;
                        DrawRectangle(relativePos.x, relativePos.y, enemies[i].ground.rect.width*SCALE, enemies[i].ground.rect.height*SCALE, YELLOW);
                    }
                } else if (enemies[i].name == "bee") {
                    relativePos.x = center.x +enemies[i].rect.x -player.rect.x;
                    relativePos.y = center.y +enemies[i].rect.y -player.rect.y;
                    DrawRectangle(relativePos.x, relativePos.y, enemies[i].rect.width*SCALE, enemies[i].rect.height*SCALE, RED);
                    relativePos.x = center.x +enemies[i].patrol1 -player.rect.x;
                    relativePos.y = center.y +enemies[i].rect.y -player.rect.y;
                    DrawCircle(relativePos.x, relativePos.y, 5, YELLOW);
                    relativePos.x = center.x +enemies[i].patrol2 -player.rect.x;
                    relativePos.y = center.y +enemies[i].rect.y -player.rect.y;
                    DrawCircle(relativePos.x, relativePos.y, 5, YELLOW);
                }
            }
            for (int i = 0; i < sizeI; i++) {
                Vector2 relativePos;
                relativePos.x = center.x +itens[i].cx -player.rect.x;
                relativePos.y = center.y +itens[i].cy -player.rect.y;
                DrawCircle(relativePos.x, relativePos.y, 5, GREEN);
            }
        }

        EndDrawing();
        tick++;
    }


    UnloadMusicStream(Theme);
    CloseAudioDevice();

    CloseWindow();
    return 0;
}