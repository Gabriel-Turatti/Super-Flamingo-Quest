#include "../header/MapLoader.hpp"



MapLoader::MapLoader(int SCALER, int BSer, float width, float height) {
    SCALE = SCALER;
    BS = BSer;
    WT = BS*width;
    HT = BS*height;
}

MapLoader::MapLoader() {}

void MapLoader::SaveLevel(Map level) {
    float leftMostBlock = 1.5;
    float upMostBlock = 1.5;
    float rightMostBlock = 1.5;
    float downMostBlock = 1.5;

    for (Block temp : level.Blocks) {
        if (leftMostBlock == 1.5 or temp.rect.x < leftMostBlock) {
            leftMostBlock = temp.rect.x;
        }
        if (upMostBlock == 1.5 or temp.rect.y < upMostBlock) {
            upMostBlock = temp.rect.y;
        }
        if (rightMostBlock == 1.5 or temp.rect.x+temp.rect.width > rightMostBlock) {
            rightMostBlock = temp.rect.x+temp.rect.width;
        }
        if (downMostBlock == 1.5 or temp.rect.y+temp.rect.height > downMostBlock) {
            downMostBlock = temp.rect.y+temp.rect.height;
        }
    }
    for (Item temp : level.itens) {
        if (leftMostBlock == 1.5 or temp.rect.x < leftMostBlock) {
            leftMostBlock = temp.rect.x;
        }
        if (upMostBlock == 1.5 or temp.rect.y < upMostBlock) {
            upMostBlock = temp.rect.y;
        }
        if (rightMostBlock == 1.5 or temp.rect.x+temp.rect.width > rightMostBlock) {
            rightMostBlock = temp.rect.x+temp.rect.width;
        }
        if (downMostBlock == 1.5 or temp.rect.y+temp.rect.height > downMostBlock) {
            downMostBlock = temp.rect.y+temp.rect.height;
        }
    }

    level.widthLevel = (int) (rightMostBlock - leftMostBlock -SCALE)/(BS-SCALE);
    level.heightLevel = (int) (downMostBlock - upMostBlock -SCALE)/(BS-SCALE);

    int lineOffset;
    int columnOffset;
    if (leftMostBlock < 0) {
        columnOffset = (leftMostBlock)/(BS-SCALE);
    } else {
        columnOffset = (leftMostBlock)/(BS-SCALE);
    }
    if (upMostBlock < 0) {
        lineOffset = (upMostBlock)/(BS-SCALE);
    } else {
        lineOffset = (upMostBlock)/(BS-SCALE);
    }

    std::map<int, std::map<int, Block>> NewBlocksGround;
    std::map<int, std::map<int, Block>> NewBlocksBackground;
    std::map<int, std::map<int, Item>> NewItens;

    for (Block temp : level.Blocks) { // May cause bugs if position is negative
        int LinePos = (int) ((temp.rect.y)/(BS-SCALE)) - lineOffset;
        int ColumnPos = (int) ((temp.rect.x)/(BS-SCALE)) - columnOffset;
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

        int LinePos = (int) ((temp.rect.y)/(BS-SCALE)) - lineOffset;
        int ColumnPos = (int) ((temp.rect.x)/(BS-SCALE)) - columnOffset;
        NewItens[LinePos][ColumnPos] = temp;
    }



    std::ofstream LevelSave("levels/"+level.name);
    if (LevelSave.is_open()) {
        std::string emptyLine(level.widthLevel, '-');

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
                LevelSave << emptyLine << '\n';
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
                        LevelSave << 'A';
                    } else if (NewBlocksGround[i][j].name == "nextLevel") {
                        LevelSave << 'N';
                    } else if (NewBlocksGround[i][j].name == "startLevel") {
                        LevelSave << 'F';
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
                LevelSave << emptyLine << '\n';
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
                LevelSave << emptyLine << '\n';
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
            int LinePos = (int) ((temp.rect.y)/(BS-SCALE)) - lineOffset;
            int ColumnPos = (int) ((temp.rect.x)/(BS-SCALE)) - columnOffset;
            if (temp.name == "snail") {
                LinePos += 1;
            }
            LevelSave << std::to_string(LinePos) << '-' << std::to_string(ColumnPos) << '-' << '\"' << temp.name << "\"\n";
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
    int CHL = 0; // Current Height Level (AKA. what column of blocks we are currently looking during the Blocks load)
    int widthLevel;
    int heightLevel;
    float playerX;
    float playerY;
    std::vector<std::string> exits;
    std::vector<std::string> entrances;

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> RNG100(0, 100);

    int charPoint = 0;



    std::getline(level, line);
    heightLevel = std::stoi(line);
    std::getline(level, line);
    widthLevel = std::stoi(line);

    std::getline(level, line);
    char* LevelTheme = strdup(line.c_str());

    std::getline(level, line);
    int timeLimit = std::stoi(line);



    std::getline(level, line);
    while (line[0] == 'S') {
        line = line.substr(2, line.size() - 1);
        exits.push_back(line);
        std::getline(level, line);
    }
    while (line[0] == 'E') {
        line = line.substr(2, line.size() - 1);
        entrances.push_back(line);
        std::getline(level, line);
    }




    int RenderPhase = 0;
    // 1 = Blocks Ground;
    // 2 = Blocks Background;
    // 3 = Itens;
    // 4 = Enemies;
    if (line == "P1") {
        RenderPhase = 1;
    }

    std::vector<Block> Blocks;
    std::map<int, std::map<int, Block>> BlocksMap;
    std::vector<Item> itens;
    std::vector<Enemy> enemies;
    while (!level.eof()) {
        std::getline(level, line);
        if (line == "endmap") {
            break;
        }
        if (line[0] == 'P' and line[1] != 'p') {
            CHL = 0;
            if (line[1] == '2') {
                RenderPhase = 2;
            } else if (line[1] == '3') {
                RenderPhase = 3;
            } else if (line[1] == '4') {
                RenderPhase = 4;
            }
            continue;
        }
        if (RenderPhase == 1 or RenderPhase == 2) {
            charPoint = -1;
            for (int CWL = 0; CWL < widthLevel; CWL++) { // Current Width Level
                charPoint++;
                if (line[charPoint] == '-' or line[charPoint] == 'p') {
                    continue;
                }
                Block tile;
                if (line[charPoint] == 'F') {
                    tile = Block(CWL*(BS-SCALE), CHL*(BS-SCALE), BS, BS*2-SCALE, "startLevel", SCALE);
                    playerX = CWL*(BS-SCALE); // to-do
                    playerY = CHL*(BS-SCALE)-SCALE;
                } else if (line[charPoint] == 'N') {
                    tile = Block(CWL*(BS-SCALE), CHL*(BS-SCALE), BS, BS*2-SCALE, "nextLevel", SCALE);
                } else if (line[charPoint] == 'G') {
                    tile = Block(CWL*(BS-SCALE), CHL*(BS-SCALE), BS, BS, "grass", SCALE);
                } else if (line[charPoint] == 'B') {
                    tile = Block(CWL*(BS-SCALE), CHL*(BS-SCALE), BS, BS, "brick", SCALE);
                } else if (line[charPoint] == 'D') {
                    if (line[charPoint+1] == '2') {
                        tile = Block(CWL*(BS-SCALE), CHL*(BS-SCALE), BS*2-SCALE, BS*2-SCALE, "dirt2", SCALE);
                        charPoint++;
                        CWL++;
                    } else {
                        tile = Block(CWL*(BS-SCALE), CHL*(BS-SCALE), BS, BS, "dirt", SCALE);
                    }
                } else if (line[charPoint] == 'P') {
                    if (line[charPoint+1] == 'p') {
                        tile = Block(CWL*(BS-SCALE), CHL*(BS-SCALE), BS*2-SCALE, BS, "platform", SCALE, 0, false);
                    } else {
                        tile = Block(CWL*(BS-SCALE), CHL*(BS-SCALE), BS, BS*2-SCALE, "platform", SCALE, 90, false);
                    }
                } else if (line[charPoint] == 'A') {
                    tile = Block(CWL*(BS-SCALE), CHL*(BS-SCALE), BS, BS, "altar", SCALE);
                } else if (line[charPoint] == '(') {
                    if (line[charPoint+1] == 'K') {
                        int rotation = 0;
                        std::string type;
                        if (line[charPoint+2] == 'h') {
                            type = "hope";
                        }
                        if (line[charPoint+2] == 'r') {
                            type = "resilience";
                        }
                        if (line[charPoint+2] == 'p') {
                            type = "power";
                        }
                        if (line[charPoint+2] == 'c') {
                            type = "courage";
                        }
                        if (line[charPoint+2] == 'w') {
                            type = "wisdom";
                        }
                        rotation = line[charPoint+3] - '0';
                        tile = Block(CWL*(BS-SCALE), CHL*(BS-SCALE), BS, BS*2-SCALE, "gate-" + type, SCALE, rotation, false);
                        charPoint += 4;
                    } else if (line[charPoint+1] == 'S') {
                        int orientation = line[charPoint+2] - '0';
                        tile = Block(CWL*(BS-SCALE), CHL*(BS-SCALE), BS, BS, "spike", SCALE, orientation, false);
                        charPoint += 3;
                    }
                } else {
                    continue;
                }
                if (RenderPhase == 2) {
                    tile.background = true;
                }
                BlocksMap[CHL][CWL] = tile;
                Blocks.push_back(tile);
            }
            CHL++;
        } else if (RenderPhase == 3) {
            charPoint = -1;
            for (int CWL = 0; CWL < widthLevel; CWL++) { // Current Width Level
                charPoint++;
                if (line[charPoint] == '-') {
                    continue;
                }
                Item temp;
                if (line[charPoint] == 'C') {
                    temp = Item(CWL*(BS-SCALE), CHL*(BS-SCALE), "courage-potion", SCALE, 'S');
                } else if (line[charPoint] == 'P') {
                    temp = Item(CWL*(BS-SCALE), CHL*(BS-SCALE), "party-potion", SCALE, 'S');
                } else if (line[charPoint] == '(') {
                    if (line[charPoint+1] == 'C') {
                        std::string addon = "copper";
                        if (line[charPoint+2] == 'p') {
                            addon = "silver";
                        } else if (line[charPoint+2] == 'g') {
                            addon = "gold";
                        } else if (line[charPoint+2] == 'd') {
                            addon = "death";
                        }
                        temp = Item(CWL*(BS-SCALE), CHL*(BS-SCALE), "coin-"+addon, SCALE, 'C');
                    } else if (line[charPoint+1] == 'F') {
                        std::string addon = "banana";
                        if (line[charPoint+2] == 'r') {
                            addon = "pear";
                        } else if (line[charPoint+2] == 'p') {
                            addon = "blueberry";
                        } else if (line[charPoint+2] == 'c') {
                            addon = "pepper";
                        } else if (line[charPoint+2] == 'w') {
                            addon = "orange";
                        }
                        temp = Item(CWL*(BS-SCALE), CHL*(BS-SCALE), "food-"+addon, SCALE, 'F');
                    } else if (line[charPoint+1] == 'H') {
                        std::string addon = "hope";
                        if (line[charPoint+2] == 'r') {
                            addon = "resilience";
                        } else if (line[charPoint+2] == 'p') {
                            addon = "power";
                        } else if (line[charPoint+2] == 'c') {
                            addon = "courage";
                        } else if (line[charPoint+2] == 'w') {
                            addon = "wisdom";
                        }
                        temp = Item(CWL*(BS-SCALE), CHL*(BS-SCALE), "Hshard-"+addon, SCALE, 'H');
                    } else if (line[charPoint+1] == 'K') {
                        std::string addon = "hope";
                        if (line[charPoint+2] == 'r') {
                            addon = "resilience";
                        } else if (line[charPoint+2] == 'p') {
                            addon = "power";
                        } else if (line[charPoint+2] == 'c') {
                            addon = "courage";
                        } else if (line[charPoint+2] == 'w') {
                            addon = "wisdom";
                        }
                        temp = Item(CWL*(BS-SCALE), CHL*(BS-SCALE), "key-"+addon, SCALE, 'K');
                    } else if (line[charPoint+1] == 'P') {
                        std::string addon = "wind";
                        if (line[charPoint+2] == 'p') {
                            addon = "party";
                        } else if (line[charPoint+2] == 'f') {
                            addon = "fun";
                        } else if (line[charPoint+2] == 'h') {
                            addon = "hard";
                        } else if (line[charPoint+2] == 'e') {
                            addon = "eloise";
                        }
                        temp = Item(CWL*(BS-SCALE), CHL*(BS-SCALE), "Pshard-"+addon, SCALE, 'P');
                    } else if (line[charPoint+1] == 'S') {
                        std::string addon = "dash";
                        if (line[charPoint+2] == 'p') {
                            addon = "party";
                        } else if (line[charPoint+2] == 'f') {
                            addon = "boost";
                        } else if (line[charPoint+2] == 'h') {
                            addon = "spear";
                        } else if (line[charPoint+2] == 'e') {
                            addon = "transmutation";
                        }
                        temp = Item(CWL*(BS-SCALE), CHL*(BS-SCALE), "power-"+addon, SCALE, 'S');
                    }
                    charPoint += 3;
                }
                itens.push_back(temp);
            }
            CHL++;
        } else if (RenderPhase == 4) {
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
            CHL = std::stoi(text);
            text = "";


            for (; line[i] != '-'; i++) {
                if (isdigit(line[i])) {
                    text += line[i];
                }
            }
            i++;
            CWL = std::stoi(text);
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
                ground = BlocksMap[CHL][CWL];
            }
            if (name == "snail") {
                enemies.push_back(Enemy((CWL)*(BS-SCALE), CHL*(BS-SCALE), name, SCALE, Blocks, RNG100(rng), ground));
            } else if (name == "butterfly") {
                enemies.push_back(Enemy(CWL*(BS-SCALE), CHL*(BS-SCALE), name, SCALE, Blocks, RNG100(rng)));
            } else if (name == "crab") {
                enemies.push_back(Enemy(CWL*(BS-SCALE), (CHL)*(BS-SCALE), name, SCALE, Blocks, RNG100(rng), ground));
            } else if (name == "meldrop") {
                enemies.push_back(Enemy(CWL*(BS-SCALE), CHL*(BS-SCALE), name, SCALE, Blocks, RNG100(rng)));
            } else {
                enemies.push_back(Enemy(CWL*(BS-SCALE), CHL*(BS-SCALE), name, SCALE, Blocks, RNG100(rng)));
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
    Level.time = timeLimit;
    Level.name = name;
    Level.levelTheme = LevelTheme;
    Level.time = timeLimit;
    Level.entrances = entrances;
    Level.exits = exits;
    return Level;
}
