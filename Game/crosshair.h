#ifndef CROSSHAIR_H
#define CROSSHAIR_H

#include "raylib.h"

struct Crosshair {
    Vector2 position;
    Texture2D texture;
};


Crosshair InitCrosshair();
void UpdateCrosshair(Crosshair& crosshair);
void DrawCrosshair(Crosshair& crosshair);

#endif 
