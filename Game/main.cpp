#include "raylib.h"
#include "raymath.h"
#include <ctime>
#include <cstdlib>
#include "fonts.h"
#include <iostream>
#include "logic.h"
#include "crosshair.h"
#include "hero.h"
#include "bullet.h"
#include "enemy.h"
#include "vector"
#include <sstream>


#define MAX_FONTS 4
using namespace std;
#define MAX_INPUT_CHARS 12;

typedef enum GameScreen {
    LOGO = 0,
    TITLE,
    GAMEPLAY,
    ENDING,
    EASTEREGG
} GameScreen;
// GameScreen currentScreen = LOGO;
static const int screenWidth = 1920;
static const int screenHeight = 1080;
static const int screenMidX = 960;
static const int screenMidY = 540;

// static GameScreen transition = UNKNOWN;
bool enemyHit = false;

// currentScreen = LOGO;
Font font = { 0 };
Music music = { 0 };
Sound fxScary = { 0 };

// stuff for transtion screen
static void changeScreen(int screen); // Change to screen, no transition effect
static void transistion(int screen);  // Request transition to next screen
static void updateScreen(void);       // Update transition effect
static void
DrawTransition(void); // Draw transition effect (full-screen rectangle)
static void UpdateDrawFrame(void); // Update and draw one frame
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
void enemyMove(int x, int y) {}

