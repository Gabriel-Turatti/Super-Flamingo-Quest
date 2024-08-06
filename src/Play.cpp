#include "../header/Play.hpp"


Play::Play() {
    loader = MapLoader(SCALE, BS, WT, HT);
    rng = std::mt19937(dev());
    RNG100 = std::uniform_int_distribution<std::mt19937::result_type>(0, 100);
    RNGe3 = std::uniform_int_distribution<std::mt19937::result_type>(0, 1000);
}

void Play::loadFlamingo() {
    player = Flamingo(400, 400, FW, FH, WT, HT, SCALE);
}

void Play::search_universe(std::vector<std::string> &Universe) {
    std::string name = "levels"; 
    DIR* dirp = opendir(name.c_str());
    struct dirent * dp;
    while ((dp = readdir(dirp)) != NULL) {
        Universe.push_back(dp->d_name);
    }
    Universe.erase(Universe.begin());
    Universe.erase(Universe.begin());
    closedir(dirp);
}

void Play::Hub() {
    SetTargetFPS(30);
    theme = LoadMusicStream("songs/MainTheme.wav");
    PlayMusicStream(theme);

    Vector2 mousePosition;
    Rectangle mouseRect = {0, 0, 2, 2};
    int SCALER = 3;

    float midX = (float)GetScreenWidth()/2;
    float midY = (float)GetScreenHeight()/2 - 200;
    float sizeOptions = 28*SCALER;

    Rectangle editorRect = {midX - 200, midY, sizeOptions, sizeOptions};
    Rectangle iconRect = {midX + 200, midY, sizeOptions, sizeOptions};

    while (!WindowShouldClose()) {
        UpdateMusicStream(theme);
        mousePosition = GetMousePosition();
        mouseRect.x = mousePosition.x;
        mouseRect.y = mousePosition.y;
        int option = 0;

        if (GenericColision(mouseRect, editorRect)) {
            option = 1;
        } else if (GenericColision(mouseRect, iconRect)) {
            option = 2;
        }


        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (option == 1) {
                HubMapEditor();
            } else if (option == 2) {
                HubLevelSelect();
            }
        }
        
        BeginDrawing();
        ClearBackground(BLUE);


        if (option == 1) {
            DrawTextureEx(iconEditor, {editorRect.x, editorRect.y}, 0, SCALER, YELLOW);
        } else {
            DrawTextureEx(iconEditor, {editorRect.x, editorRect.y}, 0, SCALER, WHITE);
        }
        DrawText("Map Editor", midX-210, midY+90, 20, BLACK);


        if (option == 2) {
            DrawTextureEx(iconGame, {iconRect.x, iconRect.y}, 0, SCALER, YELLOW);
        } else {
            DrawTextureEx(iconGame, {iconRect.x, iconRect.y}, 0, SCALER, WHITE);
        }
        DrawText("Main Game", midX+190, midY+90, 20, BLACK);

        EndDrawing();
    }

    UnloadMusicStream(theme);
}



void Play::HubMapEditor() {

    Vector2 mousePosition;
    Rectangle mouseRect = {0, 0, 2, 2};
    int SCALER = 3;

    std::vector<std::string> Universe;
    search_universe(Universe);

    float positionX = 60;
    float positionY = 60;

    while (!WindowShouldClose()) {
        UpdateMusicStream(theme);
        mousePosition = GetMousePosition();
        mouseRect.x = mousePosition.x;
        mouseRect.y = mousePosition.y;



        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            positionY = 60;
            for (std::string level : Universe) {
                DrawRectangle(positionX, positionY, 200, 25, BLACK);
                Rectangle levelRect = {positionX, positionY, 200, 25};
                if (GenericColision(mouseRect, levelRect)) {
                    EditLevel(level);
                }
                positionY += 30;
            }
        }




        BeginDrawing();
        ClearBackground(BLUE);
        positionY = 60;

        for (std::string level : Universe) {
            DrawRectangle(positionX, positionY, 200, 25, BLACK);
            Rectangle levelRect = {positionX, positionY, 200, 25};
            if (GenericColision(mouseRect, levelRect)) {
                DrawRectangle(positionX+2, positionY+2, 196, 21, YELLOW);
            } else {
                DrawRectangle(positionX+2, positionY+2, 196, 21, GRAY);
            }
            DrawText(level.c_str(), positionX+2, positionY+2, 20, BLACK);
            positionY += 30;
        }

        

        EndDrawing();
    }
}

