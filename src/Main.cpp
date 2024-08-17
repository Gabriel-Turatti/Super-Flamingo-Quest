#include "raylib.h"
#include "../include/Play.hpp"


int main(void) {
    const int SCALE = 3;
    const int BS = 13*SCALE;
    const float WT = BS*34;
    const float HT = BS*25;
    InitWindow(WT, HT, "Super Flamingo Quest 0.8 - Level Editor Update");

    InitAudioDevice();

    Play game;
    game.loadFlamingo();
    game.Hub();

    CloseAudioDevice();

    CloseWindow();
    return 0;
}