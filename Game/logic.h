#ifndef LOGIC_H
#define LOGIC_H

#include <cmath>
#include <raymath.h>
#include <raylib.h>

bool collision(int playerRadius, int aiRaidius, float* playerVector, float* aiVector) {
    if (fabs(aiVector[0] - playerVector[0]) <= (playerRadius + aiRaidius + aiRaidius) && fabs(aiVector[1] - playerVector[1]) <= (playerRadius + aiRaidius)) {
        return true;
    }
    return false;
}

Vector2 GenerateRandomPosition(int screenWidth, int screenHeight) {
    return { (float)(GetRandomValue(0, screenWidth)), (float)(GetRandomValue(0, screenHeight)) };
}

//void UpdateEnemyPosition(Vector2& enemyPos, float* playerVector, int iRand, float aiSpeed) {
//    
//
//}


#endif
