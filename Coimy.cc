#include "raylib.h"
#include <vector>

class Element {
public:
    int id = 0;
    std::vector<int> V = {0, 0};
    std::vector<int> P = {0, 0};
    int mass = 0;

    Element(idW, VW, PW, massW) {
        id = idW
        V = VW
        P = PW
        mass = massW
    }
}

class ElementDrawer {
    std::vector<Texture2D> = {
        LoadTexture("Images/Chi.png")
    };
}


// DrawTexturePro(image, origin, dest, {0, 0}, 0, WHITE);

int main(void) {

    elements = [];
    for (i = 0; i < 10; i++) {
        Element e = Element(1, {1, 1}, {50, 50}, 1);
        elements.push_back(e);
    }

    while (true) {
        BeginDrawing();
        ClearBackground(BLACK);
        for (e : elements) {
            e.update()
            e.draw()
        }
        EndDrawing();
    }

    return 0;
}