int main(void) {

    int enemyCount = 1;
    // Initialization
    //--------------------------------------------------------------------------------------
    Rectangle screen = { 0, 0, screenWidth, screenHeight };
    InitWindow(screenWidth, screenHeight, "UnDead Knight");
    HideCursor();
    InitAudioDevice();
    GameScreen currentScreen = LOGO;

    int framesCounter = 0;
    int enemyframesCounter = 0;

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Load texture
    Sound sound = LoadSound("sound.wav");
    Sound gameStart = LoadSound("start.wav");
    int currentFrame = 0;
    int enemycurrentFrame = 0;
    Crosshair crosshair;
    crosshair = InitCrosshair();
    Texture2D bulletTexture = LoadTexture("bullet.png");

    // Fonts
    Font fonts[MAX_FONTS] = { 0 };
    fonts[1] = LoadFont("coolfont.png");
    // background
    float scrollingBack = 0.0f;


    Texture2D Graveyard = LoadTexture("map.png");
    Texture2D titleScreen = LoadTexture("TITLE.png");
    Texture2D endScreen = LoadTexture("dead.png");
    if (scrollingBack <= -Graveyard.width * 2)
        scrollingBack = 0;
    Texture2D background = LoadTexture("Ending.jpeg");
    Texture2D logo = LoadTexture("logo.png");


    // Enemy Texture
    int enemyframesSpeed = 8;
    Texture2D enemy = LoadTexture("zombie.png");

    Resources font;//font stuff
    int fSpace = font.getSpacings();
    int fType = font.getType();

    Vector2 title;
    title = MeasureTextEx(fonts[1], "Zombie Survival", 250, fSpace);
    title.x = 300;
    title.y = 540;

    Character hero;
    hero.setFrame(8);
    hero.setChar(LoadTexture("hero.png"));
    hero.setRectangle(0, 0, hero.getCharacterWidth() / 6,
        hero.getCharacterHeight());
    hero.setVector(screenWidth / 2 - hero.getRectangleWidth() / 2,
        screenWidth / 2 - hero.getCharacterWidth() / 2);

    //Enemy parameters, width, "hitbox", and such
    Rectangle enemyRec;
    enemyRec.width = enemy.width / 6; 
    enemyRec.height = enemy.height;
    enemyRec.x = 0;
    enemyRec.y = 0;
   


    Vector2 enemyPos;
    enemyPos.x = screenWidth - enemyRec.width;
    enemyPos.y = screenHeight - enemyRec.height;
 


    Vector2 enemyPositions[10];

    Vector2 bulletPosition = { screenWidth / 2.0f, screenHeight / 2.0f };
    Vector2 bulletVelocity = { 5.0f, 0.0f }; // Example velocity
    Bullet bullet = InitBullet(bulletPosition, bulletVelocity, bulletTexture);
    Bullet* bullets = NULL;
    int bulletCount = 0;
    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        DrawCrosshair(crosshair);
        UpdateCrosshair(crosshair);
        

        switch (currentScreen) {
        case LOGO: {
            DrawTexture(logo, 800, 300, WHITE);
            // TODO: Update LOGO screen variables here!
            framesCounter++; // Count frames

            // Wait for 2 seconds (120 frames) before jumping to TITLE screen
            if (framesCounter > 300) {
                // InitTitleScreen();
                currentScreen = TITLE;
            }

        } break;
        case TITLE: {
            // TODO: Update TITLE screen variables here!
            DrawTexture(titleScreen, 0, 0, WHITE);
            // Press enter to change to GAMEPLAY screen
            if (IsKeyPressed(KEY_SPACE)) {
                PlaySound(gameStart);
                // InitTitleScreen();
                currentScreen = GAMEPLAY;
            }

        } break;
        case GAMEPLAY: {

            UpdateCrosshair(crosshair);
            UpdateBullet(bullet);
            DrawTexture(Graveyard, 0, 0, WHITE);
          
            enemyframesCounter++;
            framesCounter++;
            // COLLISION DETECTION
            float x[2] = { enemyPos.x, enemyPos.y };
            // float y[2] = { heroPos.x, heroPos.y };
            float y[2] = { hero.getCharPos().x, hero.getCharPos().y };
            if (collision(27, 27, x, y)) {
                PlaySound(sound);
                currentScreen = ENDING;
            }

            if (framesCounter >= (60 / hero.getFrame())) {
                framesCounter = 0;
                currentFrame++;

                if (currentFrame > 5)
                    currentFrame = 0;
                hero.setRectangleX(currentFrame * hero.getRectangleWidth());
            }
            if (enemyframesCounter >= (60 / enemyframesSpeed)) {
                enemyframesCounter = 0;
                enemycurrentFrame++;

                if (enemycurrentFrame > 5)
                    enemycurrentFrame = 0;

                enemyRec.x = enemycurrentFrame * enemy.width / 6;
            }
            // DrawTextureRec(h.getCharacter(), heroRec, heroPos, WHITE);
            DrawTextureRec(hero.getCharacter(), hero.getCharRect(), hero.getCharPos(),
                WHITE);
            DrawTextureRec(enemy, enemyRec, enemyPos, WHITE);
            if (enemyHit == true) {
                enemyCount++;
                cout << "enemy hit = " << enemyCount << endl;
                for (int i = 0; i < enemyCount; i++) {
                    enemyPositions[i] = GenerateRandomPosition(screenWidth, screenHeight);
                }

                enemyHit = false;
                // Exit the loop since we already hit the enemy
            }

            for (int i = 0; i < enemyCount; i++) {
                DrawTextureRec(enemy, enemyRec, enemyPositions[i], WHITE);
                cout << "enemy needs to be redrawn" << enemyCount << endl;
            }

            // COLLISION DETECTION

            // Press enter to change to ENDING screen
            if (IsKeyPressed(KEY_ENTER)) {
                currentScreen = ENDING;
            }
            if (IsKeyDown(KEY_D)) {
                // heroPos.x += 4.0f;
                hero.setVectorXMove(4);
                // hero.width = abs(hero.width);
                hero.setRectangleWidthChangePos();
            }

            if (IsKeyDown(KEY_A)) {
                // heroPos.x -= 4.0f;
                hero.setVectorXMove(-4);
                if (hero.getRectangleWidth() > 0) {
                    hero.setRectangleWidthChange(-1);
                }
              
            }
            if (IsKeyDown(KEY_W))
                hero.setVectorYMove(-4);
            if (IsKeyDown(KEY_S))
                hero.setVectorYMove(4);


            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                Vector2 direction = Vector2Normalize(
                    Vector2Subtract(crosshair.position, hero.getCharPos()));

                Vector2 bulletVelocity = Vector2Scale(direction, 10);

              
            }

            //  BeginDrawing();

            srand(time(0));

            int iRand = (rand() % 11) + 1;
            int towardsPlayer = (rand() % 2);
            float aiSpeed = 3.5f;

           

            for (int i = 0; i < enemyCount; i++) {
                srand(time(NULL) + iRand);
                iRand = (rand() % 11) + 1;
                towardsPlayer = (rand() % 2);
                if (towardsPlayer == 0) {
                    if (enemyPositions[i].x <= hero.getCharPos().x) {
                        enemyPositions[i].x += aiSpeed;
                    }
                    else {
                        enemyPositions[i].x -= aiSpeed;
                    }
                }
                else {
                    if (enemyPositions[i].y <= hero.getCharPos().y) {
                        enemyPositions[i].y += aiSpeed;

                    }
                    else {
                        enemyPositions[i].y -= aiSpeed;
                    }
                }
            }

            srand(time(NULL) + iRand);

            if (towardsPlayer == 0) {
                if (enemyPos.x <= hero.getCharPos().x) {
                    enemyPos.x += aiSpeed;
                    enemy.width = abs(enemy.width);
                }
                else {
                    enemyPos.x -= aiSpeed;
                    if (enemy.width > 0) {
                        enemy.width *= -1;
                    }
                }
                if (iRand == 2 || iRand == 8 ||
                    iRand == 12 && enemyPos.y <= hero.getCharPos().y)
                    enemyPos.y -= aiSpeed;
                else if (iRand == 9 || iRand == 10 ||
                    iRand == 0 && enemyPos.y <= hero.getCharPos().y)
                    enemyPos.y += aiSpeed;
            }
            else {
                if (enemyPos.y <= hero.getCharPos().y)
                    enemyPos.y += aiSpeed;
                else
                    enemyPos.y -= aiSpeed;
                if (iRand == 4 || iRand == 1 ||
                    iRand == 6 && enemyPos.x <= hero.getCharPos().x) {
                    enemyPos.x += aiSpeed;
                    enemy.width = abs(enemy.width);
                }
                else if (iRand == 11 || iRand == 5 ||
                    iRand == 3 && enemyPos.x <= hero.getCharPos().x) {
                    enemyPos.x -= aiSpeed;
                    if (enemy.width > 0) {
                        enemy.width *= -1;
                    }
                }
            }

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                // Calculate direction vector from player to crosshair
                Vector2 direction = Vector2Normalize(
                    Vector2Subtract(crosshair.position, hero.getCharPos()));

                // Set initial bullet velocity based on direction
                Vector2 bulletVelocity =
                    Vector2Scale(direction, 10); // Adjust the bullet speed as needed

                // Reallocate memory for bullets
                Bullet* newBullets = (Bullet*)realloc(bullets, (bulletCount + 1) * sizeof(Bullet));
                if (newBullets == NULL) {
                    
                    cout << "Error: Failed to allocate memory for bullets!" << endl;
                    CloseWindow();
                }
                else {
                    bullets = newBullets;

                    bullets[bulletCount] = InitBullet(hero.getCharPos(), bulletVelocity, bulletTexture);
                    bulletCount++;
                }
            }

            // Update and draw bullets
            for (int i = 0; i < bulletCount; i++) {
                UpdateBullet(bullets[i]);
                float z[2] = { bullets[i].position.x, bullets[i].position.y };

                // Remove bullets that go off-screen
                if (bullets[i].position.x > screenWidth ||
                    bullets[i].position.y > screenHeight || bullets[i].position.x < 0 ||
                    bullets[i].position.y < 0) {
                    // Remove bullet from array
                    for (int j = i; j < bulletCount - 1; j++) {
                        bullets[j] = bullets[j + 1];
                    }
                    bulletCount--;
                    bullets = (Bullet*)realloc(bullets, bulletCount * sizeof(Bullet));

                    i--; // Update loop index
                }
                for(int j = 0; j < enemyCount; j++){
                float enemyPos[2] = { enemyPositions[j].x, enemyPositions[j].y };
                if (collision(10, 27, z, x) || collision(10, 27, z, enemyPos)) {
                    PlaySound(sound);
                    cout << "Enemy has been hit" << endl;
                    enemyHit = true;
                    for (int j = i; j < bulletCount - 1; j++) {
                        bullets[j] = bullets[j + 1];
                    }
                    bulletCount--;
                    bullets = (Bullet*)realloc(bullets, bulletCount * sizeof(Bullet));

                    // Update loop index
                    i--;
                }
             }
         }

            

            // Draw bullets
            for (int i = 0; i < bulletCount; i++) {
                DrawBullet(bullets[i]);
            }

            if (enemyPos.x > screenWidth - 100) {
                enemyPos.x = screenWidth - 100;
            }
            else if (enemyPos.x < 0) {
                enemyPos.x = 0;
            }

            if (enemyPos.y > screenHeight - 350) {
                enemyPos.y = screenHeight - 350;
            }
            else if (enemyPos.y < 0) {
                enemyPos.y = 0;
            }

            ClearBackground(RAYWHITE);
            

        } break;
        case ENDING: {
            DrawTexture(endScreen, 0, 0, WHITE);
            
            if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP)) {
                currentScreen = TITLE;
            }
        } break;
        
        default:
            break;
        }
        

       
        
        BeginDrawing();

        // ClearBackground(WHITE);
        ClearBackground(GetColor(0x052c46ff));

        switch (currentScreen) {
        case LOGO: {
            // TODO: Draw LOGO screen here!
            DrawText("Loading Textures . . .", 20, 20, 40, WHITE);
            DrawText("Please WAIT...", 1920, 1080, 50, WHITE);

        } break;
        case TITLE: { //draw Title screen
            DrawTextEx(fonts[fType], "Zombie Shooter", title, 80, fSpace, VIOLET);
            DrawText("PRESS SPACE to ENTER", 500, 640, 50, YELLOW);

        } break;
        case GAMEPLAY: {
            DrawBullet(bullet);
            DrawCrosshair(crosshair);

            // DrawTextureRec(hero, hazmatRec, heroPos, WHITE);
        } break;
        case ENDING: {
            // TODO: Draw ENDING screen here!
            
            //DrawRectangle(0, 0, screenWidth, screenHeight, RED);
            //DrawText("YOU ARE DEAD", 20, 20, 40, DARKBLUE);
            DrawText(("High-Score of " + to_string(enemyCount)).c_str(), 800, 500, 40, DARKBLUE);
            DrawText("PRESS ESC	TO QUIT", 120, 220, 20, DARKBLUE);
            
        } break;
        

        default:
            break;
        }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------

    // TODO: Unload all loaded data (textures, fonts, audio) here!
    UnloadTexture(enemy);
    UnloadTexture(background);
    UnloadTexture(Graveyard);
    UnloadTexture(logo);
    UnloadTexture(titleScreen);
    UnloadSound(gameStart);
    UnloadTexture(crosshair.texture);
    UnloadTexture(bulletTexture);
    UnloadTexture(endScreen);
    free(bullets);
    // ClearBackground(background);
    // UnloadTexture(background);
    UnloadSound(sound);
    CloseAudioDevice();
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}