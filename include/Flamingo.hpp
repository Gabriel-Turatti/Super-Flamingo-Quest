#ifndef FLAMINGO_H
#define FLAMINGO_H

#include <fstream>
#include <map>
#include <vector>

#include "block.hpp"
#include "Effect.hpp"
#include "Enemy.hpp"
#include "Item.hpp"
#include "Play.hpp"
#include "predefinitions.hpp"
#include "raylib.h"

class Flamingo {
   public:
    Rectangle rect;
    Rectangle rectImage;
    float cx, cy;
    float vx, vy;

    Rectangle Hitbox1, Hitbox2, Hitbox3, HitboxA;  // Leg, Chest, Head, Crouch

    std::vector<Texture2D> images = {
        LoadTexture("assets/images/Flamingo1.png"),
        LoadTexture("assets/images/Flamingo2.png"),
        LoadTexture("assets/images/Flamingo3.png"),
        LoadTexture("assets/images/FlamingoS.png"),
        LoadTexture("assets/images/FlamingoF.png"),
        LoadTexture("assets/images/FlamingoA.png"),
    };
    int imageCount = 0;
    int imageSize = 2;

    Texture2D HeartGrid =
        LoadTexture("assets/images/heart-health.png");  // Corações de vida, cada coração tem 7 pontos de vida
    Texture2D PearlGrid =
        LoadTexture("assets/images/pearl-mana.png");  // Pérolas de mana, cada pérola tem 7 pontos de mana
    // Health
    // Max
    int MHH = 4 * 7;  // Hope Health
    int MRH = 3 * 7;  // Resilience Health
    int MPH = 2 * 7;  // Power Health
    int MCH = 2 * 7;  // Courage Health
    int MWH = 1 * 7;  // Wisdom Health

    // Current
    int HH = 4 * 7;
    int RH = 3 * 7;
    int PH = 2 * 7;
    int CH = 2 * 7;
    int WH = 1 * 7;

    // Partial
    int PHH = 0;
    int PRH = 0;
    int PPH = 0;
    int PCH = 0;
    int PWH = 0;

    // Mana
    // Max
    int MWP = 2 * 7;  // Wind Pearl
    int MPP = 2 * 7;  // Party Pearl
    int MFP = 3 * 7;  // Fun Pearl
    int MHP = 1 * 7;  // Hard Pearl
    int MEP = 2 * 7;  // Eloise Pearl

    // Current
    int WP = 2 * 7;
    int PP = 2 * 7;
    int FP = 3 * 7;
    int HP = 1 * 7;
    int EP = 2 * 7;

    // Partial Max
    int PWP = 0;
    int PPP = 0;
    int PFP = 0;
    int PHP = 0;
    int PEP = 0;

    // Partial Current
    int pWP = 0;
    int pPP = 0;
    int pFP = 0;
    int pHP = 0;
    int pEP = 0;

    Rectangle HB1;
    Sound sfxCoin = LoadSound("assets/audio/sfx/coin.wav");
    Sound sfxFood = LoadSound("assets/audio/sfx/eat.wav");
    Sound sfxJump = LoadSound("assets/audio/sfx/jump.wav");
    Sound sfxHeartPiece = LoadSound("assets/audio/sfx/HeartPiece.wav");
    Sound sfxSecret = LoadSound("assets/audio/sfx/secret.wav");
    Sound sfxKey = LoadSound("assets/audio/sfx/key.wav");
    Sound sfxDoor = LoadSound("assets/audio/sfx/door.wav");
    Sound sfxVulnerable = LoadSound("assets/audio/sfx/LoseAllHealth.wav");
    Sound sfxHurt = LoadSound("assets/audio/sfx/hurt.wav");
    Sound sfxFall = LoadSound("assets/audio/sfx/fall.wav");
    Sound sfxPearlPiece = LoadSound("assets/audio/sfx/PearlPiece.wav");
    Sound sfxSpecial = LoadSound("assets/audio/sfx/SpecialItem.wav");

    int WT, HT, SCALE;
    int naturalSpeed = 6;
    int tick = 1;
    int tickBlockUpdate = 5;
    int score = 0;

    bool W, A, S, D;
    bool canJump = true;
    bool ground = false;
    Block groundBlock;
    bool lookingRight = true;
    bool crouch = false;
    int jumpQueue = 0;
    bool gameover = false;

    int keyHope = 0;
    int keyResilience = 0;
    int keyPower = 0;
    int keyCourage = 0;
    int keyWisdom = 0;
    std::map<char, int> invincibility = {{'H', 20}, {'R', 20}, {'P', 20}, {'C', 20}, {'W', 20}};

    Texture2D P1image = LoadTexture("assets/images/power-dash.png");
    Texture2D P2image = LoadTexture("assets/images/power-toast.png");
    Texture2D P3image = LoadTexture("assets/images/power-boost.png");
    Texture2D P4image = LoadTexture("assets/images/power-spear.png");
    Texture2D P5image = LoadTexture("assets/images/power-transmutation.png");
    std::vector<bool> powers = {
        0,
        0,
        0,
        0,
        0,  // Tier-1 powers: Dash, ???, Speed, Spear, Transmutation
        0,
        0,
        0,
        0,
        0,  // Tier-2 powers: Seer, Shield, ???, ???, Transfiguration
        0,
        0,  // Tier-S Powers: StopTime, VoiceHear
    };

    std::vector<int> CBs;  // List of blocks that can collide with player
    std::vector<int> CIs;  // List of itens that can collide with player
    std::vector<int> CEs;  // List of Enemies that can collide with player

    bool isBoost = false;
    char *nextLevel;
    int strength = 0;

    int birdsToSave[5] = {0, 0, 0, 0, 0};
    int totalBirdsSaved[5] = {0, 0, 0, 0, 0};

    Play *game;

    Flamingo(float x, float y, float w, float h, int worldWidth, int worldHeight, int imagescale);

    Flamingo();

    void unload();

    void Health(int qtd, char type);

    void update(std::vector<Block> &Blocks,
                std::vector<Item> &itens,
                std::vector<Enemy> enemies,
                std::vector<Effect> &effects);
    void CheckCloseObjects(std::vector<Block> &Blocks, std::vector<Item> &itens, std::vector<Enemy> enemies);

    int blockColision(Rectangle HBox, Block &temp, bool vert, std::vector<Effect> &effects);

    void keyPress(std::vector<Block> &Blocks, std::vector<Effect> &effects);
    void gravity();
    void Physics(std::vector<Block> &Blocks, std::vector<Effect> &effects);
    void ItemColision(std::vector<Item> &itens);

    void EnemyColision(std::vector<Enemy> enemies);
    void TakeHit(Enemy enemy);

    void collect(Item item);

    bool groundCheck(Block ground);

    void updateHitbox();
    Vector2 colision(Rectangle hitbox, Rectangle B);

    bool CheckMirror(std::vector<Block> &Blocks);
    bool CrouchCheck(std::vector<Block> &Blocks);
};

#endif