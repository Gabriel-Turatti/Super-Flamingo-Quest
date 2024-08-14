#include "../header/BlockHandler.hpp"


BlockHandler::BlockHandler(std::vector<Block> &blocksLevel) {
    for (Block temp : blocksLevel) {
        if (images.count(temp.id) == 0) {
            addBlock(temp);
        }
    }
    for (auto& [id, image]: images) {
        SetTextureWrap(image, TEXTURE_WRAP_CLAMP);
    }
}

BlockHandler::~BlockHandler() {
    for (auto& [id, image]: images) {
        UnloadTexture(image);
    }
}

void BlockHandler::addBlock(Block temp) {
    switch (temp.id) {
        case 1:
            images[temp.id] = LoadTexture("images/coin-copper2.png");
            break;
        case 2:
            images[temp.id] = LoadTexture("images/coin-silver.png");
            break;
        case 3:
            images[temp.id] = LoadTexture("images/coin-gold.png");
            break;
        case 4:
            images[temp.id] = LoadTexture("images/coin-death.png");
            break;
        case 5:
            images[temp.id] = LoadTexture("images/food-banana.png");
            break;
        case 6:
            images[temp.id] = LoadTexture("images/food-pear.png");
            break;
        case 7:
            images[temp.id] = LoadTexture("images/food-blueberry.png");
            break;
        case 8:
            images[temp.id] = LoadTexture("images/food-pepper.png");
            break;
        case 9:
            images[temp.id] = LoadTexture("images/food-orange.png");
            break;
        case 10:
            images[temp.id] = LoadTexture("images/Hshard-hope.png");
            break;
        case 11:
            images[temp.id] = LoadTexture("images/Hshard-resilience.png");
            break;
        case 12:
            images[temp.id] = LoadTexture("images/Hshard-power.png");
            break;
        case 13:
            images[temp.id] = LoadTexture("images/Hshard-courage.png");
            break;
        case 14:
            images[temp.id] = LoadTexture("images/Hshard-wisdom.png");
            break;
        case 15:
            images[temp.id] = LoadTexture("images/Pshard-wind.png");
            break;
        case 16:
            images[temp.id] = LoadTexture("images/Pshard-party.png");
            break;
        case 17:
            images[temp.id] = LoadTexture("images/Pshard-fun.png");
            break;
        case 18:
            images[temp.id] = LoadTexture("images/Pshard-hard.png");
            break;
        case 19:
            images[temp.id] = LoadTexture("images/Pshard-eloise.png");
            break;
        case 20:
            images[temp.id] = LoadTexture("images/key-hope.png");
            break;
        case 21:
            images[temp.id] = LoadTexture("images/key-resilience.png");
            break;
        case 22:
            images[temp.id] = LoadTexture("images/key-power.png");
            break;
        case 23:
            images[temp.id] = LoadTexture("images/key-courage.png");
            break;
        case 24:
            images[temp.id] = LoadTexture("images/key-wisdom.png");
            break;
        case 25:
            images[temp.id] = LoadTexture("images/courage-potion.png");
            break;
        case 26:
            images[temp.id] = LoadTexture("images/party-potion.png");
            break;
        case 27:
            images[temp.id] = LoadTexture("images/power-dash.png");
            break;
        case 28:
            images[temp.id] = LoadTexture("images/power-???.png");
            break;
        case 29:
            images[temp.id] = LoadTexture("images/power-boost.png");
            break;
        case 30:
            images[temp.id] = LoadTexture("images/power-spear.png");
            break;
        case 31:
            images[temp.id] = LoadTexture("images/power-transmutation.png");
            break;            
    }
}

void BlockHandler::DrawBlocks(std::vector<Block> &blocksLevel, Rectangle cameraCenter, Rectangle relativeCameraCenter, int SCALE) {
    Vector2 relativePos;
    for (Block &temp : blocksLevel) {
        relativePos.x = cameraCenter.x +temp.rect.x -relativeCameraCenter.x;
        relativePos.y = cameraCenter.y +temp.rect.y -relativeCameraCenter.y;

        if (temp.name == "coin-copper") {
            Rectangle source, dest;

            source.x = 0 + temp.animation[temp.imageCount]*(temp.rectImage.width);
            source.y = 0;
            source.width = temp.rectImage.width;
            source.height = temp.rectImage.height;

            dest.x = relativePos.x;
            dest.y = relativePos.y;
            dest.width = temp.rect.width;
            dest.height = temp.rect.height;

            DrawTexturePro(images[temp.id], source, dest, {0, 0}, 0, WHITE);
            temp.tickImage += 1;
            if (temp.tickImage == 10) {
                temp.tickImage = 0;
                temp.imageCount += 1;
                if (temp.imageCount >= temp.imageSize) {
                    temp.imageCount = 0;
                }
            }
        } else {
            DrawTextureEx(images[temp.id], relativePos, 0, SCALE, WHITE);
        }
    }
}

void BlockHandler::DrawBlockHud(const std::vector<Block> &BlocksOption, int SCALE) {
    for (Block temp : BlocksOption) {
        DrawTextureEx(images[temp.id], {temp.rect.x, temp.rect.y}, 0, SCALE, WHITE);
    }
}

