#ifndef BLOCKHANDLER_H
#define BLOCKHANDLER_H

#include "raylib.h"
#include "Block.hpp"
#include "Play.hpp"
#include "Functions.hpp"
#include <vector>
#include <unordered_map>

class BlockHandler {
public:
    std::unordered_map<int, Texture2D> images;
    Play* game;

    BlockHandler(std::vector<Block> &blocksLevel, Play* gamer);
    ~BlockHandler();

    void addBlock(Block temp);
    void DrawBlocks(std::vector<Block> &blocksLevel, Rectangle cameraCenter, Rectangle relativeCameraCenter, int SCALE, bool background, bool showSecret);
    void DrawBlockHud(const std::vector<Block> &blocksOption, int SCALE);

};

#endif