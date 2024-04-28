#include "raylib.h"
#include "raymath.h"
#include <stdlib.h> // For malloc
#include "enemy.h"

using namespace std;

Vector2* GenerateRandomPositions(int count, int screenWidth, int screenHeight) {
    Vector2* positions = (Vector2*)malloc(count * sizeof(Vector2));
    if (positions != NULL) {
        for (int i = 0; i < count; i++) {
            // Generate random positions within the screen boundaries
            positions[i].x = GetRandomValue(0, screenWidth);
            positions[i].y = GetRandomValue(0, screenHeight);
        }
    }
    return positions;
}

