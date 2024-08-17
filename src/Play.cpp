#include "../include/Play.hpp"


Play::Play() {
    loader.reset(new MapLoader(SCALE, BS, WT, HT));
    rng = std::mt19937(dev());
    RNG100 = std::uniform_int_distribution<std::mt19937::result_type>(1, 100);
    RNGe3 = std::uniform_int_distribution<std::mt19937::result_type>(0, 1000);
}

Play::~Play() {
    UnloadTexture(iconEditor);
    UnloadTexture(iconGame);
    UnloadSound(finish);
    player->unload();
}



void Play::loadFlamingo() {
    player.reset(new Flamingo(400, 400, FW, FH, WT, HT, SCALE));
    player->game = this;
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
    theme = LoadMusicStream("assets/audio/songs/MainTheme.wav");
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


void Play::DustBringer(float x, float y, Color cor, int timer, bool random, std::string dialog) {
    Dust D;
    D.dialog = dialog;
    D.pos.x = x;
    D.pos.y = y;
    int speed = RNG100(rng);
    if (speed % 2 == 0) {
        D.dt.x = -speed/25;
    } else {
        D.dt.x = speed/25;
    }
    D.dt.y = 0;
    if (random) {
        unsigned char color1 = RNG100(rng)*255/100;
        unsigned char color2 = RNG100(rng)*255/100;
        unsigned char color3 = RNG100(rng)*255/100;
        cor = {color1, color2, color3, 127};
    }
    D.cor = cor;
    D.timer = timer;

    dusts.push_back(D);
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

int Play::complexityCalc(Item temp) {
    if (temp.name == "coin-copper") {
        return 1;
    } else if (temp.name == "silver-coin") {
        return 8;
    } else if (temp.name == "gold-coin") {
        return 18;
    } else if (temp.name == "food-banana") {
        return 2;
    } else if (temp.name == "food-pear") {
        return 3;
    } else if (temp.name == "food-blueberry") {
        return 4;
    } else if (temp.name == "food-pepper") {
        return 5;
    } else if (temp.name == "food-orange") {
        return 6;
    } else if (temp.name == "potion-courage") {
        return 10;
    } else if (temp.name == "potion-party") {
        return 10;
    } else if (temp.name == "Hshard-hope") {
        return 35;
    } else if (temp.name == "Hshard-resilience") {
        return 40;
    } else if (temp.name == "Hshard-power") {
        return 45;
    } else if (temp.name == "Hshard-courage") {
        return 50;
    } else if (temp.name == "Hshard-wisdom") {
        return 55;
    } else if (temp.name == "Pshard-wind") {
        return 45;
    } else if (temp.name == "Pshard-party") {
        return 50;
    } else if (temp.name == "Pshard-fun") {
        return 60;
    } else if (temp.name == "Pshard-hard") {
        return 70;
    } else if (temp.name == "Pshard-eloise") {
        return 80;
    } else if (temp.name == "power-dash") {
        return 60;
    } else if (temp.name == "power-toast") {
        return 70;
    } else if (temp.name == "power-boost") {
        return 80;
    } else if (temp.name == "power-spear") {
        return 90;
    } else if (temp.name == "power-transmutation") {
        return 100;
    }
    return 0;
}

int Play::complexityCalc(Enemy temp) {
    if (temp.name == "bee") {
        return 12;
    } else if (temp.name == "snail") {
        return 21;
    } else if (temp.name == "butterfly") {
        return 30;
    } else if (temp.name == "crab") {
        return 43;
    } else if (temp.name == "meldrop") {
        return 60;
    }
    return 0;
}

void Play::EditLevel(std::string name) {
    Map LevelMap = loader->LoadLevel(name);
    Blocks = LevelMap.Blocks;
    itens = LevelMap.itens;
    enemies = LevelMap.enemies;
    seconds = LevelMap.time;
    widthLevel = LevelMap.widthLevel;
    heightLevel = LevelMap.heightLevel;

    for (Block temp : Blocks) {
        if (temp.name == "startLevel") {
            player->rect.x = temp.rect.x + 1;
            player->rect.y = temp.rect.y-SCALE;
        }
    }


    cx = WT/2;
    relativeCameraCenter.x = WT/2;
    cy = HT/2;
    relativeCameraCenter.y = HT/2;
    bool W, A, S, D, E, R, Q, F;
    Vector2 relativePos;
    Texture2D grid = LoadTexture("assets/images/grid.png");
    Rectangle mouseRect = {0, 0, 2, 2};


    int Menu = 0;
    std::vector<Block> BlockOptions;

    BlockOptions.push_back(Block(0, 0, BS, BS, "dirt", SCALE));
    BlockOptions.push_back(Block(0, 0, BS*2-SCALE, BS*2-SCALE, "dirt2", SCALE));
    BlockOptions.push_back(Block(0, 0, BS, BS, "grass", SCALE));
    BlockOptions.push_back(Block(0, 0, BS, BS, "brick", SCALE));
    BlockOptions.push_back(Block(0, 0, BS, BS, "spike", SCALE));
    BlockOptions.push_back(Block(0, 0, BS, BS, "altar", SCALE));
    BlockOptions.push_back(Block(0, 0, BS, BS*2-SCALE, "gate-hope", SCALE));
    BlockOptions.push_back(Block(0, 0, BS, BS*2-SCALE, "gate-resilience", SCALE));
    BlockOptions.push_back(Block(0, 0, BS, BS*2-SCALE, "gate-power", SCALE));
    BlockOptions.push_back(Block(0, 0, BS, BS*2-SCALE, "gate-courage", SCALE));
    BlockOptions.push_back(Block(0, 0, BS, BS*2-SCALE, "gate-wisdom", SCALE));
    BlockOptions.push_back(Block(0, 0, BS*2-SCALE, BS, "platform", SCALE));
    BlockOptions.push_back(Block(0, 0, BS, BS*2-SCALE, "nextLevel", SCALE));
    BlockOptions.push_back(Block(0, 0, BS, BS*2-SCALE, "startLevel", SCALE));
    BlockOptions.push_back(Block(0, 0, BS, BS, "cage", SCALE));
    BlockOptions.push_back(Block(0, 0, BS, BS, "honey", SCALE));
    BlockOptions.push_back(Block(0, 0, BS, BS, "vines", SCALE));
    BlockOptions.push_back(Block(0, 0, BS, BS, "ivy", SCALE));
    BlockOptions.push_back(Block(0, 0, BS, BS, "switch_green", SCALE));
    BlockOptions.push_back(Block(0, 0, BS, BS, "green", SCALE));
    // BlockOptions.push_back(Block(0, 0, (BS-SCALE)*5+SCALE, BS*2-SCALE, "rotator", SCALE));
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
    ItemOptions.push_back(Item(0, 0, "key-resilience", SCALE, 'K'));
    ItemOptions.push_back(Item(0, 0, "key-power", SCALE, 'K'));
    ItemOptions.push_back(Item(0, 0, "key-courage", SCALE, 'K'));
    ItemOptions.push_back(Item(0, 0, "key-wisdom", SCALE, 'K'));
    ItemOptions.push_back(Item(0, 0, "power-dash", SCALE, 'S'));
    ItemOptions.push_back(Item(0, 0, "power-toast", SCALE, 'S'));
    ItemOptions.push_back(Item(0, 0, "power-boost", SCALE, 'S'));
    ItemOptions.push_back(Item(0, 0, "power-spear", SCALE, 'S'));
    ItemOptions.push_back(Item(0, 0, "coin-poison", SCALE, 'C'));
    ItemOptions.push_back(Item(0, 0, "power-transmutation", SCALE, 'S'));
    std::vector<Enemy> EnemyOptions;
    std::map<int, std::map<int, Block>> templates;
    EnemyOptions.push_back(Enemy(0, 0, "bee", SCALE, templates, 0));
    EnemyOptions.push_back(Enemy(0, 0, "snail", SCALE, templates, 0));
    EnemyOptions.push_back(Enemy(0, 0, "butterfly", SCALE, templates, 0));
    EnemyOptions.push_back(Enemy(0, 0, "crab", SCALE, templates, 0));
    EnemyOptions.push_back(Enemy(0, 0, "meldrop", SCALE, templates, 0));

    ItemHandler itensLevelTaker(itens), itensOptionsTaker(ItemOptions);
    BlockHandler blocksLevelTaker(Blocks, this), blocksOptionsTaker(BlockOptions, this);


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


    Px = WT*2/3 + 30;
    Py = 50;
    MaxHeight = 0;
    bc = 0;
    for (Enemy temp : EnemyOptions) {
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
        EnemyOptions[bc] = temp;
        bc += 1;
    }





    Block mouseBlock;
    Item mouseItem;
    Enemy mouseEnemy;
    bool background = false;
    bool secret = false;
    int rotation = 0;

    const int MAX_CHARS = 40;

    Rectangle SelectSong = {WT*2/3+100, 50, WT/3-110, 30};
    char SongName[MAX_CHARS + 1] = "\0";
    char SongNameFinal[MAX_CHARS + 1 + 10];
    std::string bucket = LevelMap.levelTheme;
    bucket = bucket.substr(6,-1);
    strcpy(SongName, bucket.c_str());
    strcpy(SongNameFinal, LevelMap.levelTheme);
    Music LevelTheme = LoadMusicStream(SongNameFinal);
    PlayMusicStream(LevelTheme);
    int SongLetterCount = 0;
    bool SongFocus = false;



    Rectangle NameLevelRect = {WT*2/3+100, 85, WT/3-110, 30};
    char NameLevel[MAX_CHARS + 1] = "\0";
    int NameLetterCount = 0;
    bool NameFocus = false;
    strcpy(NameLevel, LevelMap.name.c_str());



    std::vector<Block> FinishLines;
    std::vector<std::string> FinishLinesDestination;
    std::vector<int> FLDsize;
    int FLFocus = 0;
    int sizeFL = 0;
    Rectangle FinishRect = {WT*2/3+100, 325, WT/3-110, 30};
    FinishLinesDestination = LevelMap.exits;

    std::vector<Block> StartLines;
    std::vector<std::string> StartLinesDestination;
    std::vector<int> SLDsize;
    int SLFocus = 0;
    int sizeSL = 0;
    StartLinesDestination = LevelMap.entrances;


    int in = 0;
    int out = 0;
    for (Block temp : Blocks) {
        if (temp.name == "nextLevel") {
            FinishLines.push_back(temp);
            FLDsize.push_back(FinishLinesDestination[out].size()-1);
            out++;
        }
        if (temp.name == "startLevel") {
            StartLines.push_back(temp);
            SLDsize.push_back(StartLinesDestination[in].size()-1);
            in++;
        }
    }

    int ItemComplexity = 0;
    int EnemyComplexity = 0;

    for (Enemy temp : enemies) {
        EnemyComplexity += complexityCalc(temp);
    }


    for (Item temp : itens) {
        ItemComplexity += complexityCalc(temp);
    }


    int levelTime = seconds;
    int recomendedTime = seconds;
    int finalTime = seconds;
    Rectangle timeRect = {WT*2/3+130, 190+44, WT/3-210, 30};
    char timeSet[MAX_CHARS + 1];
    int timeSize = 0;
    bool timeFocus = false;
    strcpy(timeSet, std::to_string(LevelMap.time).c_str());


    Rectangle PlayTest = {WT*2/3+100, 280, 120, 30};
    bool playTestFocus = false;

    Rectangle SaveFileRect = {WT*2/3+250, 280, 125, 30};
    bool SaveFileFocus = false;



    // int Debug1 = 0;
    // int Debug2 = 0;
    // int Debug3 = 0;
    // int Debug4 = 0;


    while (!WindowShouldClose()) {
        UpdateMusicStream(LevelTheme);

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
        mouseEnemy.rect.x = posM.x;
        mouseEnemy.rect.y = posM.y;

        W = IsKeyDown(KEY_W);
        A = IsKeyDown(KEY_A);
        S = IsKeyDown(KEY_S);
        D = IsKeyDown(KEY_D);
        E = IsKeyPressed(KEY_E);
        R = IsKeyPressed(KEY_R);

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
            if (secret) {
                secret = false;
            } else if (background) {
                background = false;
                secret = true;
            } else {
                secret = false;
                background = true;
            }
        }
        if (R) {
            rotation += 1;
            if (rotation > 3) {
                rotation = 0;
            }
            if (mouseBlock.SCALE != 0) {
                if (mouseBlock.direction == 1 or mouseBlock.direction == 3) {
                    mouseBlock = Block(mouseRect.x, mouseRect.y, mouseBlock.rect.height, mouseBlock.rect.width, mouseBlock.name, SCALE, rotation, background, secret);
                } else {
                    mouseBlock = Block(mouseRect.x, mouseRect.y, mouseBlock.rect.width, mouseBlock.rect.height, mouseBlock.name, SCALE, rotation, background, secret);
                }
            }
        }

        // one = Blocks / two = Itens / Three = Enemies
        if (!timeFocus) {
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
            if (IsKeyPressed(KEY_FOUR)) {
                if (Menu == 4) {
                    Menu = 0;
                } else {
                    Menu = 4;
                }
            }
            if (IsKeyPressed(KEY_ZERO)) {
                Menu = 0;
            }
        }

        // Choose Object
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (mouseRect.x > WT*2/3) {
                if (Menu == 1) {
                    Rectangle temp;
                    for (Block blockOption : BlockOptions) {
                        if (blockOption.name == "platform") {
                            temp = {blockOption.rect.x, blockOption.rect.y, blockOption.rectImage.width*SCALE, blockOption.rectImage.height*SCALE};
                            if (GenericColision(mouseRect, temp)) {
                                mouseBlock = Block(mouseRect.x, mouseRect.y, blockOption.rect.width, blockOption.rect.height, blockOption.name, SCALE, 0, background, secret);
                                blocksLevelTaker.addBlock(mouseBlock);
                                break;
                            }
                        }
                        if (GenericColision(mouseRect, blockOption.rect)) {
                            mouseBlock = Block(mouseRect.x, mouseRect.y, blockOption.rect.width, blockOption.rect.height, blockOption.name, SCALE, 0, background, secret);
                            blocksLevelTaker.addBlock(mouseBlock);
                            break;
                        }
                    }
                } else if (Menu == 2) {
                    for (Item itemOption : ItemOptions) {
                        if (GenericColision(mouseRect, itemOption.rect)) {
                            mouseItem = Item(mouseRect.x, mouseRect.y, itemOption.name, SCALE, itemOption.category);
                            itensLevelTaker.addItem(mouseItem);
                        }
                    }
                } else if (Menu == 3) {
                    for (Enemy enemyOption : EnemyOptions) {
                        if (GenericColision(mouseRect, enemyOption.rect)) {
                            mouseEnemy = Enemy(mouseRect.x, mouseRect.y, enemyOption.name, SCALE, templates, 0);
                        }
                    }
                } else if (Menu == 4) {
                    if (GenericColision(SelectSong, mouseRect)) {
                        SongFocus = true;
                    } else {
                        SongFocus = false;
                    }

                    if (GenericColision(NameLevelRect, mouseRect)) {
                        NameFocus = true;
                    } else {
                        NameFocus = false;
                    }

                    if (GenericColision(timeRect, mouseRect)) {
                        timeFocus = true;
                    } else {
                        timeFocus = false;
                    }

                    if (GenericColision(PlayTest, mouseRect) and StartLines.size() > 0) {
                        std::vector<Item> backupItens = itens;
                        std::vector<Block> backupBlocks = Blocks;
                        std::vector<Enemy> backupEnemies = enemies;

                        
                        Music Musica = LoadMusicStream(SongNameFinal);
                        player->rect.x = StartLines[0].rect.x;
                        player->rect.y = StartLines[0].rect.y-SCALE; // test
                        tick = 1;
                        seconds = finalTime;
                        mainLoop(Musica);
                        UnloadMusicStream(Musica);

                        levelTime = tick/30;
                        recomendedTime = levelTime*2;
                        Blocks = backupBlocks;
                        enemies = backupEnemies;
                        itens = backupItens;
                        tick = 1;
                    }

                    if (GenericColision(SaveFileRect, mouseRect)) {
                        Map finalLevel;
                        finalLevel.Blocks = Blocks;
                        finalLevel.enemies = enemies;
                        finalLevel.itens = itens;
                        finalLevel.name = (std::string) NameLevel;
                        finalLevel.time = finalTime;
                        finalLevel.levelTheme = SongNameFinal;
                        finalLevel.entrances = StartLinesDestination;
                        finalLevel.exits = FinishLinesDestination;
                        loader->SaveLevel(finalLevel);
                        break;
                    }

                    FLFocus = 0;
                    sizeFL = FinishLines.size();
                    int i = 0;
                    for (; i < sizeFL; i++) {
                        Rectangle temp = {FinishRect.x, FinishRect.y+30*i, FinishRect.width, FinishRect.height};
                        if (GenericColision(temp, mouseRect)) {
                            FLFocus = i+1;
                            SLFocus = 0;
                            i++;
                            break;
                        }
                    }

                    SLFocus = 0;
                    sizeSL = StartLines.size();
                    for (int j = 0; j < sizeSL; j++) {
                        Rectangle temp = {FinishRect.x, FinishRect.y+30*i, FinishRect.width, FinishRect.height};
                        if (GenericColision(temp, mouseRect)) {
                            SLFocus = j+1;
                            FLFocus = 0;
                            break;
                        }
                        i++;
                    }
                }
            } else {
                FLFocus = 0;
                SLFocus = 0;
            }
        } else if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
            Rectangle mouseRectTemp = mouseRect;
            mouseRectTemp.x = cx + mouseRect.x - WT/2;
            mouseRectTemp.y = cy + mouseRect.y - HT/2;
            if (Menu == 1) {
                if (mouseBlock.SCALE == 0) {
                    for (int i = 0; i < sizeB; i++) {
                        if (GenericColision(Blocks[i].rect, mouseRectTemp)) {
                            if (Blocks[i].name == "nextLevel") {
                                sizeFL = FinishLines.size();
                                for (int j = 0; j < sizeFL; j++) {
                                    if (Blocks[i].rect.x == FinishLines[j].rect.x and Blocks[i].rect.y == FinishLines[j].rect.y) {
                                        auto it1 = std::next(FinishLines.begin(), j);
                                        auto it2 = std::next(FinishLinesDestination.begin(), j);
                                        auto it3 = std::next(FLDsize.begin(), j);
                                        FinishLines.erase(it1);
                                        FinishLinesDestination.erase(it2);
                                        FLDsize.erase(it3);
                                        break;
                                    }
                                }
                            } else if (Blocks[i].name == "startLevel") {
                                sizeSL = StartLines.size();
                                for (int j = 0; j < sizeSL; j++) {
                                    if (Blocks[i].rect.x == StartLines[j].rect.x and Blocks[i].rect.y == StartLines[j].rect.y) {
                                        auto it1 = std::next(StartLines.begin(), j);
                                        auto it2 = std::next(StartLinesDestination.begin(), j);
                                        auto it3 = std::next(SLDsize.begin(), j);
                                        StartLines.erase(it1);
                                        StartLinesDestination.erase(it2);
                                        SLDsize.erase(it3);
                                        break;
                                    }
                                }
                            }
                            auto it = std::next(Blocks.begin(), i);
                            Blocks.erase(it);
                            sizeB -= 1;
                            break;
                        }
                    }
                } else {
                    mouseBlock.SCALE = 0;
                    rotation = 0;
                }
            } else if (Menu == 2) {
                if (mouseItem.SCALE == 0) {
                    for (int i = 0; i < sizeI; i++) {
                        if (GenericColision(itens[i].rect, mouseRectTemp)) {
                            ItemComplexity -= complexityCalc(itens[i]);
                            auto it = std::next(itens.begin(), i);
                            itens.erase(it);
                            sizeI -= 1;
                            break;
                        }
                    }
                } else {
                    mouseItem.SCALE = 0;
                }
            } else if (Menu == 3) {
                if (mouseEnemy.SCALE == 0) {
                    for (int i = 0; i < sizeE; i++) {
                        if (GenericColision(enemies[i].rect, mouseRectTemp)) {
                            EnemyComplexity -= complexityCalc(enemies[i]);
                            auto it = std::next(enemies.begin(), i);
                            enemies.erase(it);
                            sizeE -= 1;
                            break;
                        }
                    }
                } else {
                    mouseEnemy.SCALE = 0;
                }
            }
        }
        // Remove object



        if (GenericColision(mouseRect, PlayTest)) {
            playTestFocus = true;
        } else {
            playTestFocus = false;
        }

        if (GenericColision(mouseRect, SaveFileRect)) {
            SaveFileFocus = true;
        } else {
            SaveFileFocus = false;
        }

        Block placeBlock;
        Item placeItem;
        Enemy placeEnemy;
        bool placeable = false;

        // Drawing MAP
        BeginDrawing();
        ClearBackground(BLUE);


        Vector2 posGrid = {0, 0}; // Draw Grid and start placing objects
        for (int i = 0; i < BHT+3; i++) {
            for (int j = 0; j < BWT+3; j++) {
                DrawTextureEx(grid, posGrid, 0, SCALE, WHITE);
                if (mouseRect.x <= WT*2/3 and (mouseBlock.SCALE != 0 or mouseItem.SCALE != 0 or mouseEnemy.SCALE != 0)) {
                    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                        Rectangle gridrect = {posGrid.x, posGrid.y, BS, BS};
                        if (GenericColision(gridrect, mouseRect)) {
                            float Bx = cx -WT/2 +posGrid.x;
                            float By = cy -HT/2 +posGrid.y;
                            if (Menu == 1) {
                                if (mouseBlock.direction == 1 or mouseBlock.direction == 3) {
                                    placeBlock = Block(Bx, By, mouseBlock.rect.height, mouseBlock.rect.width, mouseBlock.name, SCALE, mouseBlock.direction, background, secret);
                                } else {
                                    placeBlock = Block(Bx, By, mouseBlock.rect.width, mouseBlock.rect.height, mouseBlock.name, SCALE, mouseBlock.direction, background, secret);
                                }
                            } else if (Menu == 2) {
                                placeItem = Item(Bx, By, mouseItem.name, SCALE, mouseItem.category);
                            } else if (Menu == 3) {
                                placeEnemy = Enemy(Bx, By, mouseEnemy.name, SCALE, templates, 0);
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

        
        // Desenhando Blocos Background
        blocksLevelTaker.DrawBlocks(Blocks, {WT/2, HT/2, 1, 1}, {cx, cy, 1, 1}, SCALE, true, false);
        
        // Colisão Blocos Background
        for (int i = 0; i < sizeB; i++) {
            if (!Blocks[i].background) {
                continue;
            }
            if (Menu == 1 and background) {
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
        }

        // Desenhando inimigos
        for (int i = 0; i < sizeE; i++) {
            if (Menu == 3) {
                if (GenericColision(enemies[i].rect, placeEnemy.rect)) {
                    placeEnemy.rect.x += 2*SCALE;
                    placeEnemy.rect.y += 2*SCALE;
                    if (GenericColision(enemies[i].rect, placeEnemy.rect)) {
                        placeEnemy.rect.x -= 4*SCALE;
                        placeEnemy.rect.y -= 4*SCALE;
                        if (GenericColision(enemies[i].rect, placeEnemy.rect)) {
                            placeable = false;
                        } else {
                            placeEnemy.rect.x += 2*SCALE;
                            placeEnemy.rect.y += 2*SCALE;
                        }
                    } else {
                        placeEnemy.rect.x -= 2*SCALE;
                        placeEnemy.rect.y -= 2*SCALE;
                    }
                }
            }

            relativePos.x = WT/2 +enemies[i].rect.x -cx;
            relativePos.y = HT/2 +enemies[i].rect.y -cy;

            Rectangle source, dest;
            source.x = 0;
            source.y = 0;
            source.width = enemies[i].rectImage.width;
            source.height = enemies[i].rectImage.height;

            dest.x = relativePos.x;
            dest.y = relativePos.y;
            dest.width = enemies[i].rect.width;
            dest.height = enemies[i].rect.height;

            DrawTexturePro(enemies[i].images[0], source, dest, {0, 0}, 0, WHITE);
        }

        // Colisão Blocos Ground
        for (int i = 0; i < sizeB; i++) {
            if (Blocks[i].background) {
                continue;
            }
            if (Menu == 1 and !background) {
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
            } else if (Menu == 3) {
                if (GenericColision(Blocks[i].rect, placeEnemy.rect)) {
                    placeEnemy.rect.x += 2*SCALE;
                    placeEnemy.rect.y += 2*SCALE;
                    if (GenericColision(Blocks[i].rect, placeEnemy.rect)) {
                        placeEnemy.rect.x -= 4*SCALE;
                        placeEnemy.rect.y -= 4*SCALE;
                        if (GenericColision(Blocks[i].rect, placeEnemy.rect)) {
                            placeable = false;
                        } else {
                            placeEnemy.rect.x += 2*SCALE;
                            placeEnemy.rect.y += 2*SCALE;
                        }
                    } else {
                        placeEnemy.rect.x -= 2*SCALE;
                        placeEnemy.rect.y -= 2*SCALE;
                    }
                }
            }
        }

        // Colisão Itens
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
        }
        // Desenhando itens
        itensLevelTaker.DrawItens(itens, {WT/2, HT/2, 1, 1}, {cx, cy, 1, 1}, SCALE);
        // Desenhando Ground
        blocksLevelTaker.DrawBlocks(Blocks, {WT/2, HT/2, 1, 1}, {cx, cy, 1, 1}, SCALE, false, true);




        if (placeable) {
            if (Menu == 1) {
                Blocks.push_back(placeBlock);
                if (placeBlock.name == "nextLevel") {
                    int i = 0;
                    bool sucess = false;
                    for (Block temp : FinishLines) {
                        if (placeBlock.rect.y < temp.rect.y) {
                            FinishLines.insert(FinishLines.begin() + i, placeBlock);
                            FinishLinesDestination.insert(FinishLinesDestination.begin() + i, "Goes to\0");
                            FLDsize.insert(FLDsize.begin() + i, 7);
                            sucess = true;
                            break;
                        }
                        if (placeBlock.rect.y == temp.rect.y) {
                            if (placeBlock.rect.x < temp.rect.x) {
                                FinishLines.insert(FinishLines.begin() + i, placeBlock);
                                FinishLinesDestination.insert(FinishLinesDestination.begin() + i, "Goes to\0");
                                FLDsize.insert(FLDsize.begin() + i, 7);
                                sucess = true;
                                break;
                            }
                        }
                        i++;
                    }
                    if (!sucess) {
                        FinishLines.insert(FinishLines.begin() + i, placeBlock);
                        FinishLinesDestination.insert(FinishLinesDestination.begin() + i, "Goes to\0");
                        FLDsize.insert(FLDsize.begin() + i, 7);
                    }
                } else if (placeBlock.name == "startLevel") {
                    int i = 0;
                    bool sucess = false;
                    player->rect.x = placeBlock.rect.x;
                    player->rect.y = placeBlock.rect.y;
                    for (Block temp : StartLines) {
                        if (placeBlock.rect.y < temp.rect.y) {
                            StartLines.insert(StartLines.begin() + i, placeBlock);
                            StartLinesDestination.insert(StartLinesDestination.begin() + i, "Arrives from\0");
                            SLDsize.insert(SLDsize.begin() + i, 12);
                            sucess = true;
                            break;
                        }
                        if (placeBlock.rect.y == temp.rect.y) {
                            if (placeBlock.rect.x < temp.rect.x) {
                                StartLines.insert(StartLines.begin() + i, placeBlock);
                                StartLinesDestination.insert(StartLinesDestination.begin() + i, "Arrives from\0");
                                SLDsize.insert(SLDsize.begin() + i, 12);
                                sucess = true;
                                break;
                            }
                        }
                        i++;
                    }
                    if (!sucess) {
                        StartLines.insert(StartLines.begin() + i, placeBlock);
                        StartLinesDestination.insert(StartLinesDestination.begin() + i, "Arrives From\0");
                        SLDsize.insert(SLDsize.begin() + i, 12);
                    }
                }
            } else if (Menu == 2) {
                itens.push_back(placeItem);
                ItemComplexity += complexityCalc(placeItem);
            } else if (Menu == 3) {
                placeEnemy.tick += 1;
                enemies.push_back(placeEnemy);
                EnemyComplexity += complexityCalc(placeEnemy);
            }
        }



        // Drawing HUD

        // Gray side-bar
        if (Menu != 0) {
            DrawRectangle(WT*2/3, 0, WT/3, HT, GRAY);
        }

        // Side-Bar Object Options
        if (Menu == 1) {
            blocksOptionsTaker.DrawBlockHud(BlockOptions, SCALE);
        } else if (Menu == 2) {
            itensOptionsTaker.DrawItemHud(ItemOptions, SCALE);
        } else if (Menu == 3) {
            for (Enemy enemyOption : EnemyOptions) {
                Rectangle source, dest;
                source.x = 0;
                source.y = 0;
                source.width = enemyOption.rectImage.width;
                source.height = enemyOption.rectImage.height;

                dest.x = enemyOption.rect.x;
                dest.y = enemyOption.rect.y;
                dest.width = enemyOption.rect.width;
                dest.height = enemyOption.rect.height;

                DrawTexturePro(enemyOption.images[0], source, dest, {0, 0}, 0, WHITE);
            }
        } else if (Menu == 4) {
            DrawText("Select Song: ", SelectSong.x-90, SelectSong.y+5, 15, BLACK);
            DrawRectangle(SelectSong.x-2, SelectSong.y-2, SelectSong.width+4, SelectSong.height+4, BLACK);
            DrawRectangle(SelectSong.x, SelectSong.y, SelectSong.width, SelectSong.height, LIGHTGRAY);
            DrawText(SongName, (int)SelectSong.x + 5, (int)SelectSong.y + 4, 20, MAROON);

            if (SongFocus) {
                int key = GetCharPressed();
                while (key > 0) {
                    if ((key >= 32) && (key <= 125) && (SongLetterCount < MAX_CHARS)) {
                        SongName[SongLetterCount] = (char)key;
                        SongName[SongLetterCount+1] = '\0';
                        SongLetterCount++;
                    }

                    key = GetCharPressed();
                }
                if (IsKeyPressed(KEY_BACKSPACE)) {
                    SongLetterCount--;
                    if (SongLetterCount < 0) {
                        SongLetterCount = 0;
                    }
                    SongName[SongLetterCount] = '\0';
                }
                if (IsKeyPressed(KEY_ENTER)) {
                    UnloadMusicStream(LevelTheme);
                    std::string temp = "assets/audio/songs/" + (std::string)SongName + ".wav";
                    strcpy(SongNameFinal, temp.c_str());
                    LevelTheme = LoadMusicStream(SongNameFinal);
                    PlayMusicStream(LevelTheme);
                }
            }







            DrawText("Level Name: ", NameLevelRect.x-90, NameLevelRect.y+5, 15, BLACK);
            DrawRectangle(NameLevelRect.x-2, NameLevelRect.y-2, NameLevelRect.width+4, NameLevelRect.height+4, BLACK);
            DrawRectangle(NameLevelRect.x, NameLevelRect.y, NameLevelRect.width, NameLevelRect.height, LIGHTGRAY);
            DrawText(NameLevel, (int)NameLevelRect.x + 5, (int)NameLevelRect.y + 4, 20, MAROON);

            if (NameFocus) {
                int key = GetCharPressed();
                while (key > 0) {
                    if ((key >= 32) && (key <= 125) && (NameLetterCount < MAX_CHARS)) {
                        NameLevel[NameLetterCount] = (char)key;
                        NameLevel[NameLetterCount+1] = '\0';
                        NameLetterCount++;
                    }

                    key = GetCharPressed();
                }
                if (IsKeyPressed(KEY_BACKSPACE)) {
                    NameLetterCount--;
                    if (NameLetterCount < 0) {
                        NameLetterCount = 0;
                    }
                    NameLevel[NameLetterCount] = '\0';
                }
            }






            DrawText(TextFormat("Item Complexity: %d", ItemComplexity), (int)NameLevelRect.x - 90, (int)NameLevelRect.y + 4 +35, 20, MAROON);
            DrawText(TextFormat("Enemy Complexity: %d", EnemyComplexity), (int)NameLevelRect.x - 90, (int)NameLevelRect.y + 4 +35*2, 20, MAROON);






            DrawText(TextFormat("Level Time: %d", levelTime), (int)timeRect.x -125, (int)timeRect.y -40, 20, DARKBLUE);
            DrawText(TextFormat("Recomended Time: %d", recomendedTime), (int)timeRect.x -125, (int)timeRect.y -20, 20, DARKBLUE);
            DrawText(TextFormat("Final Time:"), (int)timeRect.x -125, (int)timeRect.y, 20, DARKBLUE);
            DrawRectangle(timeRect.x-2, timeRect.y-2, timeRect.width+4, timeRect.height+4, BLACK);
            DrawRectangle(timeRect.x, timeRect.y, timeRect.width, timeRect.height, LIGHTGRAY);
            DrawText(TextFormat("%d", finalTime), (int)timeRect.x + 5, (int)timeRect.y + 5, 20, DARKBLUE);

            if (timeFocus) {
                int key = GetCharPressed();
                while (key > 0) {
                    if ((key >= 32) && (key <= 125) && (timeSize < MAX_CHARS)) {
                        timeSet[timeSize] = (char)key;
                        timeSet[timeSize+1] = '\0';
                        timeSize++;
                    }

                    key = GetCharPressed();
                }
                if (IsKeyPressed(KEY_BACKSPACE)) {
                    timeSize--;
                    if (timeSize < 0) {
                        timeSize = 0;
                    }
                    timeSet[timeSize] = '\0';
                }
                finalTime = atoi(timeSet);
            }






            
            DrawRectangle(PlayTest.x-2, PlayTest.y-2, PlayTest.width+4, PlayTest.height+4, BLACK);
            if (playTestFocus) {
                DrawRectangle(PlayTest.x, PlayTest.y, PlayTest.width, PlayTest.height, RED);
            } else {
                DrawRectangle(PlayTest.x, PlayTest.y, PlayTest.width, PlayTest.height, GREEN);
            }
            DrawText("Play Test!", (int)PlayTest.x + 5, (int)PlayTest.y + 5, 20, PURPLE);

            
            DrawRectangle(SaveFileRect.x-2, SaveFileRect.y-2, SaveFileRect.width+4, SaveFileRect.height+4, BLACK);
            if (SaveFileFocus) {
                DrawRectangle(SaveFileRect.x, SaveFileRect.y, SaveFileRect.width, SaveFileRect.height, RED);
            } else {
                DrawRectangle(SaveFileRect.x, SaveFileRect.y, SaveFileRect.width, SaveFileRect.height, GREEN);
            }
            DrawText("Save Level!", (int)SaveFileRect.x + 5, (int)SaveFileRect.y + 5, 20, PURPLE);



            sizeFL = FinishLines.size();
            int i = 0;
            for (; i < sizeFL; i++) {
                DrawText(TextFormat("Exit %d: ", i+1), FinishRect.x-90, FinishRect.y+5+i*30, 15, BLACK);
                DrawRectangle(FinishRect.x-2, FinishRect.y-2+i*30, FinishRect.width+4, FinishRect.height+4, BLACK);
                DrawRectangle(FinishRect.x, FinishRect.y+i*30, FinishRect.width, FinishRect.height, LIGHTGRAY);
                char* temp = strdup(FinishLinesDestination[i].c_str());
                DrawText(temp, (int)FinishRect.x + 5, (int)FinishRect.y + 4+i*30, 20, MAROON); // so scarlet, it was... MAROON



                if (FLFocus-1 == i) { // Tive que botar essa parte aqui dentro porque POR ALGUM MOTIVO NÃO FUNCIONA LA EM BAIXO, AAAAAAAAAAAAAAAAAAAA RAIVA
                    int LNCount = FLDsize[FLFocus-1];
                    int key = GetCharPressed();
                    while (key > 0) {
                        if ((key >= 32) && (key <= 125) && (LNCount < MAX_CHARS)) {
                            temp[LNCount] = (char)key;
                            temp[LNCount+1] = '\0';
                            LNCount++;
                        }

                        key = GetCharPressed();
                    }
                    if (IsKeyPressed(KEY_BACKSPACE)) {
                        LNCount--;
                        if (LNCount < 0) {
                            LNCount = 0;
                        }
                        temp[LNCount] = '\0';
                    }
                    FinishLinesDestination[FLFocus-1] = (std::string)temp;
                    FLDsize[FLFocus-1] = LNCount;
                }
            }

            sizeSL = StartLines.size();
            for (int j = 0; j < sizeSL; j++) {
                DrawText(TextFormat("Entrance %d: ", j+1), FinishRect.x-90, FinishRect.y+5+i*30, 15, BLACK);
                DrawRectangle(FinishRect.x-2, FinishRect.y-2+i*30, FinishRect.width+4, FinishRect.height+4, BLACK);
                DrawRectangle(FinishRect.x, FinishRect.y+i*30, FinishRect.width, FinishRect.height, LIGHTGRAY);
                char* temp = strdup(StartLinesDestination[j].c_str());
                // strcpy(temp, StartLinesDestination[i].c_str()); <- essa linha simplesmente parou de funcionar e eu n sei pq...
                DrawText(temp, (int)FinishRect.x + 5, (int)FinishRect.y + 4+i*30, 20, MAROON);



                if (SLFocus-1 == j) {
                    int LNCount = SLDsize[SLFocus-1];
                    int key = GetCharPressed();
                    while (key > 0) {
                        if ((key >= 32) && (key <= 125) && (LNCount < MAX_CHARS)) {
                            temp[LNCount] = (char)key;
                            temp[LNCount+1] = '\0';
                            LNCount++;
                        }
                        key = GetCharPressed();
                    }
                    if (IsKeyPressed(KEY_BACKSPACE)) {
                        LNCount--;
                        if (LNCount < 0) {
                            LNCount = 0;
                        }
                        temp[LNCount] = '\0';
                    }
                    StartLinesDestination[SLFocus-1] = (std::string)temp;
                    SLDsize[SLFocus-1] = LNCount;
                }
                i++;
            }



            // DrawText(TextFormat("Debug Signal 1 = %d: ", Debug1), 50, 50, 25, RED);
            // DrawText(TextFormat("Debug Signal 2 = %d: ", Debug2), 50, 90, 25, RED);
            // DrawText(TextFormat("Debug Signal 3 = %d: ", Debug3), 50, 130, 25, RED);
            // DrawText(TextFormat("Debug Signal 4 = %d: ", Debug4), 50, 170, 25, RED);

            // if (FLFocus > 0) {
            //     int key = GetCharPressed();
            //     char* temp;
            //     strcpy(temp, FinishLinesDestination[FLFocus-1].c_str());
                
            // }
        }


        // Object in Mouse
        if (Menu == 1 and mouseBlock.SCALE != 0) {
            if (background) {
                DrawTextureEx(blocksLevelTaker.images[mouseBlock.id], {mouseBlock.rect.x, mouseBlock.rect.y}, 0, SCALE, GRAY);
            } else {
                DrawTextureEx(blocksLevelTaker.images[mouseBlock.id], {mouseBlock.rect.x, mouseBlock.rect.y}, 0, SCALE, WHITE);
            }
            if (secret) {
                DrawText("S", mouseBlock.rect.x, mouseBlock.rect.y, BS, WHITE);
            }
        } else if (Menu == 2 and mouseItem.SCALE != 0) {
            DrawTextureEx(itensLevelTaker.images[mouseItem.id], {mouseItem.rect.x, mouseItem.rect.y}, 0, SCALE, WHITE);
        } else if (Menu == 3 and mouseEnemy.SCALE != 0) {
            Rectangle source, dest;
            source.x = 0;
            source.y = 0;
            source.width = mouseEnemy.rectImage.width;
            source.height = mouseEnemy.rectImage.height;

            dest.x = mouseEnemy.rect.x;
            dest.y = mouseEnemy.rect.y;
            dest.width = mouseEnemy.rect.width;
            dest.height = mouseEnemy.rect.height;
            DrawTexturePro(mouseEnemy.images[0], source, dest, {0, 0}, 0, WHITE);
        }

        // DrawText(TextFormat("Crab POSITION Y: %02.02f", enemies[0].rect.y), 50, 100, 50, RED);
        EndDrawing();
    }



    UnloadMusicStream(LevelTheme);
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
                    std::string entrance = "";
                    while(level != "") {
                        std::string nextLevel = PlayLevel(level, entrance);
                        entrance = level;
                        level = nextLevel;
                    }
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

std::string Play::PlayLevel(std::string levelname, std::string entrance) {
    Map Level = loader->LoadLevel(levelname);
    if (Level.time == -1) {
        return "";
    }
    Blocks = Level.Blocks;
    itens = Level.itens;
    enemies = Level.enemies;
    seconds = Level.time;
    
    
    int trueEntrance = 0;
    if (entrance != "") {
        for (std::string option : Level.entrances) {
            if (option == entrance) {
                break;
            }
            trueEntrance++;
        }
    }
    for (Block temp : Blocks) {
        if (temp.name == "startLevel") {
            if (trueEntrance == 0) {
                player->rect.x = temp.rect.x+SCALE;
                player->rect.y = temp.rect.y-SCALE;
            } else {
                trueEntrance--;
            }
        } else if (temp.name == "cage") {
            int color = ((int)temp.rect.x+(int)temp.rect.y) % 5;
            player->birdsToSave[color] += 1;
        }

    }


    widthLevel = Level.widthLevel;
    heightLevel = Level.heightLevel;
    RNGWidth = std::uniform_int_distribution<std::mt19937::result_type>(0, widthLevel);
    RNGHeight = std::uniform_int_distribution<std::mt19937::result_type> (0, heightLevel);



    Music LevelTheme = LoadMusicStream(Level.levelTheme);
    int saida = mainLoop(LevelTheme);
    UnloadMusicStream(LevelTheme);

    
    player->birdsToSave[0] = 0;
    player->birdsToSave[1] = 0;
    player->birdsToSave[2] = 0;
    player->birdsToSave[3] = 0;
    player->birdsToSave[4] = 0;

    if (saida == -1) {
        return "";
    }

    std::string nextLevel = Level.exits[saida];

    return nextLevel;
}

int Play::mainLoop(Music LevelTheme) {
    SetTargetFPS(30);
    // SetTargetFPS(2);
    player->vx = 0;
    player->vy = 0;
    // Effect(player->cx, player->cy, 150, 5, {7, 0, 0, 0, 0}, SCALE);
    player->Health(7, 'H');

    

    PlayMusicStream(LevelTheme);
    Vector2 mousePosition;
    tick = 1;
    saida = -1;

    Vector2 relativePos;
    cameraCenter = {WT/2, HT/2, player->rect.width, player->rect.height};
    relativeCameraCenter = {player->rect.x, player->rect.y, player->rect.width/SCALE, player->rect.height/SCALE};
    Rectangle playerDest = {0, 0, player->rect.width, player->rect.height};

    float leftLimit, rightLimit, upperLimit, downLimit;
    leftLimit = 1*BS;
    upperLimit = 0;
    rightLimit = (widthLevel-1)*(BS-SCALE);
    downLimit = (heightLevel)*(BS-SCALE);


    Texture2D birdY = LoadTexture("assets/images/bird-flying-yellow.png");
    Texture2D birdG = LoadTexture("assets/images/bird-flying-green.png");
    Texture2D birdB = LoadTexture("assets/images/bird-flying-blue.png");
    Texture2D birdR = LoadTexture("assets/images/bird-flying-red.png");
    Texture2D birdO = LoadTexture("assets/images/bird-flying-orange.png");

    ItemHandler itemTaker = ItemHandler(itens);
    BlockHandler blockTaker = BlockHandler(Blocks, this);

    while (!WindowShouldClose()) {
        if (fadeout == 0) {
            UpdateMusicStream(LevelTheme);
        }
        sizeB = Blocks.size();
        sizeE = enemies.size();
        sizeD = dusts.size();
        sizeS = effects.size();
        sizeI = itens.size();

        if (fadeout == 0) {

            // Entities Updates
            for (int i = 0; i < sizeE; i++) {
                enemies[i].update(Blocks, player.get(), effects);
            }

            player->update(Blocks, itens, enemies, effects);
            
            if (player->isBoost) {
                float posY = player->rect.y + RNG100(rng)*player->rect.height/100;
                DustBringer(player->cx, posY, {0, 255, 255, 127}, RNG100(rng), false);
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
                if (effects[i].id == 4 and effects[i].tick % 60 == 0) {
                    DustBringer(effects[i].cx, effects[i].cy, BLACK, RNG100(rng), true, "Thank you!");
                }
                if (effects[i].update(Blocks, player.get(), itens, enemies)) {
                    DustBringer(effects[i].cx, effects[i].cy, BLACK, RNG100(rng), true);
                    DustBringer(effects[i].cx, effects[i].cy, BLACK, RNG100(rng), true);
                    DustBringer(effects[i].cx, effects[i].cy, BLACK, RNG100(rng), true);

                    auto it = std::next(effects.begin(), i);
                    effects.erase(it);
                }
            }


            mousePosition = GetMousePosition();
            // Fun-mode
            // if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            //     player->rect.x = mousePosition.x +player->rect.x - cameraCenter.x;
            //     player->rect.y = mousePosition.y +player->rect.y - cameraCenter.y;
            // }

            if (tick % 30 == 0) {
                seconds -= 1;
            }
            if (seconds < 0 and tick % 60 == 0) {
                player->Health(-1, 'H');
            }
        }


        // relative Camera movement
        if (relativeCameraCenter.x > player->rect.x+BS) {
            relativeCameraCenter.x -= 2*(relativeCameraCenter.x - player->rect.x)/BS;
        }
        if (relativeCameraCenter.x < player->rect.x-BS) {
            relativeCameraCenter.x -= 2*(relativeCameraCenter.x - player->rect.x)/BS;
        }
        if (relativeCameraCenter.y > player->rect.y+BS) {
            relativeCameraCenter.y -= 2*(relativeCameraCenter.y - player->rect.y)/BS;
        }
        if (relativeCameraCenter.y < player->rect.y-BS) {
            relativeCameraCenter.y -= 2*(relativeCameraCenter.y - player->rect.y)/BS;
        }


        if (relativeCameraCenter.x + GetScreenWidth()/2 > rightLimit) {
            relativeCameraCenter.x = rightLimit - GetScreenWidth()/2;
        }
        if (relativeCameraCenter.y + GetScreenHeight()/2 > downLimit) {
            relativeCameraCenter.y = downLimit - GetScreenHeight()/2;
        }
        if (relativeCameraCenter.x - GetScreenWidth()/2 < leftLimit) {
            relativeCameraCenter.x = leftLimit + GetScreenWidth()/2;
        }
        if (relativeCameraCenter.y - GetScreenHeight()/2 < upperLimit) {
            relativeCameraCenter.y = upperLimit + GetScreenHeight()/2;
        }

        if (player->rect.x+player->rect.width > rightLimit) {
            player->rect.x = rightLimit-player->rect.width;
        }
        if (player->rect.x < leftLimit) {
            player->rect.x = leftLimit;
        }

        
        bool SwitchGreen = false;
        int cont = 0;
        for (Block& temp : Blocks) {
            if (temp.name == "switch_green") {
                if (temp.parameter > 0) {
                    SwitchGreen = true;
                    temp.parameter = 0;
                    break;
                }
            } else if (temp.name == "energy") {
                temp.parameter -= 1;
                if (temp.parameter <= 0) {
                    auto it = std::next(Blocks.begin(), cont);
                    Blocks.erase(it);
                    sizeB--;
                }
            }
            cont++;
        }
        if (SwitchGreen) {
            for (Block& temp : Blocks) {
                if (temp.name == "green") {
                    temp.background = !temp.background;
                }
            }
        }












        // Desenhando coisas
        BeginDrawing();
        ClearBackground(BLUE);




        // Desenhando blocos Background
        blockTaker.DrawBlocks(Blocks, cameraCenter, relativeCameraCenter, SCALE, true, false);



        // Desenhando Player
        Color playerColor = WHITE;
        if (player->gameover) {
            playerColor = {0, 255, 255, 127};
        }
        // invincibility for damage
        if (player->invincibility['H'] > 0 and player->tick % 10 <= 1) {
            playerColor = {255, 255, 0, 255};
        } else if (player->invincibility['R'] > 0 and player->tick % 10 <= 3) {
            playerColor = GREEN;
        } else if (player->invincibility['P'] > 0 and player->tick % 10 <= 5) {
            playerColor = BLUE;
        } else if (player->invincibility['C'] > 0 and player->tick % 10 <= 7) {
            playerColor = RED;
        } else if (player->invincibility['W'] > 0 and player->tick % 10 <= 9) {
            playerColor = {255, 255, 0, 255};
        }


        playerDest.x = cameraCenter.x +player->rect.x -relativeCameraCenter.x;
        playerDest.y = cameraCenter.y +player->rect.y -relativeCameraCenter.y;
        playerDest.width = player->rect.width;
        playerDest.height = player->rect.height;
        if (player->lookingRight) {
            DrawTexturePro(player->images[player->imageCount], {0.0f, 0.0f, player->rectImage.width, player->rectImage.height}, playerDest, {0, 0}, 0, playerColor);
        } else {
            DrawTexturePro(player->images[player->imageCount], {0.0f, 0.0f, -player->rectImage.width, player->rectImage.height}, playerDest, {0, 0}, 0, playerColor);
        }



        // Desenhando inimigos
        for (int i = 0; i < sizeE; i++) {
            Rectangle source, dest;

            relativePos.x = cameraCenter.x +enemies[i].rect.x -relativeCameraCenter.x;
            relativePos.y = cameraCenter.y +enemies[i].rect.y -relativeCameraCenter.y;

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
                    source.x += enemies[i].rectImage.width+1;
                }
                DrawTexturePro(enemies[i].images[0], source, dest, {0, 0}, 0, WHITE);
            } else {
                DrawRectangle(relativePos.x, relativePos.y, enemies[i].rect.width, enemies[i].rect.height, BLACK);
            }
        }

        // Desenhando itens
        itemTaker.DrawItens(itens, cameraCenter, relativeCameraCenter, SCALE);

        // Desenhando blocos Ground
        blockTaker.DrawBlocks(Blocks, cameraCenter, relativeCameraCenter, SCALE, false, false);

        // Desenhando Efeitos
        for (int i = 0; i < sizeS; i++) {
            Effect temp = effects[i];
            Rectangle source, dest;

            relativePos.x = cameraCenter.x +temp.rect.x -relativeCameraCenter.x;
            relativePos.y = cameraCenter.y +temp.rect.y -relativeCameraCenter.y;

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

            relativePos.x = cameraCenter.x +D.pos.x -relativeCameraCenter.x;
            relativePos.y = cameraCenter.y +D.pos.y -relativeCameraCenter.y;
            if (D.dialog == "") {
                DrawCircle(relativePos.x, relativePos.y, (D.timer/20)+SCALE, {0, 0, 0, 127});
                DrawCircle(relativePos.x, relativePos.y, (D.timer/20), D.cor);
            } else {
                DrawText(D.dialog.c_str(), relativePos.x, relativePos.y, D.timer/3, D.cor);
            }
        }








        // fun-mode
        // if (tick % 30 == 0 and sizeI < 200) {
        //     int RNG_X = (RNGWidth(rng))*(BS-SCALE);
        //     int RNG_Y = (RNGHeight(rng)-1)*(BS-SCALE);
        //     bool freespace = true;
        //     Rectangle tempItem = {(float) RNG_X, (float) RNG_Y, 13, 13};
        //     for (int i = 0; i < sizeB; i++) {
        //         Block temp = Blocks[i];
        //         if (GenericColision(tempItem, temp.rect)) {
        //             int value = RNGe3(rng);
        //             if (value <= 1) {
        //                 enemies.push_back(Enemy(RNG_X, RNG_Y, "snail", SCALE, Blocks, RNG100(rng), temp));
        //             } else if (value <= 5) {
        //                 bool spawnable;
        //                 for(int j = 0; j < sizeB; j++) {
        //                     Block tempCeil = Blocks[j];
        //                     if (tempCeil.rect.x+tempCeil.rect.width > temp.rect.x and tempCeil.rect.x < temp.rect.x+temp.rect.width) {
        //                         if (tempCeil.rect.y+tempCeil.rect.height > temp.rect.y and tempCeil.rect.y < temp.rect.y) {
        //                             spawnable = false;
        //                             break;
        //                         }
        //                     }
        //                 }
        //                 if (spawnable) {
        //                     enemies.push_back(Enemy(RNG_X, RNG_Y, "crab", SCALE, Blocks, RNG100(rng), temp));
        //                 }
        //             }
        //             freespace = false;
        //             break;
        //         }
        //     }
        //     if (freespace) {
        //         int value = RNGe3(rng);
        //         if (value <= 1) {
        //             itens.push_back(Item(RNG_X, RNG_Y, "Pshard-eloise", SCALE, 'P'));
        //         } else if (value <= 4) {
        //             itens.push_back(Item(RNG_X, RNG_Y, "Pshard-hard", SCALE, 'P'));
        //         } else if (value <= 8) {
        //             itens.push_back(Item(RNG_X, RNG_Y, "Pshard-fun", SCALE, 'P'));
        //         } else if (value <= 13) {
        //             itens.push_back(Item(RNG_X, RNG_Y, "Pshard-party", SCALE, 'P'));
        //         } else if (value <= 19) {
        //             itens.push_back(Item(RNG_X, RNG_Y, "Pshard-wind", SCALE, 'P'));
        //         } else if (value <= 28) {
        //             itens.push_back(Item(RNG_X, RNG_Y, "Hshard-wisdom", SCALE, 'H'));
        //         } else if (value <= 38) {
        //             itens.push_back(Item(RNG_X, RNG_Y, "Hshard-courage", SCALE, 'H'));
        //         } else if (value <= 50) {
        //             itens.push_back(Item(RNG_X, RNG_Y, "Hshard-power", SCALE, 'H'));
        //         } else if (value <= 64) {
        //             itens.push_back(Item(RNG_X, RNG_Y, "Hshard-resilience", SCALE, 'H'));
        //         } else if (value <= 80) {
        //             itens.push_back(Item(RNG_X, RNG_Y, "Hshard-hope", SCALE, 'H'));
        //         } else if (value <= 82) {
        //             itens.push_back(Item(RNG_X, RNG_Y, "courage-potion", SCALE, 'I'));
        //         } else if (value <= 90) {
        //             itens.push_back(Item(RNG_X, RNG_Y, "coin-gold", SCALE, 'C'));
        //         } else if (value <= 130) {
        //             itens.push_back(Item(RNG_X, RNG_Y, "coin-silver", SCALE, 'C'));
        //         } else if (value <= 200) {
        //             itens.push_back(Item(RNG_X, RNG_Y, "coin-copper", SCALE, 'C'));
        //         } else if (value <= 280) {
        //             itens.push_back(Item(RNG_X, RNG_Y, "food-orange", SCALE, 'F'));
        //         } else if (value <= 370) {
        //             itens.push_back(Item(RNG_X, RNG_Y, "food-pepper", SCALE, 'F'));
        //         } else if (value <= 540) {
        //             itens.push_back(Item(RNG_X, RNG_Y, "food-blueberry", SCALE, 'F'));
        //         } else if (value <= 680) {
        //             itens.push_back(Item(RNG_X, RNG_Y, "food-pear", SCALE, 'F'));
        //         } else if (value <= 997) {
        //             itens.push_back(Item(RNG_X, RNG_Y, "food-banana", SCALE, 'F'));
        //         } else if (value <= 998) {
        //             enemies.push_back(Enemy(RNG_X, RNG_Y, "bee", SCALE, Blocks, RNG100(rng)));
        //         } else if (value <= 999) {
        //             enemies.push_back(Enemy(RNG_X, RNG_Y, "butterfly", SCALE, Blocks, RNG100(rng)));
        //         } else if (value <= 1000) {
        //             enemies.push_back(Enemy(RNG_X, RNG_Y, "meldrop", SCALE, Blocks, RNG100(rng)));
        //         } else {
        //             itens.push_back(Item(RNG_X, RNG_Y, "key-hope", SCALE, 'K'));
        //         }
        //         sizeI += 1;
        //     }
        // }









        // Desenhando HUD
        DesenharHeart();
        DesenharPearl();
        DrawText(TextFormat("Score: %d", player->score), GetScreenWidth()/2-100, 30, 20, WHITE);
        DrawText(TextFormat("Time: %d", seconds), GetScreenWidth()/2-100, 0, 20, WHITE);
        if (player->keyHope > 0) {
            DrawText(TextFormat("Yellow Keys: %d", player->keyHope), GetScreenWidth() - 300, 50, 20, WHITE);
        }
        if (player->keyResilience > 0) {
            DrawText(TextFormat("Green Keys: %d", player->keyResilience), GetScreenWidth() - 300, 70, 20, WHITE);
        }
        if (player->keyPower > 0) {
            DrawText(TextFormat("Blue Keys: %d", player->keyPower), GetScreenWidth() - 300, 90, 20, WHITE);
        }
        if (player->keyCourage > 0) {
            DrawText(TextFormat("Red Keys: %d", player->keyCourage), GetScreenWidth() - 300, 110, 20, WHITE);
        }
        if (player->keyWisdom > 0) {
            DrawText(TextFormat("Orange Keys: %d", player->keyWisdom), GetScreenWidth() - 300, 130, 20, WHITE);
        }
        // DrawText(TextFormat("itens no mapa: %d", itens.size()), GetScreenWidth()-300, 220, 20, WHITE);
        if (player->powers[0]) {
            DrawTextureEx(player->P1image, {(float) GetScreenWidth()/2+20*SCALE, 20}, 0, SCALE, WHITE);
            DrawText("1", (float) GetScreenWidth()/2+27*SCALE, 20+15*SCALE, 20, BLACK);
        }
        if (player->powers[1]) {
            DrawTextureEx(player->P2image, {(float) GetScreenWidth()/2+40*SCALE, 20}, 0, SCALE, WHITE);
            DrawText("2", (float) GetScreenWidth()/2+47*SCALE, 20+15*SCALE, 20, BLACK);
        }
        if (player->powers[2]) {
            DrawTextureEx(player->P3image, {(float) GetScreenWidth()/2+60*SCALE, 20}, 0, SCALE, WHITE);
            DrawText("3", (float) GetScreenWidth()/2+67*SCALE, 20+15*SCALE, 20, BLACK);
        }
        if (player->powers[3]) {
            DrawTextureEx(player->P4image, {(float) GetScreenWidth()/2+80*SCALE, 20}, 0, SCALE, WHITE);
            DrawText("4", (float) GetScreenWidth()/2+87*SCALE, 20+15*SCALE, 20, BLACK);
        }
        if (player->powers[4]) {
            DrawTextureEx(player->P5image, {(float) GetScreenWidth()/2+100*SCALE, 20}, 0, SCALE, WHITE);
            DrawText("5", (float) GetScreenWidth()/2+107*SCALE, 20+15*SCALE, 20, BLACK);
        }
        // Birds
        int birds1 = player->birdsToSave[0];
        int birds2 = player->birdsToSave[1];
        int birds3 = player->birdsToSave[2];
        int birds4 = player->birdsToSave[3];
        int birds5 = player->birdsToSave[4];
        Rectangle origin = {0, 0, 13, 13};
        Rectangle dest = {10, (float)GetScreenHeight()-36, 26, 26};
        while (birds1+birds2+birds3+birds4+birds5 > 0) {
            if (birds1 > 0) {
                DrawTexturePro(birdY, origin, dest, {0, 0}, 0, WHITE);
                dest.x += 28;
                birds1--;
            }
            if (birds2 > 0) {
                DrawTexturePro(birdG, origin, dest, {0, 0}, 0, WHITE);
                dest.x += 28;
                birds2--;
            }
            if (birds3 > 0) {
                DrawTexturePro(birdB, origin, dest, {0, 0}, 0, WHITE);
                dest.x += 28;
                birds3--;
            }
            if (birds4 > 0) {
                DrawTexturePro(birdR, origin, dest, {0, 0}, 0, WHITE);
                dest.x += 28;
                birds4--;
            }
            if (birds5 > 0) {
                DrawTexturePro(birdO, origin, dest, {0, 0}, 0, WHITE);
                dest.x += 28;
                birds5--;
            }
        }




        // DrawRectangle(cameraCenter.x, cameraCenter.y, relativeCameraCenter.width, relativeCameraCenter.height, {255, 255, 255, 127});


        // DrawText(TextFormat("Limite do mapa X: %02.02f", rightLimit), GetScreenWidth()/2-100, 220, 20, RED);
        // DrawText(TextFormat("Mouse X: %02.02f", -cameraCenter.x +mousePosition.x +relativeCameraCenter.x), GetScreenWidth()/2-100, 260, 20, RED);
        // DrawText(TextFormat("Limite da camera esquerda: %02.02f", relativeCameraCenter.x - GetScreenWidth()/2), GetScreenWidth()/2-100, 290, 20, RED);
        // DrawText(TextFormat("Limite da camera direita: %02.02f", relativeCameraCenter.x + GetScreenWidth()/2), GetScreenWidth()/2-100, 320, 20, RED);
        // DrawText(TextFormat("Limite do mapa: %d", widthLevel), GetScreenWidth()/2, 270, 20, RED);
        // DrawText(TextFormat("Camera position: %02.02f", relativeCameraCenter.x), GetScreenWidth()/2, 270, 20, RED);

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


        if (fadeout > 0) {
            // Maybe change to loop so it can have that sweet Happyland Adventures vibe.
            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), {0, 0, 0, (unsigned char)fadeout});
            fadeout += 1;
            if (fadeout >= 180) {
                break;
            }
        }


        if (DEBUG) {
            relativePos.x = WT/2 +player->groundBlock.rect.x -relativeCameraCenter.x;
            relativePos.y = HT/2 +player->groundBlock.rect.y -relativeCameraCenter.y;
            DrawRectangle(relativePos.x, relativePos.y, player->groundBlock.rect.width, player->groundBlock.rect.height, YELLOW);

            
            DrawText(TextFormat("X=%02.02f, Y=%02.02f, W=%02.02f, H=%02.02f", player->groundBlock.rect.x, player->groundBlock.rect.y, player->groundBlock.rect.width, player->groundBlock.rect.height), GetScreenWidth()/2 - 200, 100, 30, WHITE);
            if (player->crouch) {
                relativePos.x = cameraCenter.x +player->HitboxA.x -relativeCameraCenter.x;
                relativePos.y = cameraCenter.y +player->HitboxA.y -relativeCameraCenter.y;
                DrawRectangle(relativePos.x, relativePos.y, player->HitboxA.width, player->HitboxA.height, RED);
            } else {
                relativePos.x = cameraCenter.x +player->Hitbox1.x -relativeCameraCenter.x;
                relativePos.y = cameraCenter.y +player->Hitbox1.y -relativeCameraCenter.y;
                DrawRectangle(relativePos.x, relativePos.y, player->Hitbox1.width, player->Hitbox1.height, RED);
                relativePos.x = cameraCenter.x +player->Hitbox2.x -relativeCameraCenter.x;
                relativePos.y = cameraCenter.y +player->Hitbox2.y -relativeCameraCenter.y;
                DrawRectangle(relativePos.x, relativePos.y, player->Hitbox2.width, player->Hitbox2.height, RED);
                relativePos.x = cameraCenter.x +player->Hitbox3.x -relativeCameraCenter.x;
                relativePos.y = cameraCenter.y +player->Hitbox3.y -relativeCameraCenter.y;
                DrawRectangle(relativePos.x, relativePos.y, player->Hitbox3.width, player->Hitbox3.height, RED);
            }
            relativePos.x = cameraCenter.x +player->HB1.x -relativeCameraCenter.x;
            relativePos.y = cameraCenter.y +player->HB1.y -relativeCameraCenter.y;
            DrawRectangle(relativePos.x, relativePos.y, player->HB1.width, player->HB1.height, DARKBLUE);

            relativePos.x = cameraCenter.x +player->cx -relativeCameraCenter.x;
            relativePos.y = cameraCenter.y +player->cy -relativeCameraCenter.y;
            DrawCircle(relativePos.x, relativePos.y, 5, PURPLE);


            int sizeCB = player->CBs.size();
            for (int i = 0; i < sizeCB; i++) {
                Block temp = Blocks[player->CBs[i]];
                relativePos.x = cameraCenter.x +temp.rect.x -relativeCameraCenter.x;
                relativePos.y = cameraCenter.y +temp.rect.y -relativeCameraCenter.y;
                DrawRectangle(relativePos.x, relativePos.y, temp.rect.width, temp.rect.height, GRAY);
            }
            for (int i = 0; i < sizeE; i++) {
                // relativePos.x = cameraCenter.x +enemies[i].rect.x -relativeCameraCenter.x;
                // relativePos.y = cameraCenter.y +enemies[i].rect.y -relativeCameraCenter.y;
                // DrawRectangle(relativePos.x, relativePos.y, enemies[i].rect.width, enemies[i].rect.height, RED);
                if (enemies[i].name == "crab") {
                    relativePos.x = cameraCenter.x +enemies[i].patrol1 -relativeCameraCenter.x;
                    relativePos.y = cameraCenter.y +enemies[i].ground.rect.y -relativeCameraCenter.y;
                    DrawCircle(relativePos.x, relativePos.y, 5, YELLOW);
                    relativePos.x = cameraCenter.x +enemies[i].patrol2 -relativeCameraCenter.x;
                    relativePos.y = cameraCenter.y +enemies[i].ground.rect.y -relativeCameraCenter.y;
                    DrawCircle(relativePos.x, relativePos.y, 5, YELLOW);
                    relativePos.x = cameraCenter.x +enemies[i].ground.rect.x -relativeCameraCenter.x;
                    relativePos.y = cameraCenter.y +enemies[i].ground.rect.y -relativeCameraCenter.y;
                    DrawRectangle(relativePos.x, relativePos.y, enemies[i].ground.rect.width, enemies[i].ground.rect.height, YELLOW);
                    relativePos.x = cameraCenter.x +enemies[i].border1.rect.x -relativeCameraCenter.x;
                    relativePos.y = cameraCenter.y +enemies[i].border1.rect.y -relativeCameraCenter.y;
                    DrawRectangle(relativePos.x, relativePos.y, enemies[i].border1.rect.width, enemies[i].border1.rect.height, GREEN);
                    relativePos.x = cameraCenter.x +enemies[i].border2.rect.x -relativeCameraCenter.x;
                    relativePos.y = cameraCenter.y +enemies[i].border2.rect.y -relativeCameraCenter.y;
                    DrawRectangle(relativePos.x, relativePos.y, enemies[i].border2.rect.width, enemies[i].border2.rect.height, GREEN);
                } else if (enemies[i].name == "butterfly") {
                    relativePos.x = cameraCenter.x +enemies[i].orbit.x -relativeCameraCenter.x;
                    relativePos.y = cameraCenter.y +enemies[i].orbit.y -relativeCameraCenter.y;
                    DrawCircle(relativePos.x, relativePos.y, 5, YELLOW);
                } else if (enemies[i].name == "snail") {
                    relativePos.x = cameraCenter.x +enemies[i].vision.x -relativeCameraCenter.x;
                    relativePos.y = cameraCenter.y +enemies[i].vision.y -relativeCameraCenter.y;
                    DrawRectangle(relativePos.x, relativePos.y, enemies[i].vision.width, enemies[i].vision.height, BLACK);
                    relativePos.x = cameraCenter.x +enemies[i].HBFeet.x -relativeCameraCenter.x;
                    relativePos.y = cameraCenter.y +enemies[i].HBFeet.y -relativeCameraCenter.y;
                    DrawRectangle(relativePos.x, relativePos.y, enemies[i].HBFeet.width, enemies[i].HBFeet.height, BLACK);
                    if (enemies[i].ground.SCALE == 0) {
                        DrawText("UNEXPECTED SNAIL BEHAVIOR 2", GetScreenWidth() - 520, 40, 20, RED);
                    } else {
                        relativePos.x = cameraCenter.x +enemies[i].ground.rect.x -relativeCameraCenter.x;
                        relativePos.y = cameraCenter.y +enemies[i].ground.rect.y -relativeCameraCenter.y;
                        DrawRectangle(relativePos.x, relativePos.y, enemies[i].ground.rect.width, enemies[i].ground.rect.height, YELLOW);
                    }
                } else if (enemies[i].name == "bee") {
                    relativePos.x = cameraCenter.x +enemies[i].patrol1 -relativeCameraCenter.x;
                    relativePos.y = cameraCenter.y +enemies[i].rect.y -relativeCameraCenter.y;
                    DrawCircle(relativePos.x, relativePos.y, 5, YELLOW);
                    relativePos.x = cameraCenter.x +enemies[i].patrol2 -relativeCameraCenter.x;
                    relativePos.y = cameraCenter.y +enemies[i].rect.y -relativeCameraCenter.y;
                    DrawCircle(relativePos.x, relativePos.y, 5, YELLOW);
                }
                relativePos.x = cameraCenter.x +enemies[i].cx -relativeCameraCenter.x;
                relativePos.y = cameraCenter.y +enemies[i].cy -relativeCameraCenter.y;
                DrawCircle(relativePos.x, relativePos.y, 5, YELLOW);
            }
            for (int i = 0; i < sizeI; i++) {
                relativePos.x = cameraCenter.x +itens[i].rect.x -relativeCameraCenter.x;
                relativePos.y = cameraCenter.y +itens[i].rect.y -relativeCameraCenter.y;
                DrawRectangle(relativePos.x, relativePos.y, itens[i].rect.width, itens[i].rect.height, YELLOW);
                
                int sizeCI = player->CIs.size();
                relativePos.x = cameraCenter.x +itens[i].cx -relativeCameraCenter.x;
                relativePos.y = cameraCenter.y +itens[i].cy -relativeCameraCenter.y;
                DrawCircle(relativePos.x, relativePos.y, 5, GREEN);
                for (int j = 0; j < sizeCI; j++) {
                    if (player->CIs[j] == i) {
                        DrawCircle(relativePos.x, relativePos.y, 5, GRAY);
                    }
                }
            }
        }

        EndDrawing();
        tick++;
    }
    fadeout = 0;
    // SetTargetFPS(30);

    UnloadTexture(birdY);
    UnloadTexture(birdG);
    UnloadTexture(birdB);
    UnloadTexture(birdR);
    UnloadTexture(birdO);


    tick -= 180;
    if (saida == -1) {
        return -1;
    }

    if (seconds > 0) {
        player->Health(seconds/10, 'W');
    }

    int trueSaida = 0;
    for (int i = 0; i < sizeB; i++) {
        if (Blocks[i].name == "nextLevel") {
            if (i == saida) {
                break;
            }
            trueSaida += 1;
        }
    }

    return trueSaida;
}

void Play::DesenharHeart() {
    Rectangle PHud = {10.0f, 10.0f, 11.0f*SCALE, 11.0f*SCALE};
    // Hope
    int HHTemp = player->HH/7;
    int HHPart = player->HH % 7;
    int HHEmptyTemp = (player->MHH - player->HH)/7;
    while (HHTemp > 0) {
        DrawTexturePro(player->HeartGrid, {0.0f, 0.0f, 11.0f, 11.0f}, PHud, {0, 0}, 0, WHITE);
        PHud.x += 12*SCALE;
        HHTemp--;
    }
    if (HHPart > 0) {
        DrawTexturePro(player->HeartGrid, {(12.0f*(7-HHPart)), 0.0f, 11.0f, 11.0f}, PHud, {0, 0}, 0, WHITE);
        PHud.x += 12*SCALE;
    }
    while (HHEmptyTemp > 0) {
        DrawTexturePro(player->HeartGrid, {12.0f*7, 0.0f, 11.0f, 11.0f}, PHud, {0, 0}, 0, WHITE);
        PHud.x += 12*SCALE;
        HHEmptyTemp--;
    }
    if (player->PHH > 0) {
        DrawText(TextFormat("+%d", player->PHH), PHud.x, PHud.y, 35, YELLOW);
    }

    PHud.x = 10.0f;
    PHud.y += 12.0f*SCALE;



    // Resilience
    int RHTemp = player->RH/7;
    int RHPart = player->RH % 7;
    int RHEmptyTemp = (player->MRH - player->RH)/7;
    while (RHTemp > 0) {
        DrawTexturePro(player->HeartGrid, {0.0f, 12.0f, 11.0f, 11.0f}, PHud, {0, 0}, 0, WHITE);
        PHud.x += 12*SCALE;
        RHTemp--;
    }
    if (RHPart > 0) {
        DrawTexturePro(player->HeartGrid, {(12.0f*(7-RHPart)), 12.0f, 11.0f, 11.0f}, PHud, {0, 0}, 0, WHITE);
        PHud.x += 12*SCALE;
    }
    while (RHEmptyTemp > 0) {
        DrawTexturePro(player->HeartGrid, {12.0f*7, 12.0f, 11.0f, 11.0f}, PHud, {0, 0}, 0, WHITE);
        PHud.x += 12*SCALE;
        RHEmptyTemp--;
    }
    if (player->PRH > 0) {
        DrawText(TextFormat("+%d", player->PRH), PHud.x, PHud.y, 35, GREEN);
    }

    PHud.x = 10.0f;
    PHud.y += 12.0f*SCALE;



    // Power
    int PHTemp = player->PH/7;
    int PHPart = player->PH % 7;
    int PHEmptyTemp = (player->MPH - player->PH)/7;
    while (PHTemp > 0) {
        DrawTexturePro(player->HeartGrid, {0.0f, 12.0f*2, 11.0f, 11.0f}, PHud, {0, 0}, 0, WHITE);
        PHud.x += 12*SCALE;
        PHTemp--;
    }
    if (PHPart > 0) {
        DrawTexturePro(player->HeartGrid, {(12.0f*(7-PHPart)), 12.0f*2, 11.0f, 11.0f}, PHud, {0, 0}, 0, WHITE);
        PHud.x += 12*SCALE;
    }
    while (PHEmptyTemp > 0) {
        DrawTexturePro(player->HeartGrid, {12.0f*7, 12.0f*2, 11.0f, 11.0f}, PHud, {0, 0}, 0, WHITE);
        PHud.x += 12*SCALE;
        PHEmptyTemp--;
    }
    if (player->PPH > 0) {
        DrawText(TextFormat("+%d", player->PPH), PHud.x, PHud.y, 35, DARKBLUE);
    }

    PHud.x = 10.0f;
    PHud.y += 12.0f*SCALE;



    // Courage
    int CHTemp = player->CH/7;
    int CHPart = player->CH % 7;
    int CHEmptyTemp = (player->MCH - player->CH)/7;
    while (CHTemp > 0) {
        DrawTexturePro(player->HeartGrid, {0.0f, 12.0f*3, 11.0f, 11.0f}, PHud, {0, 0}, 0, WHITE);
        PHud.x += 12*SCALE;
        CHTemp--;
    }
    if (CHPart > 0) {
        DrawTexturePro(player->HeartGrid, {(12.0f*(7-CHPart)), 12.0f*3, 11.0f, 11.0f}, PHud, {0, 0}, 0, WHITE);
        PHud.x += 12*SCALE;
    }
    while (CHEmptyTemp > 0) {
        DrawTexturePro(player->HeartGrid, {12.0f*7, 12.0f*3, 11.0f, 11.0f}, PHud, {0, 0}, 0, WHITE);
        PHud.x += 12*SCALE;
        CHEmptyTemp--;
    }
    if (player->PCH > 0) {
        DrawText(TextFormat("+%d", player->PCH), PHud.x, PHud.y, 35, RED);
    }

    PHud.x = 10.0f;
    PHud.y += 12.0f*SCALE;



    // Wisdom
    int WHTemp = player->WH/7;
    int WHPart = player->WH % 7;
    int WHEmptyTemp = (player->MWH - player->WH)/7;
    while (WHTemp > 0) {
        DrawTexturePro(player->HeartGrid, {0.0f, 12.0f*4, 11.0f, 11.0f}, PHud, {0, 0}, 0, WHITE);
        PHud.x += 12*SCALE;
        WHTemp--;
    }
    if (WHPart > 0) {
        DrawTexturePro(player->HeartGrid, {(12.0f*(7-WHPart)), 12.0f*4, 11.0f, 11.0f}, PHud, {0, 0}, 0, WHITE);
        PHud.x += 12*SCALE;
    }
    while (WHEmptyTemp > 0) {
        DrawTexturePro(player->HeartGrid, {12.0f*7, 12.0f*4, 11.0f, 11.0f}, PHud, {0, 0}, 0, WHITE);
        PHud.x += 12*SCALE;
        WHEmptyTemp--;
    }
    if (player->PWH > 0) {
        DrawText(TextFormat("+%d", player->PWH), PHud.x, PHud.y, 35, ORANGE);
    }
}

void Play::DesenharPearl() {
        Rectangle PHud = {GetScreenWidth() - 20.0f*SCALE, 10.0f, 11.0f*SCALE, 11.0f*SCALE};
        // Wind
        int WPTemp = player->WP/7;
        int WPPart = player->WP % 7;
        int WPEmptyTemp = (player->MWP - player->WP)/7;
        while (WPTemp > 0) {
            DrawTexturePro(player->PearlGrid, {0.0f, 0.0f, 11.0f, 11.0f}, PHud, {0, 0}, 0, WHITE);
            PHud.x -= 12*SCALE;
            WPTemp--;
        }
        if (WPPart > 0) {
            DrawTexturePro(player->PearlGrid, {(12.0f*(7-WPPart)), 0.0f, -11.0f, 11.0f}, PHud, {0, 0}, 0, WHITE);
            PHud.x -= 12*SCALE;
        }
        while (WPEmptyTemp > 0) {
            DrawTexturePro(player->PearlGrid, {12.0f*7, 0.0f, 11.0f, 11.0f}, PHud, {0, 0}, 0, WHITE);
            PHud.x -= 12*SCALE;
            WPEmptyTemp--;
        }
        if (player->PWP > 0) {
            DrawText(TextFormat("%d+", player->PWP), PHud.x, PHud.y, 35, {223, 245, 0, 255});
        }

        PHud.x = GetScreenWidth() - 20.0f*SCALE;
        PHud.y += 12.0f*SCALE;



        // Party
        int PPTemp = player->PP/7;
        int PPPart = player->PP % 7;
        int PPEmptyTemp = (player->MPP - player->PP)/7;
        while (PPTemp > 0) {
            DrawTexturePro(player->PearlGrid, {0.0f, 12.0f, 11.0f, 11.0f}, PHud, {0, 0}, 0, WHITE);
            PHud.x -= 12*SCALE;
            PPTemp--;
        }
        if (PPPart > 0) {
            DrawTexturePro(player->PearlGrid, {(12.0f*(7-PPPart)), 12.0f, -11.0f, 11.0f}, PHud, {0, 0}, 0, WHITE);
            PHud.x -= 12*SCALE;
        }
        while (PPEmptyTemp > 0) {
            DrawTexturePro(player->PearlGrid, {12.0f*7, 12.0f, 11.0f, 11.0f}, PHud, {0, 0}, 0, WHITE);
            PHud.x -= 12*SCALE;
            PPEmptyTemp--;
        }
        if (player->PPP > 0) {
            DrawText(TextFormat("%d+", player->PPP), PHud.x, PHud.y, 35, {133, 255, 0, 255});
        }

        PHud.x = GetScreenWidth() - 20.0f*SCALE;
        PHud.y += 12.0f*SCALE;



        // Fun
        int FPTemp = player->FP/7;
        int FPPart = player->FP % 7;
        int FPEmptyTemp = (player->MFP - player->FP)/7;
        while (FPTemp > 0) {
            DrawTexturePro(player->PearlGrid, {0.0f, 12.0f*2, 11.0f, 11.0f}, PHud, {0, 0}, 0, WHITE);
            PHud.x -= 12*SCALE;
            FPTemp--;
        }
        if (FPPart > 0) {
            DrawTexturePro(player->PearlGrid, {(12.0f*(7-FPPart)), 12.0f*2, -11.0f, 11.0f}, PHud, {0, 0}, 0, WHITE);
            PHud.x -= 12*SCALE;
        }
        while (FPEmptyTemp > 0) {
            DrawTexturePro(player->PearlGrid, {12.0f*7, 12.0f*2, 11.0f, 11.0f}, PHud, {0, 0}, 0, WHITE);
            PHud.x -= 12*SCALE;
            FPEmptyTemp--;
        }
        if (player->PFP > 0) {
            DrawText(TextFormat("%d+", player->PFP), PHud.x, PHud.y, 35, {30, 235, 210, 255});
        }

        PHud.x = GetScreenWidth() - 20.0f*SCALE;
        PHud.y += 12.0f*SCALE;



        // Hard
        int HPTemp = player->HP/7;
        int HPPart = player->HP % 7;
        int HPEmptyTemp = (player->MHP - player->HP)/7;
        while (HPTemp > 0) {
            DrawTexturePro(player->PearlGrid, {0.0f, 12.0f*3, 11.0f, 11.0f}, PHud, {0, 0}, 0, WHITE);
            PHud.x -= 12*SCALE;
            HPTemp--;
        }
        if (HPPart > 0) {
            DrawTexturePro(player->PearlGrid, {(12.0f*(7-HPPart)), 12.0f*3, -11.0f, 11.0f}, PHud, {0, 0}, 0, WHITE);
            PHud.x -= 12*SCALE;
        }
        while (HPEmptyTemp > 0) {
            DrawTexturePro(player->PearlGrid, {12.0f*7, 12.0f*3, 11.0f, 11.0f}, PHud, {0, 0}, 0, WHITE);
            PHud.x -= 12*SCALE;
            HPEmptyTemp--;
        }
        if (player->PHP > 0) {
            DrawText(TextFormat("%d+", player->PHP), PHud.x, PHud.y, 35, {253, 105, 150, 255});
        }

        PHud.x = GetScreenWidth() - 20.0f*SCALE;
        PHud.y += 12.0f*SCALE;



        // Eloise
        int EPTemp = player->EP/7;
        int EPPart = player->EP % 7;
        int EPEmptyTemp = (player->MEP - player->EP)/7;
        while (EPTemp > 0) {
            DrawTexturePro(player->PearlGrid, {0.0f, 12.0f*4, 11.0f, 11.0f}, PHud, {0, 0}, 0, WHITE);
            PHud.x -= 12*SCALE;
            EPTemp--;
        }
        if (EPPart > 0) {
            DrawTexturePro(player->PearlGrid, {(12.0f*(7-EPPart)), 12.0f*4, 11.0f, 11.0f}, PHud, {0, 0}, 0, WHITE);
            PHud.x -= 12*SCALE;
        }
        while (EPEmptyTemp > 0) {
            DrawTexturePro(player->PearlGrid, {12.0f*7, 12.0f*4, 11.0f, 11.0f}, PHud, {0, 0}, 0, WHITE);
            PHud.x -= 12*SCALE;
            EPEmptyTemp--;
        }
        if (player->PEP > 0) {
            DrawText(TextFormat("%d+", player->PEP), PHud.x, PHud.y, 35, {255, 150, 150, 255});
        }
    }

void Play::DesenharBlocos(bool background, bool showSecret) {
    int sizeB = Blocks.size();
    Vector2 relativePos;
    for (int i = 0; i < sizeB; i++) {
        Block temp = Blocks[i];
        if (temp.background != background) {
            continue;
        }
        if (Blocks[i].name == "nextLevel" and fadeout == 0) {
            if (GenericColision(player->rect, Blocks[i].rect)) {
                fadeout = 1;
                saida = i;
                PlaySound(finish);
            }
        }

        relativePos.x = WT/2 +temp.rect.x -relativeCameraCenter.x;
        relativePos.y = HT/2 +temp.rect.y -relativeCameraCenter.y;
        if (temp.direction != 0) {
            if (temp.direction == 1) {
                relativePos.y += temp.rect.height;
            } else if (temp.direction == 2) {
                relativePos.x += temp.rect.width;
                relativePos.y += temp.rect.height;
            } else if (temp.direction == 3) {
                relativePos.x += temp.rect.width;
            }
        }

        Color transparency;
        if (temp.background) {
            transparency = GRAY;
        } else {
            transparency = WHITE;
        }

        if (temp.name == "cage") {
            Rectangle source, dest;
            if ((tick+(int)temp.rect.x+(int)temp.rect.y) % 20 < 10) {
                source.x = 12;
            } else {
                source.x = 0;
            }
            source.y = 0;
            source.width = temp.rectImage.width;
            source.height = temp.rectImage.height;

            dest.x = relativePos.x;
            dest.y = relativePos.y;
            dest.width = temp.rect.width;
            dest.height = temp.rect.height;

            DrawTexturePro(temp.image, source, dest, {0, 0}, temp.direction*-90, transparency);
        } else {
            DrawTextureEx(temp.image, relativePos, temp.direction*-90, SCALE, transparency);
        }
    }
}





