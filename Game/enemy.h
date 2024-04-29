#ifndef ENEMY_H
#define ENEMY_H

#include "raylib.h"

struct Enemy
{
    Vector2 position;
    float speed;
    int width;
    // Add more properties as needed
};


Vector2* GenerateRandomPositions(int count, int screenWidth, int screenHeight);

#endif