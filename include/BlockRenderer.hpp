#ifndef BLOCKHANDLER_H
#define BLOCKHANDLER_H

#include "raylib.h"
#include "Level.hpp"
#include "Block.hpp"
#include "Play.hpp"
#include "Functions.hpp"
#include <vector>
#include <unordered_map>

class BlockRenderer {
public:
    std::unordered_map<int, Texture2D> images;
    Play* game;

    BlockRenderer(Level &level, Play* gamer);
    BlockRenderer(std::vector<Block> &blocksLevel, Play* gamer);
    ~BlockRenderer();

    void addBlock(Block temp);
    void DrawBlocks(std::map<int, std::map<int, Block>> &blocksLevel, Rectangle cameraCenter, Rectangle relativeCameraCenter, int SCALE, bool background, bool showSecret);
    void DrawBlockHud(const std::vector<Block> &blocksOption, int SCALE);

};

#endif