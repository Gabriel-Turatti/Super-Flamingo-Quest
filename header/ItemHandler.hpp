#ifndef ITEMHANDLER_H
#define ITEMHANDLER_H

#include "raylib.h"
#include "item.hpp"
#include <vector>
#include <unordered_map>

class ItemHandler {
public:
    std::unordered_map<int, Texture2D> images;

    ItemHandler(std::vector<Item> &itensLevel);
    ~ItemHandler();

    void addItem(Item temp);
    void DrawItens(std::vector<Item> &itensLevel, Rectangle cameraCenter, Rectangle relativeCameraCenter, int SCALE);
    void DrawItemHud(const std::vector<Item> &itensOption, int SCALE);

};

#endif