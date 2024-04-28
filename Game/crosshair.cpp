#include "crosshair.h"
#include "raylib.h"
#include "raymath.h"


using namespace std;

Crosshair InitCrosshair() {
	Crosshair crosshair;
	crosshair.position = { 0, 0 };
	crosshair.texture = LoadTexture("crosshair1.png");
	return crosshair;
}

void UpdateCrosshair(Crosshair& crosshair) {
    
    Vector2 mousePos = GetMousePosition();
	crosshair.position = mousePos;
  
}

void DrawCrosshair(Crosshair& crosshair) {
	DrawTexture(crosshair.texture, crosshair.position.x, crosshair.position.y, WHITE);
}