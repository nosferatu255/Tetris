#pragma once

#include "grid.h"
#include <random>

class Game
{
public:
    Game();
    ~Game();
    void Draw();
    void Draw(const int& offsetX, const int& offsetY);
    void HandleInput();
    void MoveShapeDown();

    bool gameRunning;
    int score;
    Music music;
private:
    bool IsShapeOutside();
    void RotateShape();
    void LockShape();
    bool ShapeFits();
    void Reset();
    void UpdateScore(const int& rowsCleared);
    void MoveShapeLeft();
    void MoveShapeRight();
    Shape GetRandomShape();
    std::vector<Shape> GetAllShapes();

    Grid grid;
    std::vector<Shape> shapes;
    Shape currentShape;
    Shape nextShape;
    Sound scoreSound, gameOverSound;
};