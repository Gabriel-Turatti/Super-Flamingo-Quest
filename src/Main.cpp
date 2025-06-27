#include "raylib.h"
#include "../include/Play.hpp"


int main(void) {
    const int SCALE = 3;
    const int BS = 13*SCALE;
    const float WT = BS*34;
    const float HT = BS*25;

    
    #ifdef OPERATIONALDEBUG
    std::ofstream operation("operationalFile");
    operation << "Well, at least the Main is being called.\n";
    operation.close();
    #endif
    
    
    InitWindow(WT, HT, "Super Flamingo Quest 0.8 - Level Editor Update");
    
    InitAudioDevice();
    
    
    #ifdef OPERATIONALDEBUG
    std::ofstream operation2("operationalFile", std::ios::app);
    operation2 << "Raylib stuff is working.\n";
    operation2.close();
    #endif

    Play game;
    
    
    #ifdef OPERATIONALDEBUG
    std::ofstream operation3("operationalFile", std::ios::app);
    operation3 << "game object has been initialized.\n";
    operation3.close();
    #endif

    game.loadFlamingo();
    
    
    #ifdef OPERATIONALDEBUG
    std::ofstream operation4("operationalFile", std::ios::app);
    operation4 << "Flamingo has loaded correctly!\n";
    operation4.close();
    #endif

    game.Hub();

    CloseAudioDevice();

    CloseWindow();
    return 0;
}