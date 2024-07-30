#include "../header/Functions.hpp"


bool GenericColision(Rectangle A, Rectangle B, int SCALE) {
    return
        (A.x + A.width*SCALE) > (B.x) and
        (A.x) < (B.x + B.width*SCALE) and
        (A.y) < (B.y + B.height*SCALE) and
        (A.height*SCALE + A.y) > (B.y);
}
