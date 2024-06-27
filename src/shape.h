#pragma once

#include <map>
#include "position.h"
#include "colors.h"

// Defines the basic functionality of shapes 
class Shape
{
public:
    Shape();
    void Draw();
    void Draw(const int& offsetX, const int& offsetY);
    void Move(const int& rows, const int& columns);
    std::vector<Position> GetCellPositions();
    void UndoRotation();
    void Rotate();

    // Shape id determines what type of shape will be assigned
    int id;
    // This map determines what cells are occupied in each state of individual shapes
    std::map<int, std::vector<Position>> cells;
private:
    int cellSize;
    int rotationState;
    std::vector<Color> colors;
    int rowOffset;
    int columnOffset;
};