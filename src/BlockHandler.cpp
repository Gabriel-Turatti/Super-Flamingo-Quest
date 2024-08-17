#include "../include/BlockHandler.hpp"


BlockHandler::BlockHandler(std::vector<Block> &blocksLevel, Play* gamer) {
    game = gamer;
    images[29] = LoadTexture("assets/images/block_energy.png");
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
            images[temp.id] = LoadTexture("assets/images/block_grass.png");
            break;
        case 2:
            images[temp.id] = LoadTexture("assets/images/block_dirt.png");
            break;
        case 3:
            images[temp.id] = LoadTexture("assets/images/block_dirt2x2.png");
            break;
        case 4:
            images[temp.id] = LoadTexture("assets/images/block_brick.png");
            break;
        case 5:
            images[temp.id] = LoadTexture("assets/images/block_gate_hope_closed.png");
            break;
        case 6:
            images[temp.id] = LoadTexture("assets/images/block_gate_resilience_closed.png");
            break;
        case 7:
            images[temp.id] = LoadTexture("assets/images/block_gate_power_closed.png");
            break;
        case 8:
            images[temp.id] = LoadTexture("assets/images/block_gate_courage_closed.png");
            break;
        case 9:
            images[temp.id] = LoadTexture("assets/images/block_gate_wisdom_closed.png");
            break;
        case 10:
            images[temp.id] = LoadTexture("assets/images/block_gate_hope_open.png");
            break;
        case 11:
            images[temp.id] = LoadTexture("assets/images/block_gate_resilience_open.png");
            break;
        case 12:
            images[temp.id] = LoadTexture("assets/images/block_gate_power_open.png");
            break;
        case 13:
            images[temp.id] = LoadTexture("assets/images/block_gate_courage_open.png");
            break;
        case 14:
            images[temp.id] = LoadTexture("assets/images/block_gate_wisdom_open.png");
            break;
        case 15:
            images[temp.id] = LoadTexture("assets/images/block_altar.png");
            break;
        case 16:
            images[temp.id] = LoadTexture("assets/images/block_spike.png");
            break;
        case 17:
            images[temp.id] = LoadTexture("assets/images/block_nextLevel.png");
            break;
        case 18:
            images[temp.id] = LoadTexture("assets/images/block_StartLevel.png");
            break;
        case 19:
            images[temp.id] = LoadTexture("assets/images/block_bird_yellow.png");
            break;
        case 20:
            images[temp.id] = LoadTexture("assets/images/block_bird_green.png");
            break;
        case 21:
            images[temp.id] = LoadTexture("assets/images/block_bird_blue.png");
            break;
        case 22:
            images[temp.id] = LoadTexture("assets/images/block_bird_red.png");
            break;
        case 23:
            images[temp.id] = LoadTexture("assets/images/block_bird_orange.png");
            break;
        case 24:
            images[temp.id] = LoadTexture("assets/images/block_honey.png");
            break;
        case 25:
            images[temp.id] = LoadTexture("assets/images/block_vines.png");
            break;
        case 26:
            images[temp.id] = LoadTexture("assets/images/block_ivy.png");
            break;
        case 27:
            images[temp.id] = LoadTexture("assets/images/block_green_control.png");
            break;
        case 28:
            images[temp.id] = LoadTexture("assets/images/block_green.png");
            break;
        case 29:
            images[temp.id] = LoadTexture("assets/images/block_energy.png");
            break;
        case 30:
            images[temp.id] = LoadTexture("assets/images/platform.png");
            break;
        default:
            images[temp.id] = LoadTexture("assets/images/block_energy.png");
            break;

    }
}

void BlockHandler::DrawBlocks(std::vector<Block> &blocksLevel, Rectangle cameraCenter, Rectangle relativeCameraCenter, int SCALE, bool background, bool showSecret) {
    int sizeB = blocksLevel.size();
    Vector2 relativePos;
    for (int i = 0; i < sizeB; i++) {
        Block temp = blocksLevel[i];
        if (temp.background != background) {
            continue;
        }
        if (temp.name == "nextLevel" and game->fadeout == 0) {
            if (GenericColision(game->player->rect, temp.rect)) {
                game->fadeout = 1;
                game->saida = i;
                PlaySound(game->finish);
            }
        }

        relativePos.x = cameraCenter.x +temp.rect.x -relativeCameraCenter.x;
        relativePos.y = cameraCenter.y +temp.rect.y -relativeCameraCenter.y;
        if (temp.direction != 0) {
            if (temp.direction == 1) {
                relativePos.y += temp.rect.height;
            } else if (temp.direction == 2) {
                relativePos.x += temp.rect.width;
                relativePos.y += temp.rect.height;
            } else if (temp.direction == 3) {
                relativePos.x += temp.rect.width;
            }
        }

        Color transparency;
        if (temp.background) {
            transparency = GRAY;
        } else {
            transparency = WHITE;
        }

        if (temp.name == "cage") {
            Rectangle source, dest;
            if ((game->tick+(int)temp.rect.x+(int)temp.rect.y) % 20 < 10) {
                source.x = 12;
            } else {
                source.x = 0;
            }
            source.y = 0;
            source.width = temp.rectImage.width;
            source.height = temp.rectImage.height;

            dest.x = relativePos.x;
            dest.y = relativePos.y;
            dest.width = temp.rect.width;
            dest.height = temp.rect.height;

            DrawTexturePro(images[temp.id], source, dest, {0, 0}, temp.direction*-90, transparency);
        } else {
            DrawTextureEx(images[temp.id], relativePos, temp.direction*-90, SCALE, transparency);
        }
        if (temp.secret) {
            DrawText("S", relativePos.x, relativePos.y, game->BS, WHITE);
        }
    }
}

void BlockHandler::DrawBlockHud(const std::vector<Block> &BlocksOption, int SCALE) {
    for (Block temp : BlocksOption) {
        DrawTextureEx(images[temp.id], {temp.rect.x, temp.rect.y}, 0, SCALE, WHITE);
    }
}

