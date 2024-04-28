#ifndef CHARACTER_H
#define CHARACTER_H
#include "raylib.h"
#include "raymath.h"

class Character {
    Texture2D character = {};
    Rectangle charRect = {};
    Vector2 charPos = {};
    int frames = 0;

public:
    Character() = default;
    ~Character() = default;

    void setRectangle(int x, int y, int width, int height) {
        charRect.x = x;
        charRect.y = y;
        charRect.width = width;
        charRect.height = height;

    }
    void setFrame(int fr) { frames = fr; }
    void setRectangleX(int x) { charRect.x = x; }
    void setRectangleY(int y) { charRect.y = y; }
    void setRectangleWidth(int width) { charRect.width = width; }
    void setRectangleWidthChange(int width) { charRect.width *= width; }
    void setRectangleWidthChangePos() { charRect.width = abs(charRect.width); }
    void setRectangleHeight(int height) { charRect.height = height; }

    void setVector(int x, int y) {
        charPos.x = x;
        charPos.y = y;
    }
    void setVectorX(int x) { charPos.x = x; }
    void setVectorY(int y) { charPos.y = y; }
    void setVectorXMove(int x) { charPos.x += x; }
    void setVectorYMove(int y) { charPos.y += y; }
    void setChar(Texture2D c) { character = c; }

    Texture2D getCharacter() {
        return character;
    }
    Rectangle getCharRect() {
        return charRect;
    }
    Vector2 getCharPos() {
        return charPos;
    }

    int getFrame() {
        return frames;
    }
    int getCharacterWidth() {
        return character.width;
    }
    int getCharacterHeight() {
        return character.height;
    }
    int getRectangleWidth() { return charRect.width; }


};

#endif // !CHARACTER_H