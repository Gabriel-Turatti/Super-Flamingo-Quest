#include "../include/ItemHandler.hpp"


ItemHandler::ItemHandler(std::vector<Item> &itensLevel) {
    for (Item temp : itensLevel) {
        if (images.count(temp.id) == 0) {
            addItem(temp);
        }
    }
    for (auto& [id, image]: images) {
        SetTextureWrap(image, TEXTURE_WRAP_CLAMP);
    }
}

ItemHandler::~ItemHandler() {
    for (auto& [id, image]: images) {
        UnloadTexture(image);
    }
}

void ItemHandler::addItem(Item temp) {
    switch (temp.id) {
        case 1:
            images[temp.id] = LoadTexture("assets/images/coin-copper2.png");
            break;
        case 2:
            images[temp.id] = LoadTexture("assets/images/coin-silver2.png");
            break;
        case 3:
            images[temp.id] = LoadTexture("assets/images/coin-gold2.png");
            break;
        case 4:
            images[temp.id] = LoadTexture("assets/images/coin-death2.png");
            break;
        case 5:
            images[temp.id] = LoadTexture("assets/images/food-banana.png");
            break;
        case 6:
            images[temp.id] = LoadTexture("assets/images/food-pear.png");
            break;
        case 7:
            images[temp.id] = LoadTexture("assets/images/food-blueberry.png");
            break;
        case 8:
            images[temp.id] = LoadTexture("assets/images/food-pepper.png");
            break;
        case 9:
            images[temp.id] = LoadTexture("assets/images/food-orange.png");
            break;
        case 10:
            images[temp.id] = LoadTexture("assets/images/Hshard-hope.png");
            break;
        case 11:
            images[temp.id] = LoadTexture("assets/images/Hshard-resilience.png");
            break;
        case 12:
            images[temp.id] = LoadTexture("assets/images/Hshard-power.png");
            break;
        case 13:
            images[temp.id] = LoadTexture("assets/images/Hshard-courage.png");
            break;
        case 14:
            images[temp.id] = LoadTexture("assets/images/Hshard-wisdom.png");
            break;
        case 15:
            images[temp.id] = LoadTexture("assets/images/Pshard-wind.png");
            break;
        case 16:
            images[temp.id] = LoadTexture("assets/images/Pshard-party.png");
            break;
        case 17:
            images[temp.id] = LoadTexture("assets/images/Pshard-fun.png");
            break;
        case 18:
            images[temp.id] = LoadTexture("assets/images/Pshard-hard.png");
            break;
        case 19:
            images[temp.id] = LoadTexture("assets/images/Pshard-eloise.png");
            break;
        case 20:
            images[temp.id] = LoadTexture("assets/images/key-hope.png");
            break;
        case 21:
            images[temp.id] = LoadTexture("assets/images/key-resilience.png");
            break;
        case 22:
            images[temp.id] = LoadTexture("assets/images/key-power.png");
            break;
        case 23:
            images[temp.id] = LoadTexture("assets/images/key-courage.png");
            break;
        case 24:
            images[temp.id] = LoadTexture("assets/images/key-wisdom.png");
            break;
        case 25:
            images[temp.id] = LoadTexture("assets/images/courage-potion.png");
            break;
        case 26:
            images[temp.id] = LoadTexture("assets/images/party-potion.png");
            break;
        case 27:
            images[temp.id] = LoadTexture("assets/images/power-dash.png");
            break;
        case 28:
            images[temp.id] = LoadTexture("assets/images/power-toast.png");
            break;
        case 29:
            images[temp.id] = LoadTexture("assets/images/power-boost.png");
            break;
        case 30:
            images[temp.id] = LoadTexture("assets/images/power-spear.png");
            break;
        case 31:
            images[temp.id] = LoadTexture("assets/images/power-transmutation.png");
            break;            
        case 32:
            images[temp.id] = LoadTexture("assets/images/coin-poison.png");
            break;            
    }
}

void ItemHandler::DrawItens(std::vector<Item> &itensLevel, Rectangle cameraCenter, Rectangle relativeCameraCenter, int SCALE) {
    Vector2 relativePos;
    for (Item &temp : itensLevel) {
        relativePos.x = cameraCenter.x +temp.rect.x -relativeCameraCenter.x;
        relativePos.y = cameraCenter.y +temp.rect.y -relativeCameraCenter.y;

        if (temp.category == 'C') {
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
            if (temp.tickImage == 5) {
                temp.tickImage = 0;
                temp.imageCount += 1;
                if (temp.imageCount >= temp.imageSize) {
                    temp.imageCount = 0;
                }
            }
        } else {
            temp.imageCount += 1;
            if (temp.imageCount > 60) {
                temp.imageCount = 0;
            }
            if (temp.imageCount < 15) {
                relativePos.y += SCALE;
            } else if (temp.imageCount < 30) {

            } else if (temp.imageCount < 45) {
                relativePos.y -= SCALE;
            }
            DrawTextureEx(images[temp.id], relativePos, 0, SCALE, WHITE);
        }
    }
}

void ItemHandler::DrawItemHud(const std::vector<Item> &itensOption, int SCALE) {
    for (Item temp : itensOption) {
        if (temp.category == 'C') {
            Rectangle source, dest;

            source.x = 0;
            source.y = 0;
            source.width = temp.rectImage.width;
            source.height = temp.rectImage.height;

            dest.x = temp.rect.x;
            dest.y = temp.rect.y;
            dest.width = temp.rect.width;
            dest.height = temp.rect.height;

            DrawTexturePro(images[temp.id], source, dest, {0, 0}, 0, WHITE);
        } else {
            DrawTextureEx(images[temp.id], {temp.rect.x, temp.rect.y}, 0, SCALE, WHITE);
        }
    }
}

