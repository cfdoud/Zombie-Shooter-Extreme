#ifndef LOGIC_H
#define LOGIC_H

#include <cmath>

bool collision(int playerRadius, int aiRaidius, float* playerVector, float* aiVector) {
    if (fabs(aiVector[0] - playerVector[0]) <= (playerRadius + aiRaidius + aiRaidius) && fabs(aiVector[1] - playerVector[1]) <= (playerRadius + aiRaidius)) {
        return true;
    }
    return false;
}

bool collisionBulletEnemy(int bulletRadius, int enemyRadius, float* bulletX, float* bulletY, float* enemyX, float* enemyY) {
    // Calculate the distance between the bullet and the enemy using Pythagoras' theorem
    float distanceX = *bulletX - *enemyX;
    float distanceY = *bulletY - *enemyY;
    float distanceSquared = distanceX * distanceX + distanceY * distanceY;

    // Check if the distance is less than the sum of the radii squared
    float combinedRadius = bulletRadius + enemyRadius;
    float combinedRadiusSquared = combinedRadius * combinedRadius;
    if (distanceSquared <= combinedRadiusSquared) {
        return true; // Collision detected
    }
    return false; // No collision
}


#endif
