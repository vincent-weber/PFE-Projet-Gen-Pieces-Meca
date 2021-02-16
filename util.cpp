#include "util.h"

float radians(float angle_deg) {
    return angle_deg * (PI / 180);
}

float min(float a, float b) {
    if (a < b) {
        return a;
    }
    return b;
}
