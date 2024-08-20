#include "../include/Functions.hpp"


bool GenericColision(Rectangle A, Rectangle B) {
    return
        (A.x + A.width) > (B.x) and
        (A.x) < (B.x + B.width) and
        (A.y) < (B.y + B.height) and
        (A.height + A.y) > (B.y);
}