void Play::EditLevel(std::string name) {
    Map LevelMap = loader.LoadFile(name);
    Blocks = LevelMap.Blocks;
    itens = LevelMap.itens;
    enemies = LevelMap.enemies;
    player.rect.x = LevelMap.playerX;
    player.rect.y = LevelMap.playerY;


    float cx = WT/2;
    float cy = HT/2;
    bool W, A, S, D, E;
    Vector2 relativePos;
    Texture2D grid = LoadTexture("images/grid.png");
    Rectangle mouseRect = {0, 0, 2, 2};


    int Menu = 0;
    std::vector<Block> BlockOptions;
    BlockOptions.push_back(Block(0, 0, BS, BS, "dirt", SCALE));
    BlockOptions.push_back(Block(0, 0, BS*2-SCALE, BS*2-SCALE, "dirt2", SCALE));
    BlockOptions.push_back(Block(0, 0, BS, BS, "grass", SCALE));
    BlockOptions.push_back(Block(0, 0, BS, BS, "brick", SCALE));
    std::vector<Item> ItemOptions;
    ItemOptions.push_back(Item(0, 0, "coin-copper", SCALE, 'C'));
    ItemOptions.push_back(Item(0, 0, "coin-silver", SCALE, 'C'));
    ItemOptions.push_back(Item(0, 0, "coin-gold", SCALE, 'C'));
    ItemOptions.push_back(Item(0, 0, "coin-death", SCALE, 'C'));
    ItemOptions.push_back(Item(0, 0, "food-banana", SCALE, 'F'));
    ItemOptions.push_back(Item(0, 0, "food-pear", SCALE, 'F'));
    ItemOptions.push_back(Item(0, 0, "food-blueberry", SCALE, 'F'));
    ItemOptions.push_back(Item(0, 0, "food-pepper", SCALE, 'F'));
    ItemOptions.push_back(Item(0, 0, "food-orange", SCALE, 'F'));
    ItemOptions.push_back(Item(0, 0, "Hshard-hope", SCALE, 'H'));
    ItemOptions.push_back(Item(0, 0, "Hshard-resilience", SCALE, 'H'));
    ItemOptions.push_back(Item(0, 0, "Hshard-power", SCALE, 'H'));
    ItemOptions.push_back(Item(0, 0, "Hshard-courage", SCALE, 'H'));
    ItemOptions.push_back(Item(0, 0, "Hshard-wisdom", SCALE, 'H'));
    ItemOptions.push_back(Item(0, 0, "courage-potion", SCALE, 'S'));
    ItemOptions.push_back(Item(0, 0, "party-potion", SCALE, 'S'));
    ItemOptions.push_back(Item(0, 0, "Pshard-wind", SCALE, 'P'));
    ItemOptions.push_back(Item(0, 0, "Pshard-party", SCALE, 'P'));
    ItemOptions.push_back(Item(0, 0, "Pshard-fun", SCALE, 'P'));
    ItemOptions.push_back(Item(0, 0, "Pshard-hard", SCALE, 'P'));
    ItemOptions.push_back(Item(0, 0, "Pshard-eloise", SCALE, 'P'));
    ItemOptions.push_back(Item(0, 0, "key-hope", SCALE, 'K'));
    ItemOptions.push_back(Item(0, 0, "power-dash", SCALE, 'S'));
    ItemOptions.push_back(Item(0, 0, "power-transmutation", SCALE, 'S'));
    ItemOptions.push_back(Item(0, 0, "power-boost", SCALE, 'S'));
    ItemOptions.push_back(Item(0, 0, "power-spear", SCALE, 'S'));


    float Px = WT*2/3 + 30;
    float Py = 50;
    float MaxHeight = 0;
    int bc = 0;
    for (Block temp : BlockOptions) {
        temp.rect.x = Px;
        temp.rect.y = Py;
        Px += temp.rect.width + 10;
        if (temp.rect.height > MaxHeight) {
            MaxHeight = temp.rect.height;
        }
        if (Px+temp.rect.width > WT) {
            Px = WT*2/3 + 30;
            Py += MaxHeight + 10;
        }
        BlockOptions[bc] = temp;
        bc += 1;
    }


    Px = WT*2/3 + 30;
    Py = 50;
    MaxHeight = 0;
    bc = 0;
    for (Item temp : ItemOptions) {
        temp.rect.x = Px;
        temp.rect.y = Py;
        Px += temp.rect.width + 10;
        if (temp.rect.height > MaxHeight) {
            MaxHeight = temp.rect.height;
        }
        if (Px+temp.rect.width > WT) {
            Px = WT*2/3 + 30;
            Py += MaxHeight + 10;
        }
        ItemOptions[bc] = temp;
        bc += 1;
    }


    Block mouseBlock;
    Item mouseItem;
    Enemy mouseEnemy;
    bool background = false;


    while (!WindowShouldClose()) {
        UpdateMusicStream(theme);
        sizeB = Blocks.size();
        sizeE = enemies.size();
        sizeI = itens.size();


        Vector2 posM =  GetMousePosition();
        mouseRect.x = posM.x;
        mouseRect.y = posM.y;
        mouseBlock.rect.x = posM.x;
        mouseBlock.rect.y = posM.y;
        mouseItem.rect.x = posM.x;
        mouseItem.rect.y = posM.y;

        W = IsKeyDown(KEY_W);
        A = IsKeyDown(KEY_A);
        S = IsKeyDown(KEY_S);
        D = IsKeyDown(KEY_D);
        E = IsKeyPressed(KEY_E);

        if (W) {
            cy -= BS-SCALE;
        }
        if (A) {
            cx -= BS-SCALE;
        }
        if (S) {
            cy += BS-SCALE;
        }
        if (D) {
            cx += BS-SCALE;
        }
        if (E) {
            background = !background;
        }

        // one = Blocks/ two = Itens/ Three = Enemies
        if (IsKeyPressed(KEY_ONE)) {
            if (Menu == 1) {
                Menu = 0;
            } else {
                Menu = 1;
            }
        }
        if (IsKeyPressed(KEY_TWO)) {
            if (Menu == 2) {
                Menu = 0;
            } else {
                Menu = 2;
            }
        }
        if (IsKeyPressed(KEY_THREE)) {
            if (Menu == 3) {
                Menu = 0;
            } else {
                Menu = 3;
            }
        }
        if (IsKeyPressed(KEY_ZERO)) {
            Menu = 0;
        }


        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (mouseRect.x > WT/3) {
                if (Menu == 1) {
                    for (Block blockOption : BlockOptions) {
                        if (GenericColision(mouseRect, blockOption.rect)) {
                            mouseBlock = Block(mouseRect.x, mouseRect.y, blockOption.rect.width, blockOption.rect.height, blockOption.name, SCALE, 0, background);
                        }
                    }
                } else if (Menu == 2) {
                    for (Item itemOption : ItemOptions) {
                        if (GenericColision(mouseRect, itemOption.rect)) {
                            mouseItem = Item(mouseRect.x, mouseRect.y, itemOption.name, SCALE, itemOption.category);
                        }
                    }
                }
            }
        } else if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
            Rectangle mouseRectTemp = mouseRect;
            mouseRectTemp.x = cx + mouseRect.x - WT/2;
            mouseRectTemp.y = cy + mouseRect.y - HT/2;
            if (Menu == 1) {
                if (mouseBlock.SCALE == 0) {
                    for (int i = 0; i < sizeB; i++) {
                        if (GenericColision(Blocks[i].rect, mouseRectTemp)) {
                            auto it = std::next(Blocks.begin(), i);
                            Blocks.erase(it);
                            sizeB -= 1;
                            break;
                        }
                    }
                } else {
                    mouseBlock.SCALE = 0;
                }
            } else if (Menu == 2) {
                if (mouseItem.SCALE == 0) {
                    for (int i = 0; i < sizeI; i++) {
                        if (GenericColision(itens[i].rect, mouseRectTemp)) {
                            auto it = std::next(itens.begin(), i);
                            itens.erase(it);
                            sizeI -= 1;
                            break;
                        }
                    }
                } else {
                    mouseItem.SCALE = 0;
                }
            }
        }



        Block placeBlock;
        Item placeItem;
        bool placeable = false;

        // Drawing MAP
        BeginDrawing();
        ClearBackground(BLUE);


        Vector2 posGrid = {0, 0};
        for (int i = 0; i < BHT+3; i++) {
            for (int j = 0; j < BWT+3; j++) {
                DrawTextureEx(grid, posGrid, 0, SCALE, WHITE);
                if (mouseRect.x <= WT*2/3 and (mouseBlock.SCALE != 0 or mouseItem.SCALE != 0)) {
                    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                        Rectangle gridrect = {posGrid.x, posGrid.y, BS, BS};
                        if (GenericColision(gridrect, mouseRect)) {
                            float Bx = cx -WT/2 +posGrid.x;
                            float By = cy -HT/2 +posGrid.y;
                            if (Menu == 1) {
                                placeBlock = Block(Bx, By, mouseBlock.rect.width, mouseBlock.rect.height, mouseBlock.name, SCALE, 0, background);
                            } else if (Menu == 2) {
                                placeItem = Item(Bx, By, mouseItem.name, SCALE, mouseItem.category);
                            }
                            placeable = true;
                        }
                    }
                }
                posGrid.x += (BS-SCALE);
            }
            posGrid.x = 0;
            posGrid.y += (BS-SCALE);
        }


        // if (IsMouseButtonPressed())

        
        relativePos.x = WT/2 +player.rect.x -cx;
        relativePos.y = HT/2 +player.rect.y -cy;
        DrawTextureEx(player.images[player.imageCount], relativePos, 0, 1, WHITE);

        
        // Desenhando blocos Background
        for (int i = 0; i < sizeB; i++) {
            if (!Blocks[i].background) {
                continue;
            }
            if (Menu == 1) {
                if (GenericColision(Blocks[i].rect, placeBlock.rect)) {
                    placeBlock.rect.x += 2*SCALE;
                    placeBlock.rect.y += 2*SCALE;
                    if (GenericColision(Blocks[i].rect, placeBlock.rect)) {
                        placeBlock.rect.x -= 4*SCALE;
                        placeBlock.rect.y -= 4*SCALE;
                        if (GenericColision(Blocks[i].rect, placeBlock.rect)) {
                            placeable = false;
                        } else {
                            placeBlock.rect.x += 2*SCALE;
                            placeBlock.rect.y += 2*SCALE;
                        }
                    } else {
                        placeBlock.rect.x -= 2*SCALE;
                        placeBlock.rect.y -= 2*SCALE;
                    }
                }
            }


            relativePos.x = WT/2 +Blocks[i].rect.x -cx;
            relativePos.y = HT/2 +Blocks[i].rect.y -cy;
            if (Blocks[i].name == "gate-hope") {
                // Rectangle cut, dest;
                // dest.x = relativePos.x;
                // dest.y = relativePos.y;
                // dest.width = 13*SCALE;
                // dest.height = 25*SCALE;

                // cut.x = 0;
                // cut.y = 0;
                // cut.width = 13;
                // cut.height = 25;
                // DrawTexturePro(Blocks[i].image, cut, dest, {0, 0}, 0, GRAY);
                DrawTextureEx(Blocks[i].image, relativePos, 0, SCALE, GRAY);
            } else {
                DrawTextureEx(Blocks[i].image, relativePos, 0, SCALE, GRAY);
            }
        }

        // Desenhando inimigos
        for (int i = 0; i < sizeE; i++) {
            relativePos.x = WT/2 +enemies[i].rect.x -cx;
            relativePos.y = HT/2 +enemies[i].rect.y -cy;
            // Rectangle source, dest;
            // source.x = 0 + enemies[i].imageCount*(enemies[i].rectImage.width+1);
            // source.y = 0;
            // source.width = enemies[i].rectImage.width;
            // source.height = enemies[i].rectImage.height;

            // dest.x = relativePos.x;
            // dest.y = relativePos.y;
            // dest.width = enemies[i].rect.width;
            // dest.height = enemies[i].rect.height;

            DrawTextureEx(enemies[i].images[0], relativePos, 0, 1, WHITE);
            // DrawTexturePro(enemies[i].images[0], source, enemies[i].rect, {0, 0}, 0, WHITE);
        }

        // Desenhando blocos Ground
        for (int i = 0; i < sizeB; i++) {
            if (Blocks[i].background) {
                continue;
            }
            if (Menu == 1) {
                if (GenericColision(Blocks[i].rect, placeBlock.rect)) {
                    placeBlock.rect.x += 2*SCALE;
                    placeBlock.rect.y += 2*SCALE;
                    if (GenericColision(Blocks[i].rect, placeBlock.rect)) {
                        placeBlock.rect.x -= 4*SCALE;
                        placeBlock.rect.y -= 4*SCALE;
                        if (GenericColision(Blocks[i].rect, placeBlock.rect)) {
                            placeable = false;
                        } else {
                            placeBlock.rect.x += 2*SCALE;
                            placeBlock.rect.y += 2*SCALE;
                        }
                    } else {
                        placeBlock.rect.x -= 2*SCALE;
                        placeBlock.rect.y -= 2*SCALE;
                    }
                }
            } else if (Menu == 2) {
                if (GenericColision(Blocks[i].rect, placeItem.rect)) {
                    placeItem.rect.x += 2*SCALE;
                    placeItem.rect.y += 2*SCALE;
                    if (GenericColision(Blocks[i].rect, placeItem.rect)) {
                        placeItem.rect.x -= 4*SCALE;
                        placeItem.rect.y -= 4*SCALE;
                        if (GenericColision(Blocks[i].rect, placeItem.rect)) {
                            placeable = false;
                        } else {
                            placeItem.rect.x += 2*SCALE;
                            placeItem.rect.y += 2*SCALE;
                        }
                    } else {
                        placeItem.rect.x -= 2*SCALE;
                        placeItem.rect.y -= 2*SCALE;
                    }
                }
            }
            relativePos.x = WT/2 +Blocks[i].rect.x -cx;
            relativePos.y = HT/2 +Blocks[i].rect.y -cy;
            if (Blocks[i].name == "gate-hope") {
                // Rectangle cut, dest;
                // dest.x = relativePos.x;
                // dest.y = relativePos.y;
                // dest.width = 13*SCALE;
                // dest.height = 25*SCALE;

                // cut.x = 0;
                // cut.y = 24;
                // cut.width = 13;
                // cut.height = 25;
                // DrawTexturePro(Blocks[i].image, cut, dest, {0, 0}, 0, WHITE);
                DrawTextureEx(Blocks[i].image, relativePos, 0, SCALE, WHITE);
            } else if (Blocks[i].name == "spike") {
                if (Blocks[i].direction == 1) {
                    relativePos.y += Blocks[i].rect.height;
                } else if (Blocks[i].direction == 2) {
                    relativePos.x += Blocks[i].rect.width;
                    relativePos.y += Blocks[i].rect.height;
                } else if (Blocks[i].direction == 3) {
                    relativePos.x += Blocks[i].rect.width;
                }

                DrawTextureEx(Blocks[i].image, relativePos, Blocks[i].direction*-90, SCALE, WHITE);
            } else {
                DrawTextureEx(Blocks[i].image, relativePos, 0, SCALE, WHITE);
            }
        }

        // Desenhando itens
        for (int i = 0; i < sizeI; i++) {
            if (Menu == 2) {
                if (GenericColision(itens[i].rect, placeItem.rect)) {
                    placeItem.rect.x += 2*SCALE;
                    placeItem.rect.y += 2*SCALE;
                    if (GenericColision(itens[i].rect, placeItem.rect)) {
                        placeItem.rect.x -= 4*SCALE;
                        placeItem.rect.y -= 4*SCALE;
                        if (GenericColision(itens[i].rect, placeItem.rect)) {
                            placeable = false;
                        } else {
                            placeItem.rect.x += 2*SCALE;
                            placeItem.rect.y += 2*SCALE;
                        }
                    } else {
                        placeItem.rect.x -= 2*SCALE;
                        placeItem.rect.y -= 2*SCALE;
                    }
                }
            }


            relativePos.x = WT/2 +itens[i].rect.x -cx;
            relativePos.y = HT/2 +itens[i].rect.y -cy;
            DrawTextureEx(itens[i].image, relativePos, 0, SCALE, WHITE);
        }



        if (placeable) {
            if (Menu == 1) {
                Blocks.push_back(placeBlock);
            } else if (Menu == 2) {
                itens.push_back(placeItem);
            }
        }



        // Drawing HUD

        if (Menu != 0) {
            DrawRectangle(WT*2/3, 0, WT/3, HT, GRAY);
        }

        if (Menu == 1) {
            for (Block blockOption : BlockOptions) {
                DrawTextureEx(blockOption.image, {blockOption.rect.x, blockOption.rect.y}, 0, SCALE, WHITE);
            }
        } else if (Menu == 2) {
            for (Item itemOption : ItemOptions) {
                DrawTextureEx(itemOption.image, {itemOption.rect.x, itemOption.rect.y}, 0, SCALE, WHITE);
            }
        }

        if (mouseBlock.SCALE != 0 or mouseItem.SCALE != 0) {
            if (Menu == 1) {
                if (background) {
                    DrawTextureEx(mouseBlock.image, {mouseBlock.rect.x, mouseBlock.rect.y}, 0, SCALE, GRAY);
                } else {
                    DrawTextureEx(mouseBlock.image, {mouseBlock.rect.x, mouseBlock.rect.y}, 0, SCALE, WHITE);
                }
            } else if (Menu == 2) {
                DrawTextureEx(mouseItem.image, {mouseItem.rect.x, mouseItem.rect.y}, 0, SCALE, WHITE);
            }
        }





        EndDrawing();
    }

}


