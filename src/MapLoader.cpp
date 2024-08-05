#include "../header/MapLoader.hpp"



MapLoader::MapLoader(int SCALER, int BSer, float width, float height) {
    SCALE = SCALER;
    BS = BSer;
    WT = BS*width;
    HT = BS*height;
}

MapLoader::MapLoader() {}

Map MapLoader::LoadFile(std::string name) {
    std::ifstream level("levels/teste.txt");
    if (!level) {
        level.close();
        Map Error;
        Error.playerX = -1;
        Error.playerY = -1;
        return Error;
    }

    std::string line;
    std::string previousLine;
    int CHL; // Current Height Level (AKA. what column of blocks we are currently looking during the Blocks load)
    int widthLevel;
    int heightLevel;
    std::getline(level, line);
    heightLevel = std::stoi(line);
    std::getline(level, line);
    widthLevel = std::stoi(line);

    float playerX;
    float playerY;

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> RNG100(0, 100);

    int RenderPhase = 0; // 1 = Blocks; 2 = Itens; 3 = Enemies;
    
    Blocks.clear();
    itens.clear();
    enemies.clear();
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
                    playerX = CWL*(BS-SCALE);
                    playerY = CHL*(BS-SCALE);
                    continue;
                }
                Block tile;
                if (line[CWL] == 'G') {
                    tile = Block(CWL*(BS-SCALE), CHL*(BS-SCALE), BS, BS, "grass", SCALE);
                } else if (line[CWL] == 'D') {
                    if (line[CWL+1] == '2') {
                        tile = Block(CWL*(BS-SCALE), CHL*(BS-SCALE), BS*2-SCALE, BS*2-SCALE, "dirt2", SCALE);
                        CWL++;
                    } else {
                        tile = Block(CWL*(BS-SCALE), CHL*(BS-SCALE), BS, BS, "dirt", SCALE);
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
                    tile = Block(CWL*(BS-SCALE), CHL*(BS-SCALE), BS, BS*2-SCALE, "gate-" + type, SCALE, rotation);
                } else if (line[CWL] == 'P') {
                    if (line[CWL+1] == 'p') {
                        tile = Block(CWL*(BS-SCALE), CHL*(BS-SCALE), BS*2-SCALE, BS, "platform", SCALE, 0);
                    } else {
                        tile = Block(CWL*(BS-SCALE), CHL*(BS-SCALE), BS, BS*2-SCALE, "platform", SCALE, 90);
                    }
                } else if (line[CWL] == 'A') {
                    tile = Block(CWL*(BS-SCALE), CHL*(BS-SCALE), BS, BS, "altar", SCALE);
                } else if (line[CWL] == 'S') {
                    int orientation = 0;
                    if (line[CWL-1] == 'S' or line[CWL+1] == 'S') {
                        if (previousLine[CWL] != '-' and previousLine[CWL] != 'S') {
                            orientation = 2;
                        }
                    }
                    if (line[CWL-1] != 'S' and line[CWL+1] != 'S') {
                        if (line[CWL-1] != '-') {
                            orientation = 3;
                        } else if (line[CWL+1] != '-') {
                            orientation = 1;
                        } else if (previousLine[CWL] != '-' and previousLine[CWL] != 'S') {
                            orientation = 2;
                        }
                    }
                    tile = Block(CWL*(BS-SCALE), CHL*(BS-SCALE), BS, BS, "spike", SCALE, orientation);
                }
                Blocks.push_back(tile);
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
                    } else if (text == "power") {
                        category = 'S';
                    }
                }
                text += line[i];
            }
            name = text;

            Item novoItem(CHL*(BS-SCALE), CWL*(BS-SCALE), name, SCALE, category);
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

            Block ground;
            if (name == "snail" or name == "crab") {
                int sizeB = Blocks.size();
                for (int j = 0; j < sizeB; j++) {
                    ground = Blocks[j];
                    if (ground.rect.x == (float)(CHL)*(BS-SCALE) and ground.rect.y == (float)CWL*(BS-SCALE)) {
                        break;
                    }
                }
            }
            if (name == "snail") {
                enemies.push_back(Enemy((CHL-1)*(BS-SCALE), CWL*(BS-SCALE), name, SCALE, Blocks, RNG100(rng), ground));
            } else if (name == "butterfly") {
                enemies.push_back(Enemy(CHL*(BS-SCALE), CWL*(BS-SCALE), name, SCALE, Blocks, RNG100(rng)));
            } else if (name == "crab") {
                enemies.push_back(Enemy(CHL*(BS-SCALE), (CWL-1)*(BS-SCALE), name, SCALE, Blocks, RNG100(rng), ground));
            } else if (name == "meldrop") {
                enemies.push_back(Enemy(CHL*(BS-SCALE), CWL*(BS-SCALE), name, SCALE, Blocks, RNG100(rng)));
            } else {
                enemies.push_back(Enemy(CHL*(BS-SCALE), CWL*(BS-SCALE), name, SCALE, Blocks, RNG100(rng)));
            }
        }
    }
    
    level.close();

    Map Level;
    Level.Blocks = Blocks;
    Level.itens = itens;
    Level.enemies = enemies;
    Level.widthLevel = widthLevel;
    Level.heightLevel = heightLevel;
    Level.playerX = playerX;
    Level.playerY = playerY;
    return Level;
}

