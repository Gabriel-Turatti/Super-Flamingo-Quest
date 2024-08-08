#include "../header/MapLoader.hpp"



MapLoader::MapLoader(int SCALER, int BSer, float width, float height) {
    SCALE = SCALER;
    BS = BSer;
    WT = BS*width;
    HT = BS*height;
}

MapLoader::MapLoader() {}

Map MapLoader::LoadFile(std::string name) {
    std::ifstream level("levels/"+name);
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
                    tile = Block(CWL*(BS-SCALE), CHL*(BS-SCALE), BS, BS*2-SCALE, "gate-" + type, SCALE, rotation, false);
                } else if (line[CWL] == 'P') {
                    if (line[CWL+1] == 'p') {
                        tile = Block(CWL*(BS-SCALE), CHL*(BS-SCALE), BS*2-SCALE, BS, "platform", SCALE, 0, false);
                    } else {
                        tile = Block(CWL*(BS-SCALE), CHL*(BS-SCALE), BS, BS*2-SCALE, "platform", SCALE, 90, false);
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
                    tile = Block(CWL*(BS-SCALE), CHL*(BS-SCALE), BS, BS, "spike", SCALE, orientation, false);
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

void MapLoader::SaveLevel(Map level) {
    Block leftMostBlock;
    Block upMostBlock;
    Block rightMostBlock;
    Block downMostBlock;

    for (Block temp : level.Blocks) {
        if (leftMostBlock.SCALE == 0 or temp.rect.x < leftMostBlock.rect.x) {
            leftMostBlock = temp;
        }
        if (upMostBlock.SCALE == 0 or temp.rect.y < upMostBlock.rect.y) {
            upMostBlock = temp;
        }
        if (rightMostBlock.SCALE == 0 or temp.rect.x > rightMostBlock.rect.x) {
            rightMostBlock = temp;
        }
        if (downMostBlock.SCALE == 0 or temp.rect.y > downMostBlock.rect.y) {
            downMostBlock = temp;
        }
    }

    level.widthLevel = (int) (rightMostBlock.rect.x - leftMostBlock.rect.x)/BS;
    level.heightLevel = (int) (upMostBlock.rect.y - downMostBlock.rect.y)/BS;

    int lineOffset = leftMostBlock.rect.x/BS;
    int columnOffset = upMostBlock.rect.y/BS;

    std::map<int, std::map<int, Block>> NewBlocksGround;
    std::map<int, std::map<int, Block>> NewBlocksBackground;
    std::map<int, std::map<int, Item>> NewItens;

    for (Block temp : level.Blocks) {
        int LinePos = (int) (temp.rect.y/BS) - lineOffset;
        int ColumnPos = (int) (temp.rect.x/BS) - columnOffset;
        if (temp.background) {
            NewBlocksBackground[LinePos][ColumnPos] = temp;
        } else {
            NewBlocksGround[LinePos][ColumnPos] = temp;
        }
    }


    for (Item temp : level.itens) {
        std::string name = temp.name;
         if (name == "coin-copper") {
            temp.rect.x -= 2*SCALE;
            temp.rect.y -= 1*SCALE;
        } else if (name == "coin-silver") {
            temp.rect.x -= 2*SCALE;
            temp.rect.y -= 1*SCALE;
        } else if (name == "coin-gold") {
            temp.rect.x -= 2*SCALE;
            temp.rect.y -= 1*SCALE;
        } else if (name == "coin-death") {
            temp.rect.x -= 0*SCALE;
            temp.rect.y -= 0*SCALE;
        } else if (name == "food-banana") {
            temp.rect.x -= 1*SCALE;
            temp.rect.y -= 1*SCALE;
        } else if (name == "food-pear") {
            temp.rect.x += 0*SCALE;
            temp.rect.y += 0*SCALE;
        } else if (name == "food-blueberry") {
            temp.rect.x -= 2*SCALE;
            temp.rect.y -= 1*SCALE;
        } else if (name == "food-pepper") {
            temp.rect.x -= 1*SCALE;
            temp.rect.y -= 1*SCALE;
        } else if (name == "food-orange") {
            temp.rect.x -= 1*SCALE;
            temp.rect.y -= 0*SCALE;
        } else if (name == "Hshard-hope") {
            temp.rect.x -= 3*SCALE;
            temp.rect.y -= 2*SCALE;
        } else if (name == "Hshard-resilience") {
            temp.rect.x -= 3*SCALE;
            temp.rect.y -= 2*SCALE;
        } else if (name == "Hshard-power") {
            temp.rect.x -= 3*SCALE;
            temp.rect.y -= 2*SCALE;
        } else if (name == "Hshard-courage") {
            temp.rect.x -= 3*SCALE;
            temp.rect.y -= 2*SCALE;
        } else if (name == "Hshard-wisdom") {
            temp.rect.x -= 3*SCALE;
            temp.rect.y -= 2*SCALE;
        } else if (name == "Pshard-wind") {
            temp.rect.x -= 2.5*SCALE;
            temp.rect.y -= 2.5*SCALE;
        } else if (name == "Pshard-party") {
            temp.rect.x -= 2.5*SCALE;
            temp.rect.y -= 2.5*SCALE;
        } else if (name == "Pshard-fun") {
            temp.rect.x -= 2.5*SCALE;
            temp.rect.y -= 2.5*SCALE;
        } else if (name == "Pshard-hard") {
            temp.rect.x -= 2.5*SCALE;
            temp.rect.y -= 2.5*SCALE;
        } else if (name == "Pshard-eloise") {
            temp.rect.x -= 2.5*SCALE;
            temp.rect.y -= 2.5*SCALE;
        } else if (name == "key-hope") {
            temp.rect.x -= 3*SCALE;
            temp.rect.y -= 1*SCALE;
        } else if (name == "key-resilience") {
            temp.rect.x -= 3*SCALE;
            temp.rect.y -= 1*SCALE;
        } else if (name == "key-power") {
            temp.rect.x -= 3*SCALE;
            temp.rect.y -= 1*SCALE;
        } else if (name == "key-courage") {
            temp.rect.x -= 2*SCALE;
            temp.rect.y -= 1*SCALE;
        } else if (name == "key-wisdom") {
            temp.rect.x -= 3*SCALE;
            temp.rect.y -= 1*SCALE;
        } else if (name == "courage-potion") {
            temp.rect.x -= 2*SCALE;
            temp.rect.y -= 1*SCALE;
        } else if (name == "party-potion") {
            temp.rect.x -= 2*SCALE;
            temp.rect.y -= 1*SCALE;
        } else if (name == "power-dash") {
            temp.rect.x += 1*SCALE;
            temp.rect.y += 1*SCALE;
        } else if (name == "power-transmutation") {
            temp.rect.x += 1*SCALE;
            temp.rect.y += 1*SCALE;
        } else if (name == "power-boost") {
            temp.rect.x += 1*SCALE;
            temp.rect.y += 1*SCALE;
        } else if (name == "power-spear") {
            temp.rect.x += 1*SCALE;
            temp.rect.y += 1*SCALE;
        }

        int LinePos = (int) (temp.rect.y/BS) - lineOffset;
        int ColumnPos = (int) (temp.rect.x/BS) - columnOffset;
        NewItens[LinePos][ColumnPos] = temp;
    }



    std::ofstream LevelSave("levels/"+level.name);
    if (LevelSave.is_open()) {
        std::string emptyLine('-', level.widthLevel);

        LevelSave << std::to_string(level.heightLevel) << '\n';
        LevelSave << std::to_string(level.widthLevel) << '\n';
        LevelSave << level.levelTheme << '\n';
        LevelSave << std::to_string(level.time) << '\n';

        for (std::string exit : level.exits) {
            LevelSave << "S-" +exit+"\n"; 
        }
        for (std::string entrance : level.entrances) {
            LevelSave << "E-" +entrance+"\n"; 
        }



        LevelSave << "P1\n";
        for (int i = 0; i < level.heightLevel; i++) {
            if (NewBlocksGround.count(i) == 0) {
                LevelSave << emptyLine;
                continue;
            }
            for (int j = 0; j < level.widthLevel; j++) {
                if (NewBlocksGround[i].count(j) > 0) {
                    if (NewBlocksGround[i][j].name == "grass") {
                        LevelSave << 'G';
                    } else if (NewBlocksGround[i][j].name == "dirt") {
                        LevelSave << 'D';
                    } else if (NewBlocksGround[i][j].name == "dirt2") {
                        LevelSave << "D2";
                        j++;
                    } else if (NewBlocksGround[i][j].name == "brick") {
                        LevelSave << 'B';
                    } else if (NewBlocksGround[i][j].name == "gate-hope") {
                        LevelSave << "(Kh" + std::to_string(NewBlocksGround[i][j].direction) + ")";
                    } else if (NewBlocksGround[i][j].name == "gate-resilience") {
                        LevelSave << "(Kr" + std::to_string(NewBlocksGround[i][j].direction) + ")";
                    } else if (NewBlocksGround[i][j].name == "gate-power") {
                        LevelSave << "(Kp" + std::to_string(NewBlocksGround[i][j].direction) + ")";
                    } else if (NewBlocksGround[i][j].name == "gate-courage") {
                        LevelSave << "(Kc" + std::to_string(NewBlocksGround[i][j].direction) + ")";
                    } else if (NewBlocksGround[i][j].name == "gate-wisdom") {
                        LevelSave << "(Kw" + std::to_string(NewBlocksGround[i][j].direction) + ")";
                    } else if (NewBlocksGround[i][j].name == "platform") {
                        LevelSave << "Pp";
                        j++;
                    } else if (NewBlocksGround[i][j].name == "spike") {
                        LevelSave << "(S" + std::to_string(NewBlocksGround[i][j].direction) + ")";
                    } else if (NewBlocksGround[i][j].name == "altar") {
                        LevelSave << "A";
                    } else if (NewBlocksGround[i][j].name == "nextLevel") {
                        LevelSave << "N";
                    } else if (NewBlocksGround[i][j].name == "startLevel") {
                        LevelSave << "F";
                    }
                } else {
                    LevelSave << '-';
                }
            }
            LevelSave << '\n';
        }



        
        
        LevelSave << "P2\n";
        for (int i = 0; i < level.heightLevel; i++) {
            if (NewBlocksBackground.count(i) == 0) {
                LevelSave << emptyLine;
                continue;
            }
            for (int j = 0; j < level.widthLevel; j++) {
                if (NewBlocksBackground[i].count(j) > 0) {
                    if (NewBlocksBackground[i][j].name == "grass") {
                        LevelSave << 'G';
                    } else if (NewBlocksBackground[i][j].name == "dirt") {
                        LevelSave << 'D';
                    } else if (NewBlocksBackground[i][j].name == "dirt2") {
                        LevelSave << "D2";
                        j++;
                    } else if (NewBlocksBackground[i][j].name == "brick") {
                        LevelSave << 'B';
                    } else if (NewBlocksBackground[i][j].name == "gate-hope") {
                        LevelSave << "(Kh" + std::to_string(NewBlocksBackground[i][j].direction) + ")";
                    } else if (NewBlocksBackground[i][j].name == "gate-resilience") {
                        LevelSave << "(Kr" + std::to_string(NewBlocksBackground[i][j].direction) + ")";
                    } else if (NewBlocksBackground[i][j].name == "gate-power") {
                        LevelSave << "(Kp" + std::to_string(NewBlocksBackground[i][j].direction) + ")";
                    } else if (NewBlocksBackground[i][j].name == "gate-courage") {
                        LevelSave << "(Kc" + std::to_string(NewBlocksBackground[i][j].direction) + ")";
                    } else if (NewBlocksBackground[i][j].name == "gate-wisdom") {
                        LevelSave << "(Kw" + std::to_string(NewBlocksBackground[i][j].direction) + ")";
                    } else if (NewBlocksBackground[i][j].name == "platform") {
                        LevelSave << "Pp";
                        j++;
                    } else if (NewBlocksBackground[i][j].name == "spike") {
                        LevelSave << "(S" + std::to_string(NewBlocksBackground[i][j].direction) + ")";
                    } else if (NewBlocksBackground[i][j].name == "altar") {
                        LevelSave << "A";
                    } else if (NewBlocksBackground[i][j].name == "nextLevel") {
                        LevelSave << "N";
                    } else if (NewBlocksBackground[i][j].name == "startLevel") {
                        LevelSave << "F";
                    }
                } else {
                    LevelSave << '-';
                }
            }
            LevelSave << '\n';
        }




        LevelSave << "P3\n";
        for (int i = 0; i < level.heightLevel; i++) {
            if (NewItens.count(i) == 0) {
                LevelSave << emptyLine;
                continue;
            }
            for (int j = 0; j < level.widthLevel; j++) {
                if (NewItens[i].count(j) > 0) {
                    if (NewItens[i][j].name == "coin-copper") {
                        LevelSave << "(Cc)";
                    } else if (NewItens[i][j].name == "coin-silver") {
                        LevelSave << "(Cp)";
                    } else if (NewItens[i][j].name == "coin-gold") {
                        LevelSave << "(Cg)";
                    } else if (NewItens[i][j].name == "coin-death") {
                        LevelSave << "(Cd)";


                    } else if (NewItens[i][j].name == "food-banana") {
                        LevelSave << "(Fh)";
                    } else if (NewItens[i][j].name == "food-pear") {
                        LevelSave << "(Fr)";
                    } else if (NewItens[i][j].name == "food-blueberry") {
                        LevelSave << "(Fp)";
                    } else if (NewItens[i][j].name == "food-pepper") {
                        LevelSave << "(Fc)";
                    } else if (NewItens[i][j].name == "food-orange") {
                        LevelSave << "(Fw)";


                    } else if (NewItens[i][j].name == "Hshard-hope") {
                        LevelSave << "(Hh)";
                    } else if (NewItens[i][j].name == "Hshard-resilience") {
                        LevelSave << "(Hr)";
                    } else if (NewItens[i][j].name == "Hshard-power") {
                        LevelSave << "(Hp)";
                    } else if (NewItens[i][j].name == "Hshard-courage") {
                        LevelSave << "(Hc)";
                    } else if (NewItens[i][j].name == "Hshard-wisdom") {
                        LevelSave << "(Hw)";


                    } else if (NewItens[i][j].name == "key-hope") {
                        LevelSave << "(Kh)";
                    } else if (NewItens[i][j].name == "key-resilience") {
                        LevelSave << "(Kr)";
                    } else if (NewItens[i][j].name == "key-power") {
                        LevelSave << "(Kp)";
                    } else if (NewItens[i][j].name == "key-courage") {
                        LevelSave << "(Kc)";
                    } else if (NewItens[i][j].name == "key-wisdom") {
                        LevelSave << "(Kw)";


                    } else if (NewItens[i][j].name == "Pshard-wind") {
                        LevelSave << "(Pw)";
                    } else if (NewItens[i][j].name == "Pshard-party") {
                        LevelSave << "(Pp)";
                    } else if (NewItens[i][j].name == "Pshard-fun") {
                        LevelSave << "(Pf)";
                    } else if (NewItens[i][j].name == "Pshard-hard") {
                        LevelSave << "(Ph)";
                    } else if (NewItens[i][j].name == "Pshard-eloise") {
                        LevelSave << "(Pe)";


                    } else if (NewItens[i][j].name == "power-dash") {
                        LevelSave << "(Sw)";
                    } else if (NewItens[i][j].name == "power-???") {
                        LevelSave << "(Sp)";
                    } else if (NewItens[i][j].name == "power-boost") {
                        LevelSave << "(Sf)";
                    } else if (NewItens[i][j].name == "power-spear") {
                        LevelSave << "(Sh)";
                    } else if (NewItens[i][j].name == "power-transmutation") {
                        LevelSave << "(Se)";


                    } else if (NewItens[i][j].name == "courage-potion") {
                        LevelSave << 'C';
                    } else if (NewItens[i][j].name == "party-potion") {
                        LevelSave << 'P';
                    }
                } else {
                    LevelSave << '-';
                }
            }
            LevelSave << '\n';
        }




        LevelSave << "P4\n";
        for (Enemy temp : level.enemies) {
            int columnPos = temp.rect.x/BS;
            int linePos = temp.rect.y/BS;
            if (temp.name == "snail") {
                columnPos += 1;
            } else if (temp.name == "crab") {
                linePos += 1;
            }
            LevelSave << std::to_string(columnPos) << '-' << std::to_string(linePos) << '-' << '\"' << temp.name << "\"\n";
        }



        LevelSave << "endmap";
    }


    LevelSave.close();
}

void MapLoader::SaveFlamingo(Flamingo player) {
    std::ofstream FlamFile("saves/Flamingo1/player.txt");

    FlamFile << player.MHH << '-' << player.MRH << '-' << player.MPH << '-' << player.MCH << '-' << player.MWH << '\n';
    FlamFile << player.HH << '-' << player.RH << '-' << player.PH << '-' << player.CH << '-' << player.WH << '\n';
    FlamFile << player.MWP << '-' << player.MPP << '-' << player.MFP << '-' << player.MHP << '-' << player.MEP << '\n';
    FlamFile << player.WP << '-' << player.PP << '-' << player.FP << '-' << player.HP << '-' << player.EP << '\n';
    FlamFile << player.powers[0] << player.powers[1] << player.powers[2] << player.powers[3] << player.powers[4] << '\n';

}

Flamingo MapLoader::LoadFlamingo() {
    std::ifstream FlamFile("saves/Flamingo1/player.txt");
    std::string line;

    Flamingo player;

    std::getline(FlamFile, line);
    int i = 0;
    std::string value = "";
    int questCount = 0;
    while(line[i] != '\n') {
        if (line[i] != '-') {
            value += line[i];
        } else {
            switch(questCount) {
                case 0:
                    player.MHH = std::stoi(value);
                    break;
                case 1:
                    player.MRH = std::stoi(value);
                    break;
                case 2:
                    player.MPH = std::stoi(value);
                    break;
                case 3:
                    player.MCH = std::stoi(value);
                    break;
                case 4:
                    player.MWH = std::stoi(value);
                    break;
            }
            value = "";
            questCount += 1;
        }
    }


    std::getline(FlamFile, line);
    i = 0;
    value = "";
    questCount = 0;
    while(line[i] != '\n') {
        if (line[i] != '-') {
            value += line[i];
        } else {
            switch(questCount) {
                case 0:
                    player.HH = std::stoi(value);
                    break;
                case 1:
                    player.RH = std::stoi(value);
                    break;
                case 2:
                    player.PH = std::stoi(value);
                    break;
                case 3:
                    player.CH = std::stoi(value);
                    break;
                case 4:
                    player.WH = std::stoi(value);
                    break;
            }
            value = "";
            questCount += 1;
        }
    }
    

    std::getline(FlamFile, line);
    i = 0;
    value = "";
    questCount = 0;
    while(line[i] != '\n') {
        if (line[i] != '-') {
            value += line[i];
        } else {
            switch(questCount) {
                case 0:
                    player.MWP = std::stoi(value);
                    break;
                case 1:
                    player.MPP = std::stoi(value);
                    break;
                case 2:
                    player.MFP = std::stoi(value);
                    break;
                case 3:
                    player.MHP = std::stoi(value);
                    break;
                case 4:
                    player.MEP = std::stoi(value);
                    break;
            }
            value = "";
            questCount += 1;
        }
    }


    std::getline(FlamFile, line);
    i = 0;
    value = "";
    questCount = 0;
    while(line[i] != '\n') {
        if (line[i] != '-') {
            value += line[i];
        } else {
            switch(questCount) {
                case 0:
                    player.WP = std::stoi(value);
                    break;
                case 1:
                    player.PP = std::stoi(value);
                    break;
                case 2:
                    player.FP = std::stoi(value);
                    break;
                case 3:
                    player.HP = std::stoi(value);
                    break;
                case 4:
                    player.EP = std::stoi(value);
                    break;
            }
            value = "";
            questCount += 1;
        }
    }
    
    


    std::getline(FlamFile, line);
    i = 0;
    while (i !='\n') {
        if (line[i] == '0') {
            player.powers[i] = false;
        } else {
            player.powers[i] = true;
        }
    }


    return player;
}

Map MapLoader::LoadLevel(std::string name) {
    std::ifstream level("levels/"+name);
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

    std::getline(level, line);
    char* LevelTheme = strdup(line.c_str());

    std::getline(level, line);
    int timeLimit = std::stoi(line);

    std::getline(level, line);
    std::vector<std::string> exits;
    while (line[0] == 'S') {
        line = line.substr(2, line.size() - 1);
        exits.push_back(line);
        std::getline(level, line);
    }
    std::vector<std::string> entrances;
    while (line[0] == 'E') {
        line = line.substr(2, line.size() - 1);
        entrances.push_back(line);
        std::getline(level, line);
    }

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> RNG100(0, 100);



    // to-do Below

    int RenderPhase = 0; // 1 = Blocks Ground; 2 = Blocks Background; 3 = Itens; 4 = Enemies;
    
    // Blocks.clear();
    // itens.clear();
    // enemies.clear();
    // while (!level.eof()) {
    //     std::getline(level, line);
    //     if (line == "endmap") {
    //         break;
    //     }
    //     if (line[0] == 'P') {
    //         CHL = 0;
    //         RenderPhase += 1;
    //         continue;
    //     }
    //     if (RenderPhase == 1) {
    //         for (int CWL = 0; CWL < widthLevel; CWL++) { // Current Width Level
    //             if (line[CWL] == '-' or line[CWL] == '|' or line[CWL] == 'p' or line[CWL] == 'h') {
    //                 continue;
    //             }
    //             if (line[CWL] == 'F') {
    //                 playerX = CWL*(BS-SCALE);
    //                 playerY = CHL*(BS-SCALE);
    //                 continue;
    //             }
    //             Block tile;
    //             if (line[CWL] == 'G') {
    //                 tile = Block(CWL*(BS-SCALE), CHL*(BS-SCALE), BS, BS, "grass", SCALE);
    //             } else if (line[CWL] == 'D') {
    //                 if (line[CWL+1] == '2') {
    //                     tile = Block(CWL*(BS-SCALE), CHL*(BS-SCALE), BS*2-SCALE, BS*2-SCALE, "dirt2", SCALE);
    //                     CWL++;
    //                 } else {
    //                     tile = Block(CWL*(BS-SCALE), CHL*(BS-SCALE), BS, BS, "dirt", SCALE);
    //                 }
    //             } else if (line[CWL] == 'K') {
    //                 bool rotation = false;
    //                 std::string type;
    //                 if (line[CWL-1] == '|') {
    //                     rotation = true;
    //                 }
    //                 if (line[CWL+1] == 'h') {
    //                     type = "hope";
    //                 }
    //                 tile = Block(CWL*(BS-SCALE), CHL*(BS-SCALE), BS, BS*2-SCALE, "gate-" + type, SCALE, rotation, false);
    //             } else if (line[CWL] == 'P') {
    //                 if (line[CWL+1] == 'p') {
    //                     tile = Block(CWL*(BS-SCALE), CHL*(BS-SCALE), BS*2-SCALE, BS, "platform", SCALE, 0, false);
    //                 } else {
    //                     tile = Block(CWL*(BS-SCALE), CHL*(BS-SCALE), BS, BS*2-SCALE, "platform", SCALE, 90, false);
    //                 }
    //             } else if (line[CWL] == 'A') {
    //                 tile = Block(CWL*(BS-SCALE), CHL*(BS-SCALE), BS, BS, "altar", SCALE);
    //             } else if (line[CWL] == 'S') {
    //                 int orientation = 0;
    //                 if (line[CWL-1] == 'S' or line[CWL+1] == 'S') {
    //                     if (previousLine[CWL] != '-' and previousLine[CWL] != 'S') {
    //                         orientation = 2;
    //                     }
    //                 }
    //                 if (line[CWL-1] != 'S' and line[CWL+1] != 'S') {
    //                     if (line[CWL-1] != '-') {
    //                         orientation = 3;
    //                     } else if (line[CWL+1] != '-') {
    //                         orientation = 1;
    //                     } else if (previousLine[CWL] != '-' and previousLine[CWL] != 'S') {
    //                         orientation = 2;
    //                     }
    //                 }
    //                 tile = Block(CWL*(BS-SCALE), CHL*(BS-SCALE), BS, BS, "spike", SCALE, orientation, false);
    //             }
    //             Blocks.push_back(tile);
    //         }
    //         CHL++;
    //         previousLine = line;
    //     } else if (RenderPhase == 2) {
    //         int i = 0;
    //         int CWL;
    //         std::string text = "";
    //         std::string name = "";
    //         char category;

    //         for (; line[i] != '-'; i++) {
    //             if (isdigit(line[i])) {
    //                 text += line[i];
    //             }
    //         }
    //         i++;
    //         CWL = std::stoi(text);
    //         text = "";


    //         for (; line[i] != '-'; i++) {
    //             if (isdigit(line[i])) {
    //                 text += line[i];
    //             }
    //         }
    //         i++;
    //         CHL = std::stoi(text);
    //         text = "";


    //         for (; line[i] != '\0'; i++) {
    //             if (line[i] == '\"') {
    //                 continue;
    //             }
    //             if (line[i] == '-') {
    //                 if (text == "coin") {
    //                     category = 'C';
    //                 } else if (text == "food") {
    //                     category = 'F';
    //                 } else if (text == "Hshard") {
    //                     category = 'H';
    //                 } else if (text == "key") {
    //                     category = 'K';
    //                 } else if (text == "power") {
    //                     category = 'S';
    //                 }
    //             }
    //             text += line[i];
    //         }
    //         name = text;

    //         Item novoItem(CHL*(BS-SCALE), CWL*(BS-SCALE), name, SCALE, category);
    //         itens.push_back(novoItem);
    //     } else if (RenderPhase == 3) {
    //         int i = 0;
    //         int CWL;
    //         std::string text = "";
    //         std::string name = "";

    //         for (; line[i] != '-'; i++) {
    //             if (isdigit(line[i])) {
    //                 text += line[i];
    //             }
    //         }
    //         i++;
    //         CWL = std::stoi(text);
    //         text = "";


    //         for (; line[i] != '-'; i++) {
    //             if (isdigit(line[i])) {
    //                 text += line[i];
    //             }
    //         }
    //         i++;
    //         CHL = std::stoi(text);
    //         text = "";


    //         for (; line[i] != '\0'; i++) {
    //             if (line[i] == '\"') {
    //                 continue;
    //             }
    //             text += line[i];
    //         }
    //         name = text;

    //         Block ground;
    //         if (name == "snail" or name == "crab") {
    //             int sizeB = Blocks.size();
    //             for (int j = 0; j < sizeB; j++) {
    //                 ground = Blocks[j];
    //                 if (ground.rect.x == (float)(CHL)*(BS-SCALE) and ground.rect.y == (float)CWL*(BS-SCALE)) {
    //                     break;
    //                 }
    //             }
    //         }
    //         if (name == "snail") {
    //             enemies.push_back(Enemy((CHL-1)*(BS-SCALE), CWL*(BS-SCALE), name, SCALE, Blocks, RNG100(rng), ground));
    //         } else if (name == "butterfly") {
    //             enemies.push_back(Enemy(CHL*(BS-SCALE), CWL*(BS-SCALE), name, SCALE, Blocks, RNG100(rng)));
    //         } else if (name == "crab") {
    //             enemies.push_back(Enemy(CHL*(BS-SCALE), (CWL-1)*(BS-SCALE), name, SCALE, Blocks, RNG100(rng), ground));
    //         } else if (name == "meldrop") {
    //             enemies.push_back(Enemy(CHL*(BS-SCALE), CWL*(BS-SCALE), name, SCALE, Blocks, RNG100(rng)));
    //         } else {
    //             enemies.push_back(Enemy(CHL*(BS-SCALE), CWL*(BS-SCALE), name, SCALE, Blocks, RNG100(rng)));
    //         }
    //     }
    // }
    
    // level.close();

    // Map Level;
    // Level.Blocks = Blocks;
    // Level.itens = itens;
    // Level.enemies = enemies;
    // Level.widthLevel = widthLevel;
    // Level.heightLevel = heightLevel;
    // Level.playerX = playerX;
    // Level.playerY = playerY;
    // Level.time = timeLimit;
    // return Level;
}