void Play::HubLevelSelect() {
    Vector2 mousePosition;
    Rectangle mouseRect = {0, 0, 2, 2};
    int SCALER = 3;

    std::vector<std::string> Universe;
    search_universe(Universe);

    float positionX = 60;
    float positionY = 60;

    while (!WindowShouldClose()) {
        UpdateMusicStream(theme);
        mousePosition = GetMousePosition();
        mouseRect.x = mousePosition.x;
        mouseRect.y = mousePosition.y;



        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            positionY = 60;
            for (std::string level : Universe) {
                DrawRectangle(positionX, positionY, 200, 25, BLACK);
                Rectangle levelRect = {positionX, positionY, 200, 25};
                if (GenericColision(mouseRect, levelRect)) {
                    PlayLevel(level);
                }
                positionY += 30;
            }
        }




        BeginDrawing();
        ClearBackground(BLUE);
        positionY = 60;

        for (std::string level : Universe) {
            DrawRectangle(positionX, positionY, 200, 25, BLACK);
            Rectangle levelRect = {positionX, positionY, 200, 25};
            if (GenericColision(mouseRect, levelRect)) {
                DrawRectangle(positionX+2, positionY+2, 196, 21, YELLOW);
            } else {
                DrawRectangle(positionX+2, positionY+2, 196, 21, GRAY);
            }
            DrawText(level.c_str(), positionX+4, positionY+2, 20, BLACK);
            positionY += 30;
        }

        

        EndDrawing();
    }
}

