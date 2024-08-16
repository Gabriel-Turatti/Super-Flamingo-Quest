#ifndef PLAY_H
#define PLAY_H

#include "raylib.h"

#include <sys/types.h>
#include <dirent.h>

#include "Block.hpp"
#include "Effect.hpp"
#include "Item.hpp"
#include "Level.hpp"
#include "Flamingo.hpp"
#include "Enemy.hpp"
#include "Functions.hpp"
#include "MapLoader.hpp"
#include "ItemHandler.hpp"

/*
*   Class dedicated to running the game.
*/
class Play {
public:
    const int SCALE = 3;
    const bool DEBUG = false;
    const float BS = 13*SCALE;
    const int BWT = 34;
    const int BHT = 25;
    const float WT = BS*BWT;
    const float HT = BS*BHT;
    const float FW = 18;
    const float FH = 23;
    int tickBlockUpdate = 5;
    int tick = 1;
    int seconds = 0;
    std::unique_ptr<Flamingo> player;
    int widthLevel;
    int heightLevel;

    Texture2D iconEditor = LoadTexture("images/mapEditor.png");
    Texture2D iconGame = LoadTexture("images/mainGame.png");
    Sound finish = LoadSound("sfx/finishLine.wav");


    struct Dust {
        Vector2 pos;
        Vector2 dt;
        Color cor;
        int timer;
        std::string dialog;
    };

    Music theme;

    
    std::random_device dev;
    std::mt19937 rng;
    std::uniform_int_distribution<std::mt19937::result_type> RNG100;
    std::uniform_int_distribution<std::mt19937::result_type> RNGe3;
    std::uniform_int_distribution<std::mt19937::result_type> RNGWidth;
    std::uniform_int_distribution<std::mt19937::result_type> RNGHeight;

    std::vector<Block> Blocks;
    std::vector<Item> itens;
    std::vector<Enemy> enemies;
    std::vector<Effect> effects;
    std::vector<Dust> dusts;
    int sizeB;
    int sizeE;
    int sizeI;
    int sizeD;
    int sizeS;

    int fadeout = 0;
    int saida = -1;

    float cx, cy;

    Rectangle cameraCenter, relativeCameraCenter;


    std::unique_ptr<MapLoader> loader;

    Play();
    ~Play();
    void loadFlamingo();
    void Hub();
    void HubLevelSelect();
    void HubMapEditor();
    void search_universe(std::vector<std::string> &Universe);

    void DustBringer(float x, float y, Color cor, int timer, bool random, std::string dialog = "");

    int complexityCalc(Item temp);
    int complexityCalc(Enemy temp);
    std::string PlayLevel(std::string level, std::string entrance);
    int mainLoop(Music LevelTheme);
    void EditLevel(std::string level);
    void DesenharHeart();
    void DesenharPearl();
    void DesenharBlocos(bool Background, bool showSecret);
};

#endif