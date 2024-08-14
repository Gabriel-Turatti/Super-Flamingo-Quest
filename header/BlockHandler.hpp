#include "raylib.h"
#include "Block.hpp"
#include <vector>
#include <unordered_map>

class BlockHandler {
public:
    std::unordered_map<int, Texture2D> images;

    BlockHandler(std::vector<Block> &blocksLevel);
    ~BlockHandler();

    void addBlock(Block temp);
    void DrawBlocks(std::vector<Block> &blocksLevel, Rectangle cameraCenter, Rectangle relativeCameraCenter, int SCALE);
    void DrawBlockHud(const std::vector<Block> &blocksOption, int SCALE);

};