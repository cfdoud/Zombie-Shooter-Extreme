#include "bullet.h"
#include "raylib.h"

// Function to initialize a bullet with a given position, velocity, and texture
Bullet InitBullet(Vector2 position, Vector2 velocity, Texture2D texture) {
    Bullet bullet;
    bullet.position = position;
    bullet.velocity = velocity;
    bullet.texture = texture;
    return bullet;
}

// Function to update the position of a bullet
void UpdateBullet(Bullet& bullet) {
    bullet.position.x += bullet.velocity.x;
    bullet.position.y += bullet.velocity.y;
}

// Function to draw a bullet on the screen
void DrawBullet(Bullet& bullet) {
    DrawTexture(bullet.texture, bullet.position.x, bullet.position.y, WHITE);
}
