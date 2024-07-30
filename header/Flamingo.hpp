#ifndef FLAMINGO_H
#define FLAMINGO_H

#include "raylib.h"
#include <fstream>
#include <vector>
#include "Block.hpp"
#include "Item.hpp"
#include "Enemy.hpp"


class Flamingo {
public:
    Rectangle rect;
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

    Texture2D HeartGrid = LoadTexture("Images/heart_health.png"); // Corações de vida, cada coração tem 7 pontos de vida
    int MHH = 4*7; // Hope Health
    int MRH = 3*7; // Resilience Health
    int MPH = 2*7; // Power Health
    int MCH = 2*7; // Courage Health
    int MWH = 1*7; // Wisdom Health

    int HH = 4*7;
    int RH = 3*7;
    int PH = 2*7;
    int CH = 2*7;
    int WH = 1*7;

    int PHH = 0;
    int PRH = 0;
    int PPH = 0;
    int PCH = 0;
    int PWH = 0;

    Rectangle HB1;
    Sound sfxCoin = LoadSound("sfx/coin.wav"); 
    Sound sfxFood = LoadSound("sfx/eat.wav"); 
    Sound sfxJump = LoadSound("sfx/jump.wav");
    Sound sfxHeartPiece = LoadSound("sfx/HeartPiece.wav");
    Sound sfxSecret = LoadSound("sfx/secret.wav");
    Sound sfxKey = LoadSound("sfx/key.wav");
    Sound sfxDoor = LoadSound("sfx/door.wav");


    int WT, HT, SCALE;
    int naturalSpeed = 6;
    int tick = 1;
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
    int invincibility = 60;

    Flamingo(float x, float y, float w, float h, int worldWidth, int worldHeight, int imagescale);

    void Health(int qtd, char type);
    
    void update(std::vector<int> CBs, std::vector<Block> &map, std::vector<int> CIs, std::vector<Item> &itens, std::vector<int> CEs, std::vector<Enemy> enemies);

    int blockColision(Rectangle HBox, Block &temp, bool vert);

    void keyPress();
    void gravity();
    void Physics(std::vector<int> CBs, std::vector<Block> &map);
    void ItemColision (std::vector<int> CIs, std::vector<Item> &itens);

    void EnemyColision(std::vector<int> CEs, std::vector<Enemy> enemies);
    void TakeHit(Enemy enemy);

    void collect(Item item);

    bool groundCheck(Block ground);

    void updateHitbox();
    Vector2 colision(Rectangle hitbox, Rectangle B);
};

#endif