void Play::PlayLevel(std::string levelname) {
    Map Level = loader.LoadFile(levelname);
    if (Level.playerX == -1) {
        return;
    }
    Blocks = Level.Blocks;
    itens = Level.itens;
    enemies = Level.enemies;
    player.rect.x = Level.playerX;
    player.rect.y = Level.playerY;
    RNGWidth = std::uniform_int_distribution<std::mt19937::result_type>(0, Level.widthLevel);
    RNGHeight = std::uniform_int_distribution<std::mt19937::result_type> (0, Level.heightLevel);

    Music LevelTheme;
    int song = RNG100(rng);
    if (song <= 0) {
        LevelTheme = LoadMusicStream("songs/BrighterWays.wav");
    }else if (song <= 2) {
        LevelTheme = LoadMusicStream("songs/Couragetheme.wav");
    } else if (song <= 7) {
        LevelTheme = LoadMusicStream("songs/Powertheme.wav");
    } else if (song <= 15) {
        LevelTheme = LoadMusicStream("songs/Resiliencetheme.wav");
    } else if (song <= 30) {
        LevelTheme = LoadMusicStream("songs/Hopetheme.wav");
    } else if (song <= 61) {
        LevelTheme = LoadMusicStream("songs/GrassyWalks.wav");
    } else {
        LevelTheme = LoadMusicStream("songs/HumidInsomnia.wav");
    }
    mainLoop(LevelTheme);
    UnloadMusicStream(LevelTheme);
}

