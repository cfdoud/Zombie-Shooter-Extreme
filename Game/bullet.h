#ifndef BULLET_H
#define BULLET_H

#include "raylib.h"

struct Bullet
{
    Vector2 position;
    Vector2 velocity;
    Texture2D texture;

};

Bullet InitBullet(Vector2 position, Vector2 velocity, Texture2D texture);
void UpdateBullet(Bullet& bullet);
void DrawBullet(Bullet& bullet);


#endif // BULLET_H
