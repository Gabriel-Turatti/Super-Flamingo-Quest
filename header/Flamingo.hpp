#ifndef FLAMINGO_H
#define FLAMINGO_H

#include "raylib.h"
#include <fstream>
#include <vector>
#include <map>
#include "Block.hpp"
#include "Item.hpp"
#include "Enemy.hpp"
#include "Effect.hpp"


class Flamingo {
public:
    Rectangle rect;
    Rectangle rectImage;
    float cx, cy;
    float vx, vy;

    Rectangle Hitbox1, Hitbox2, Hitbox3, HitboxA; // Leg, Chest, Head, Crouch

    std::vector<Texture2D> images = {
        LoadTexture("images/Flamingo1.png"),
        LoadTexture("images/Flamingo2.png"),
        LoadTexture("images/Flamingo3.png"),
        LoadTexture("images/FlamingoS.png"),
        LoadTexture("images/FlamingoF.png"),
        LoadTexture("images/FlamingoA.png"),
    };
    int imageCount = 0;
    int imageSize = 2;

    Texture2D HeartGrid = LoadTexture("Images/heart-health.png"); // Corações de vida, cada coração tem 7 pontos de vida
    Texture2D PearlGrid = LoadTexture("Images/pearl-mana.png"); // Pérolas de mana, cada pérola tem 7 pontos de mana
    // Health
    // Max
    int MHH = 4*7; // Hope Health
    int MRH = 3*7; // Resilience Health
    int MPH = 2*7; // Power Health
    int MCH = 2*7; // Courage Health
    int MWH = 1*7; // Wisdom Health

    // Current
    int HH = 4*7;
    int RH = 3*7;
    int PH = 2*7;
    int CH = 2*7;
    int WH = 1*7;

    // Partial
    int PHH = 0;
    int PRH = 0;
    int PPH = 0;
    int PCH = 0;
    int PWH = 0;

    // Mana
    // Max
    int MWP = 2*7; // Wind Pearl
    int MPP = 2*7; // Party Pearl
    int MFP = 3*7; // Fun Pearl
    int MHP = 1*7; // Hard Pearl
    int MEP = 2*7; // Eloise Pearl

    // Current
    int WP = 2*7;
    int PP = 2*7;
    int FP = 3*7;
    int HP = 1*7;
    int EP = 2*7;

    // Partial Max
    int PWP = 0;
    int PPP = 0;
    int PFP = 0;
    int PHP = 0;
    int PEP = 0;

    Rectangle HB1;
    Sound sfxCoin = LoadSound("sfx/coin.wav"); 
    Sound sfxFood = LoadSound("sfx/eat.wav"); 
    Sound sfxJump = LoadSound("sfx/jump.wav");
    Sound sfxHeartPiece = LoadSound("sfx/HeartPiece.wav");
    Sound sfxSecret = LoadSound("sfx/secret.wav");
    Sound sfxKey = LoadSound("sfx/key.wav");
    Sound sfxDoor = LoadSound("sfx/door.wav");
    Sound sfxVulnerable = LoadSound("sfx/LoseAllHealth.wav");
    Sound sfxHurt = LoadSound("sfx/hurt.wav");
    Sound sfxFall = LoadSound("sfx/fall.wav");
    Sound sfxPearlPiece = LoadSound("sfx/PearlPiece.wav");
    Sound sfxSpecial = LoadSound("sfx/SpecialItem.wav");


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
    std::map<char, int> invincibility = {
        { 'H', 20 },
        { 'R', 20 },
        { 'P', 20 },
        { 'C', 20 },
        { 'W', 20 }
    };

    Texture2D P1image = LoadTexture("images/power-dash.png");
    // Texture2D P2image = LoadTexture("images/power-???.png");
    Texture2D P3image = LoadTexture("images/power-boost.png");
    Texture2D P4image = LoadTexture("images/power-spear.png");
    Texture2D P5image = LoadTexture("images/power-transmutation.png");
    std::vector<bool> powers = {
        0, 0, 0, 0, 0, // Tier-1 powers: Dash, ???, Speed, Spear, Transmutation
        0, 0, 0, 0, 0, // Tier-2 powers: Seer, Shield, ???, ???, Transfiguration
        0, 0, // Tier-S Powers: StopTime, VoiceHear 
    };

    std::vector<int> CBs; // List of blocks that can collide with player
    std::vector<int> CIs; // List of itens that can collide with player
    std::vector<int> CEs; // List of Enemies that can collide with player

    bool isBoost = false;

    Flamingo(float x, float y, float w, float h, int worldWidth, int worldHeight, int imagescale);

    Flamingo();

    void Health(int qtd, char type);
    
    void update(std::vector<Block> &Blocks, std::vector<Item> &itens, std::vector<Enemy> enemies, std::vector<Effect> &effects);
    void CheckCloseObjects(std::vector<Block> &Blocks, std::vector<Item> &itens, std::vector<Enemy> enemies);

    int blockColision(Rectangle HBox, Block &temp, bool vert);

    void keyPress(std::vector<Block> &Blocks, std::vector<Effect> &effects);
    void gravity();
    void Physics(std::vector<Block> &Blocks);
    void ItemColision (std::vector<Item> &itens);

    void EnemyColision(std::vector<Enemy> enemies);
    void TakeHit(Enemy enemy);

    void collect(Item item);

    bool groundCheck(Block ground);

    void updateHitbox();
    Vector2 colision(Rectangle hitbox, Rectangle B);

    bool CheckMirror(std::vector<Block> &Blocks);
};

#endif