void Play::mainLoop(Music LevelTheme) {
    SetTargetFPS(30);

    PlayMusicStream(LevelTheme);
    Vector2 mousePosition;
    
    while (!WindowShouldClose()) {
        UpdateMusicStream(LevelTheme);
        sizeB = Blocks.size();
        sizeE = enemies.size();
        sizeD = dusts.size();
        sizeS = effects.size();
        sizeI = itens.size();


        // Entities Updates
        for (int i = 0; i < sizeE; i++) {
            enemies[i].update(Blocks, player, effects);
        }
        player.update(Blocks, itens, enemies, effects);
        if (player.isBoost) {
            float posY = player.rect.y + RNG100(rng)*player.rect.height/100;
            Dust D1;
            D1.pos.x = player.cx;
            D1.pos.y = posY;
            D1.dt.x = 0;
            D1.dt.y = 0;
            D1.cor = {0, 255, 255, 127};
            D1.timer = RNG100(rng);

            dusts.push_back(D1);
        }

        if (abs(player.vy) > 8 or abs(player.vx) > 8) {
            tickBlockUpdate = 1;
        } else {
            tickBlockUpdate = 5;
        }

        // Particles
        for (int i = 0; i < sizeD; i++) {
            Dust D = dusts[i];
            D.timer -= 1;
            if (D.timer <= 0) {
                auto it = std::next(dusts.begin(), i);
                dusts.erase(it);
            } else {
                D.pos.x += D.dt.x;
                D.pos.y += D.dt.y;
                D.dt.y += 0.1;
                dusts[i] = D;
            }
        }

        // Effects
        for (int i = 0; i < sizeS; i++) {
            if (effects[i].update(Blocks, player, itens, enemies)) {
                Dust D1, D2, D3;
                D1.pos.x = effects[i].cx;
                D1.pos.y = effects[i].cy;
                D2.pos.x = effects[i].cx;
                D2.pos.y = effects[i].cy;
                D3.pos.x = effects[i].cx;
                D3.pos.y = effects[i].cy;

                D1.dt.x = RNG100(rng)*5/100;
                D1.dt.y = RNG100(rng)*5/100;
                D2.dt.x = RNG100(rng)*5/100;
                D2.dt.y = RNG100(rng)*5/100;
                D3.dt.x = RNG100(rng)*5/100;
                D3.dt.y = RNG100(rng)*5/100;

                unsigned char color1 = RNG100(rng)*255/100;
                unsigned char color2 = RNG100(rng)*255/100;
                unsigned char color3 = RNG100(rng)*255/100;
                D1.cor = {color1, color2, color3, 127};
                D1.timer = RNG100(rng);

                D2.cor = {color1, color2, color3, 127};
                D2.timer = RNG100(rng);

                D3.cor = {color1, color2, color3, 127};
                D3.timer = RNG100(rng);

                dusts.push_back(D1);
                dusts.push_back(D2);
                dusts.push_back(D3);

                auto it = std::next(effects.begin(), i);
                effects.erase(it);
            }
        }

        Rectangle center = {WT/2, HT/2, player.rect.width, player.rect.height};

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
            if (!Blocks[i].background) {
                continue;
            }
            Vector2 relativePos;
            relativePos.x = center.x +Blocks[i].rect.x -player.rect.x;
            relativePos.y = center.y +Blocks[i].rect.y -player.rect.y;
            
            if (Blocks[i].name == "gate-hope") {
                Rectangle cut, dest;
                dest.x = relativePos.x;
                dest.y = relativePos.y;
                dest.width = 13*SCALE;
                dest.height = 25*SCALE;

                cut.x = 0;
                cut.y = 0;
                cut.width = 13;
                cut.height = 25;
                DrawTexturePro(Blocks[i].image, cut, dest, {0, 0}, 0, GRAY);
            } else {
                DrawTextureEx(Blocks[i].image, relativePos, 0, SCALE, GRAY);
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
            DrawTexturePro(player.images[player.imageCount], {0.0f, 0.0f, player.rectImage.width, player.rectImage.height}, center, {0, 0}, 0, playerColor);
        } else {
            DrawTexturePro(player.images[player.imageCount], {0.0f, 0.0f, -player.rectImage.width, player.rectImage.height}, center, {0, 0}, 0, playerColor);
        }



        // Desenhando inimigos
        for (int i = 0; i < sizeE; i++) {
            Vector2 relativePos;
            Rectangle source, dest;

            relativePos.x = center.x +enemies[i].rect.x -player.rect.x;
            relativePos.y = center.y +enemies[i].rect.y -player.rect.y;

            source.x = 0 + enemies[i].imageCount*(enemies[i].rectImage.width+1);
            source.y = 0;
            source.width = enemies[i].rectImage.width;
            source.height = enemies[i].rectImage.height;

            dest.x = relativePos.x;
            dest.y = relativePos.y;
            dest.width = enemies[i].rect.width;
            dest.height = enemies[i].rect.height;

            if (enemies[i].name == "bee") {
                DrawTexturePro(enemies[i].images[0], source, dest, {0, 0}, 0, WHITE);
            } else if (enemies[i].name == "snail") {
                if (enemies[i].behavior == 1) {
                    dest.y += enemies[i].rect.width;
                } else if (enemies[i].behavior == 2) {
                    dest.y += enemies[i].rect.height;
                    dest.x += enemies[i].rect.width;
                } else if (enemies[i].behavior == 3) {
                    dest.x += enemies[i].rect.height;
                }
                DrawTexturePro(enemies[i].images[0], source, dest, {0, 0}, enemies[i].behavior*-90, WHITE);
            } else if (enemies[i].name == "butterfly") {
                DrawTexturePro(enemies[i].images[0], source, dest, {0, 0}, 0, WHITE);
            } else if (enemies[i].name == "crab") {
                // DrawRectangle(relativePos.x, relativePos.y, enemies[i].rect.width, enemies[i].rect.height, RED);
                DrawTexturePro(enemies[i].images[0], source, dest, {0, 0}, 0, WHITE);
            } else if (enemies[i].name == "meldrop") {
                if (enemies[i].behavior > 1) {
                    source.x += enemies[i].rect.width+1;
                }
                DrawTexturePro(enemies[i].images[0], source, dest, {0, 0}, 0, WHITE);
            } else {
                DrawRectangle(relativePos.x, relativePos.y, enemies[i].rect.width, enemies[i].rect.height, BLACK);
            }
        }

        // Desenhando blocos Ground
        for (int i = 0; i < sizeB; i++) {
            if (Blocks[i].background) {
                continue;
            }
            Vector2 relativePos;
            relativePos.x = center.x +Blocks[i].rect.x -player.rect.x;
            relativePos.y = center.y +Blocks[i].rect.y -player.rect.y;
            if (Blocks[i].name == "gate-hope") {
                Rectangle cut, dest;
                dest.x = relativePos.x;
                dest.y = relativePos.y;
                dest.width = 13*SCALE;
                dest.height = 25*SCALE;

                cut.x = 0;
                cut.y = 24;
                cut.width = 13;
                cut.height = 25;
                DrawTexturePro(Blocks[i].image, cut, dest, {0, 0}, 0, WHITE);
            } else if (Blocks[i].name == "spike") {
                if (Blocks[i].direction == 1) {
                    relativePos.y += Blocks[i].rect.height;
                } else if (Blocks[i].direction == 2) {
                    relativePos.x += Blocks[i].rect.width;
                    relativePos.y += Blocks[i].rect.height;
                } else if (Blocks[i].direction == 3) {
                    relativePos.x += Blocks[i].rect.width;
                }

                DrawTextureEx(Blocks[i].image, relativePos, Blocks[i].direction*-90, SCALE, WHITE);
            } else {
                DrawTextureEx(Blocks[i].image, relativePos, 0, SCALE, WHITE);
            }
        }

        // Desenhando itens
        for (int i = 0; i < sizeI; i++) {
            Vector2 relativePos;
            relativePos.x = center.x +itens[i].rect.x -player.rect.x;
            relativePos.y = center.y +itens[i].rect.y -player.rect.y;
            DrawTextureEx(itens[i].image, relativePos, 0, SCALE, WHITE);
        }

        // Desenhando Efeitos
        for (int i = 0; i < sizeS; i++) {
            Effect temp = effects[i];
            Vector2 relativePos;
            Rectangle source, dest;

            relativePos.x = center.x +temp.rect.x -player.rect.x;
            relativePos.y = center.y +temp.rect.y -player.rect.y;

            source.x = 0 + temp.imageCount*(temp.rectImage.width);
            source.y = 0;
            source.width = temp.rectImage.width;
            source.height = temp.rectImage.height;

            dest.x = relativePos.x;
            dest.y = relativePos.y;
            dest.width = temp.rect.width;
            dest.height = temp.rect.height;
            if (temp.id == 2) {
                float angle = temp.timer*3;
                DrawTexturePro(temp.image, source, dest, {0, 0}, angle, WHITE);
            } else if (temp.id == 3) {
                if (temp.vx < 0) {
                    source.width = -source.width;
                }
                DrawTexturePro(temp.image, source, dest, {0, 0}, 0, WHITE);
            } else {
                DrawTexturePro(temp.image, source, dest, {0, 0}, 0, WHITE);
            }
        }

        // Desenhando Particulas
        for (int i = 0; i < sizeD; i++) {
            Dust D = dusts[i];
            Vector2 relativePos;

            relativePos.x = center.x +D.pos.x -player.rect.x;
            relativePos.y = center.y +D.pos.y -player.rect.y;
            DrawCircle(relativePos.x, relativePos.y, (D.timer/20)+SCALE, {0, 0, 0, 127});
            DrawCircle(relativePos.x, relativePos.y, (D.timer/20), D.cor);
        }










        // fun-mode
        if (tick % 30 == 0 and sizeI < 200) {
            int RNG_X = (RNGWidth(rng))*(BS-SCALE);
            int RNG_Y = (RNGHeight(rng)-1)*(BS-SCALE);
            bool freespace = true;
            Rectangle tempItem = {(float) RNG_X, (float) RNG_Y, 13, 13};
            for (int i = 0; i < sizeB; i++) {
                Block temp = Blocks[i];
                if (GenericColision(tempItem, temp.rect)) {
                    int value = RNGe3(rng);
                    if (value <= 1) {
                        enemies.push_back(Enemy(RNG_X, RNG_Y, "snail", SCALE, Blocks, RNG100(rng), temp));
                    } else if (value <= 5) {
                        bool spawnable;
                        for(int j = 0; j < sizeB; j++) {
                            Block tempCeil = Blocks[j];
                            if (tempCeil.rect.x+tempCeil.rect.width > temp.rect.x and tempCeil.rect.x < temp.rect.x+temp.rect.width) {
                                if (tempCeil.rect.y+tempCeil.rect.height > temp.rect.y and tempCeil.rect.y < temp.rect.y) {
                                    spawnable = false;
                                    break;
                                }
                            }
                        }
                        if (spawnable) {
                            enemies.push_back(Enemy(RNG_X, RNG_Y, "crab", SCALE, Blocks, RNG100(rng), temp));
                        }
                    }
                    freespace = false;
                    break;
                }
            }
            if (freespace) {
                int value = RNGe3(rng);
                if (value <= 1) {
                    itens.push_back(Item(RNG_X, RNG_Y, "Pshard-eloise", SCALE, 'P'));
                } else if (value <= 4) {
                    itens.push_back(Item(RNG_X, RNG_Y, "Pshard-hard", SCALE, 'P'));
                } else if (value <= 8) {
                    itens.push_back(Item(RNG_X, RNG_Y, "Pshard-fun", SCALE, 'P'));
                } else if (value <= 13) {
                    itens.push_back(Item(RNG_X, RNG_Y, "Pshard-party", SCALE, 'P'));
                } else if (value <= 19) {
                    itens.push_back(Item(RNG_X, RNG_Y, "Pshard-wind", SCALE, 'P'));
                } else if (value <= 28) {
                    itens.push_back(Item(RNG_X, RNG_Y, "Hshard-wisdom", SCALE, 'H'));
                } else if (value <= 38) {
                    itens.push_back(Item(RNG_X, RNG_Y, "Hshard-courage", SCALE, 'H'));
                } else if (value <= 50) {
                    itens.push_back(Item(RNG_X, RNG_Y, "Hshard-power", SCALE, 'H'));
                } else if (value <= 64) {
                    itens.push_back(Item(RNG_X, RNG_Y, "Hshard-resilience", SCALE, 'H'));
                } else if (value <= 80) {
                    itens.push_back(Item(RNG_X, RNG_Y, "Hshard-hope", SCALE, 'H'));
                } else if (value <= 82) {
                    itens.push_back(Item(RNG_X, RNG_Y, "courage-potion", SCALE, 'I'));
                } else if (value <= 90) {
                    itens.push_back(Item(RNG_X, RNG_Y, "coin-gold", SCALE, 'C'));
                } else if (value <= 130) {
                    itens.push_back(Item(RNG_X, RNG_Y, "coin-silver", SCALE, 'C'));
                } else if (value <= 200) {
                    itens.push_back(Item(RNG_X, RNG_Y, "coin-copper", SCALE, 'C'));
                } else if (value <= 280) {
                    itens.push_back(Item(RNG_X, RNG_Y, "food-orange", SCALE, 'F'));
                } else if (value <= 370) {
                    itens.push_back(Item(RNG_X, RNG_Y, "food-pepper", SCALE, 'F'));
                } else if (value <= 540) {
                    itens.push_back(Item(RNG_X, RNG_Y, "food-blueberry", SCALE, 'F'));
                } else if (value <= 680) {
                    itens.push_back(Item(RNG_X, RNG_Y, "food-pear", SCALE, 'F'));
                } else if (value <= 997) {
                    itens.push_back(Item(RNG_X, RNG_Y, "food-banana", SCALE, 'F'));
                } else if (value <= 998) {
                    enemies.push_back(Enemy(RNG_X, RNG_Y, "bee", SCALE, Blocks, RNG100(rng)));
                } else if (value <= 999) {
                    enemies.push_back(Enemy(RNG_X, RNG_Y, "butterfly", SCALE, Blocks, RNG100(rng)));
                } else if (value <= 1000) {
                    enemies.push_back(Enemy(RNG_X, RNG_Y, "meldrop", SCALE, Blocks, RNG100(rng)));
                } else {
                    itens.push_back(Item(RNG_X, RNG_Y, "key-hope", SCALE, 'K'));
                }
                sizeI += 1;
            }
        }











        // Desenhando HUD
        DesenharHeart();
        DesenharPearl();
        DrawText(TextFormat("Score: %d", player.score), GetScreenWidth()/2-100, 30, 20, WHITE);
        DrawText(TextFormat("Time: %d", seconds), GetScreenWidth()/2-100, 0, 20, WHITE);
        if (player.keyHope > 0) {
            DrawText(TextFormat("Yellow Keys: %d", player.keyHope), GetScreenWidth() - 300, 50, 20, WHITE);
        }
        DrawText(TextFormat("itens no mapa: %d", itens.size()), GetScreenWidth()-300, 220, 20, WHITE);
        if (player.powers[0]) {
            DrawTextureEx(player.P1image, {(float) GetScreenWidth()/2+20*SCALE, 20}, 0, SCALE, WHITE);
            DrawText("1", (float) GetScreenWidth()/2+27*SCALE, 20+15*SCALE, 20, BLACK);
        }
        if (player.powers[1]) {
            // DrawTextureEx(player.P2image, {(float) GetScreenWidth()/2+40*SCALE, 20}, 0, SCALE, WHITE);
            DrawText("2", (float) GetScreenWidth()/2+47*SCALE, 20+15*SCALE, 20, BLACK);
        }
        if (player.powers[2]) {
            DrawTextureEx(player.P3image, {(float) GetScreenWidth()/2+60*SCALE, 20}, 0, SCALE, WHITE);
            DrawText("3", (float) GetScreenWidth()/2+67*SCALE, 20+15*SCALE, 20, BLACK);
        }
        if (player.powers[3]) {
            DrawTextureEx(player.P4image, {(float) GetScreenWidth()/2+80*SCALE, 20}, 0, SCALE, WHITE);
            DrawText("4", (float) GetScreenWidth()/2+87*SCALE, 20+15*SCALE, 20, BLACK);
        }
        if (player.powers[4]) {
            DrawTextureEx(player.P5image, {(float) GetScreenWidth()/2+100*SCALE, 20}, 0, SCALE, WHITE);
            DrawText("5", (float) GetScreenWidth()/2+107*SCALE, 20+15*SCALE, 20, BLACK);
        }













        // Color test for White Flamingo

        // if (IsKeyPressed(KEY_F)) {
        //     setFlamingo[0] += 1;
        //     if (setFlamingo[0] > 255) {
        //         setFlamingo[0] = 0;
        //     }
        // }
        // if (IsKeyPressed(KEY_G)) {
        //     setFlamingo[1] += 1;
        //     if (setFlamingo[1] > 255) {
        //         setFlamingo[1] = 0;
        //     }
        // }
        // if (IsKeyPressed(KEY_H)) {
        //     setFlamingo[2] += 1;
        //     if (setFlamingo[2] > 255) {
        //         setFlamingo[2] = 0;
        //     }
        // }
        // if (IsKeyPressed(KEY_V)) {
        //     setFlamingo[0] -= 1;
        //     if (setFlamingo[0] < 0) {
        //         setFlamingo[0] = 255;
        //     }
        // }
        // if (IsKeyPressed(KEY_B)) {
        //     setFlamingo[1] -= 1;
        //     if (setFlamingo[1] > 0) {
        //         setFlamingo[1] = 255;
        //     }
        // }
        // if (IsKeyPressed(KEY_N)) {
        //     setFlamingo[2] -= 1;
        //     if (setFlamingo[2] > 0) {
        //         setFlamingo[2] = 255;
        //     }
        // }


        // Color test = {(unsigned char)setFlamingo[0], (unsigned char)setFlamingo[1], (unsigned char)setFlamingo[2], (unsigned char)setFlamingo[3]};
        // DrawRectangle(100, 50, 60, 60, test);



        if (DEBUG) {
            Vector2 relativePos;
            relativePos.x = WT/2 +player.groundBlock.rect.x -player.rect.x;
            relativePos.y = HT/2 +player.groundBlock.rect.y -player.rect.y;
            DrawRectangle(relativePos.x, relativePos.y, player.groundBlock.rect.width, player.groundBlock.rect.height, YELLOW);

            
            DrawText(TextFormat("X=%02.02f, Y=%02.02f, W=%02.02f, H=%02.02f", player.groundBlock.rect.x, player.groundBlock.rect.y, player.groundBlock.rect.width, player.groundBlock.rect.height), GetScreenWidth()/2 - 200, 100, 30, WHITE);
            if (player.crouch) {
                relativePos.x = center.x +player.HitboxA.x -player.rect.x;
                relativePos.y = center.y +player.HitboxA.y -player.rect.y;
                DrawRectangle(relativePos.x, relativePos.y, player.HitboxA.width, player.HitboxA.height, RED);
            } else {
                relativePos.x = center.x +player.Hitbox1.x -player.rect.x;
                relativePos.y = center.y +player.Hitbox1.y -player.rect.y;
                DrawRectangle(relativePos.x, relativePos.y, player.Hitbox1.width, player.Hitbox1.height, RED);
                relativePos.x = center.x +player.Hitbox2.x -player.rect.x;
                relativePos.y = center.y +player.Hitbox2.y -player.rect.y;
                DrawRectangle(relativePos.x, relativePos.y, player.Hitbox2.width, player.Hitbox2.height, RED);
                relativePos.x = center.x +player.Hitbox3.x -player.rect.x;
                relativePos.y = center.y +player.Hitbox3.y -player.rect.y;
                DrawRectangle(relativePos.x, relativePos.y, player.Hitbox3.width, player.Hitbox3.height, RED);
            }
            relativePos.x = center.x +player.HB1.x -player.rect.x;
            relativePos.y = center.y +player.HB1.y -player.rect.y;
            DrawRectangle(relativePos.x, relativePos.y, player.HB1.width, player.HB1.height, DARKBLUE);

            relativePos.x = center.x +player.cx -player.rect.x;
            relativePos.y = center.y +player.cy -player.rect.y;
            DrawCircle(relativePos.x, relativePos.y, 5, PURPLE);


            int sizeCB = player.CBs.size();
            for (int i = 0; i < sizeCB; i++) {
                Block temp = Blocks[player.CBs[i]];
                relativePos.x = center.x +temp.rect.x -player.rect.x;
                relativePos.y = center.y +temp.rect.y -player.rect.y;
                DrawRectangle(relativePos.x, relativePos.y, temp.rect.width, temp.rect.height, GRAY);
            }
            for (int i = 0; i < sizeE; i++) {
                // relativePos.x = center.x +enemies[i].rect.x -player.rect.x;
                // relativePos.y = center.y +enemies[i].rect.y -player.rect.y;
                // DrawRectangle(relativePos.x, relativePos.y, enemies[i].rect.width, enemies[i].rect.height, RED);
                if (enemies[i].name == "crab") {
                    relativePos.x = center.x +enemies[i].patrol1 -player.rect.x;
                    relativePos.y = center.y +enemies[i].ground.rect.y -player.rect.y;
                    DrawCircle(relativePos.x, relativePos.y, 5, YELLOW);
                    relativePos.x = center.x +enemies[i].patrol2 -player.rect.x;
                    relativePos.y = center.y +enemies[i].ground.rect.y -player.rect.y;
                    DrawCircle(relativePos.x, relativePos.y, 5, YELLOW);
                    relativePos.x = center.x +enemies[i].ground.rect.x -player.rect.x;
                    relativePos.y = center.y +enemies[i].ground.rect.y -player.rect.y;
                    DrawRectangle(relativePos.x, relativePos.y, enemies[i].ground.rect.width, enemies[i].ground.rect.height, YELLOW);
                    relativePos.x = center.x +enemies[i].border1.rect.x -player.rect.x;
                    relativePos.y = center.y +enemies[i].border1.rect.y -player.rect.y;
                    DrawRectangle(relativePos.x, relativePos.y, enemies[i].border1.rect.width, enemies[i].border1.rect.height, GREEN);
                    relativePos.x = center.x +enemies[i].border2.rect.x -player.rect.x;
                    relativePos.y = center.y +enemies[i].border2.rect.y -player.rect.y;
                    DrawRectangle(relativePos.x, relativePos.y, enemies[i].border2.rect.width, enemies[i].border2.rect.height, GREEN);
                } else if (enemies[i].name == "butterfly") {
                    relativePos.x = center.x +enemies[i].orbit.x -player.rect.x;
                    relativePos.y = center.y +enemies[i].orbit.y -player.rect.y;
                    DrawCircle(relativePos.x, relativePos.y, 5, YELLOW);
                } else if (enemies[i].name == "snail") {
                    relativePos.x = center.x +enemies[i].vision.x -player.rect.x;
                    relativePos.y = center.y +enemies[i].vision.y -player.rect.y;
                    DrawRectangle(relativePos.x, relativePos.y, enemies[i].vision.width, enemies[i].vision.height, BLACK);
                    relativePos.x = center.x +enemies[i].HBFeet.x -player.rect.x;
                    relativePos.y = center.y +enemies[i].HBFeet.y -player.rect.y;
                    DrawRectangle(relativePos.x, relativePos.y, enemies[i].HBFeet.width, enemies[i].HBFeet.height, BLACK);
                    if (enemies[i].ground.SCALE == 0) {
                        DrawText("UNEXPECTED SNAIL BEHAVIOR 2", GetScreenWidth() - 520, 40, 20, RED);
                    } else {
                        relativePos.x = center.x +enemies[i].ground.rect.x -player.rect.x;
                        relativePos.y = center.y +enemies[i].ground.rect.y -player.rect.y;
                        DrawRectangle(relativePos.x, relativePos.y, enemies[i].ground.rect.width, enemies[i].ground.rect.height, YELLOW);
                    }
                } else if (enemies[i].name == "bee") {
                    relativePos.x = center.x +enemies[i].patrol1 -player.rect.x;
                    relativePos.y = center.y +enemies[i].rect.y -player.rect.y;
                    DrawCircle(relativePos.x, relativePos.y, 5, YELLOW);
                    relativePos.x = center.x +enemies[i].patrol2 -player.rect.x;
                    relativePos.y = center.y +enemies[i].rect.y -player.rect.y;
                    DrawCircle(relativePos.x, relativePos.y, 5, YELLOW);
                }
                relativePos.x = center.x +enemies[i].cx -player.rect.x;
                relativePos.y = center.y +enemies[i].cy -player.rect.y;
                DrawCircle(relativePos.x, relativePos.y, 5, YELLOW);
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

}

void Play::DesenharHeart() {
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

void Play::DesenharPearl() {
        Rectangle PHud = {GetScreenWidth() - 20.0f*SCALE, 10.0f, 11.0f*SCALE, 11.0f*SCALE};
        // Wind
        int WPTemp = player.WP/7;
        int WPPart = player.WP % 7;
        int WPEmptyTemp = (player.MWP - player.WP)/7;
        while (WPTemp > 0) {
            DrawTexturePro(player.PearlGrid, {0.0f, 0.0f, 11.0f, 11.0f}, PHud, {0, 0}, 0, WHITE);
            PHud.x -= 12*SCALE;
            WPTemp--;
        }
        if (WPPart > 0) {
            DrawTexturePro(player.PearlGrid, {(12.0f*(7-WPPart)), 0.0f, -11.0f, 11.0f}, PHud, {0, 0}, 0, WHITE);
            PHud.x -= 12*SCALE;
        }
        while (WPEmptyTemp > 0) {
            DrawTexturePro(player.PearlGrid, {12.0f*7, 0.0f, 11.0f, 11.0f}, PHud, {0, 0}, 0, WHITE);
            PHud.x -= 12*SCALE;
            WPEmptyTemp--;
        }
        if (player.PWP > 0) {
            DrawText(TextFormat("%d+", player.PWP), PHud.x, PHud.y, 35, {223, 245, 0, 255});
        }

        PHud.x = GetScreenWidth() - 20.0f*SCALE;
        PHud.y += 12.0f*SCALE;



        // Party
        int PPTemp = player.PP/7;
        int PPPart = player.PP % 7;
        int PPEmptyTemp = (player.MPP - player.PP)/7;
        while (PPTemp > 0) {
            DrawTexturePro(player.PearlGrid, {0.0f, 12.0f, 11.0f, 11.0f}, PHud, {0, 0}, 0, WHITE);
            PHud.x -= 12*SCALE;
            PPTemp--;
        }
        if (PPPart > 0) {
            DrawTexturePro(player.PearlGrid, {(12.0f*(7-PPPart)), 12.0f, -11.0f, 11.0f}, PHud, {0, 0}, 0, WHITE);
            PHud.x -= 12*SCALE;
        }
        while (PPEmptyTemp > 0) {
            DrawTexturePro(player.PearlGrid, {12.0f*7, 12.0f, 11.0f, 11.0f}, PHud, {0, 0}, 0, WHITE);
            PHud.x -= 12*SCALE;
            PPEmptyTemp--;
        }
        if (player.PPP > 0) {
            DrawText(TextFormat("%d+", player.PPP), PHud.x, PHud.y, 35, {133, 255, 0, 255});
        }

        PHud.x = GetScreenWidth() - 20.0f*SCALE;
        PHud.y += 12.0f*SCALE;



        // Fun
        int FPTemp = player.FP/7;
        int FPPart = player.FP % 7;
        int FPEmptyTemp = (player.MFP - player.FP)/7;
        while (FPTemp > 0) {
            DrawTexturePro(player.PearlGrid, {0.0f, 12.0f*2, 11.0f, 11.0f}, PHud, {0, 0}, 0, WHITE);
            PHud.x -= 12*SCALE;
            FPTemp--;
        }
        if (FPPart > 0) {
            DrawTexturePro(player.PearlGrid, {(12.0f*(7-FPPart)), 12.0f*2, -11.0f, 11.0f}, PHud, {0, 0}, 0, WHITE);
            PHud.x -= 12*SCALE;
        }
        while (FPEmptyTemp > 0) {
            DrawTexturePro(player.PearlGrid, {12.0f*7, 12.0f*2, 11.0f, 11.0f}, PHud, {0, 0}, 0, WHITE);
            PHud.x -= 12*SCALE;
            FPEmptyTemp--;
        }
        if (player.PFP > 0) {
            DrawText(TextFormat("%d+", player.PFP), PHud.x, PHud.y, 35, {30, 235, 210, 255});
        }

        PHud.x = GetScreenWidth() - 20.0f*SCALE;
        PHud.y += 12.0f*SCALE;



        // Hard
        int HPTemp = player.HP/7;
        int HPPart = player.HP % 7;
        int HPEmptyTemp = (player.MHP - player.HP)/7;
        while (HPTemp > 0) {
            DrawTexturePro(player.PearlGrid, {0.0f, 12.0f*3, 11.0f, 11.0f}, PHud, {0, 0}, 0, WHITE);
            PHud.x -= 12*SCALE;
            HPTemp--;
        }
        if (HPPart > 0) {
            DrawTexturePro(player.PearlGrid, {(12.0f*(7-HPPart)), 12.0f*3, -11.0f, 11.0f}, PHud, {0, 0}, 0, WHITE);
            PHud.x -= 12*SCALE;
        }
        while (HPEmptyTemp > 0) {
            DrawTexturePro(player.PearlGrid, {12.0f*7, 12.0f*3, 11.0f, 11.0f}, PHud, {0, 0}, 0, WHITE);
            PHud.x -= 12*SCALE;
            HPEmptyTemp--;
        }
        if (player.PHP > 0) {
            DrawText(TextFormat("%d+", player.PHP), PHud.x, PHud.y, 35, {253, 105, 150, 255});
        }

        PHud.x = GetScreenWidth() - 20.0f*SCALE;
        PHud.y += 12.0f*SCALE;



        // Eloise
        int EPTemp = player.EP/7;
        int EPPart = player.EP % 7;
        int EPEmptyTemp = (player.MEP - player.EP)/7;
        while (EPTemp > 0) {
            DrawTexturePro(player.PearlGrid, {0.0f, 12.0f*4, 11.0f, 11.0f}, PHud, {0, 0}, 0, WHITE);
            PHud.x -= 12*SCALE;
            EPTemp--;
        }
        if (EPPart > 0) {
            DrawTexturePro(player.PearlGrid, {(12.0f*(7-EPPart)), 12.0f*4, 11.0f, 11.0f}, PHud, {0, 0}, 0, WHITE);
            PHud.x -= 12*SCALE;
        }
        while (EPEmptyTemp > 0) {
            DrawTexturePro(player.PearlGrid, {12.0f*7, 12.0f*4, 11.0f, 11.0f}, PHud, {0, 0}, 0, WHITE);
            PHud.x -= 12*SCALE;
            EPEmptyTemp--;
        }
        if (player.PEP > 0) {
            DrawText(TextFormat("%d+", player.PEP), PHud.x, PHud.y, 35, {255, 150, 150, 255});
        }
    }
