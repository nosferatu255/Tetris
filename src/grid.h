#pragma once

#include <iostream>
#include "colors.h"
#include "shape.h"

// Defines the "game grid" as a matrix of integers where 
// the value 0 is an empty grid cell
class Grid
{
public:
    Grid();
    void Init();
    void Print();
    void Draw();
    bool IsCellOutside(const int& row, const int& column);
    bool IsCellEmpty(const int& row, const int& column);
    int ClearFullRows();

    int grid[20][10];
private:
    bool IsRowFull(const int& row);
    void ClearRow(const int& row);
    void MoveRowsDown(const int& row, const int& numRows);
    
    int rows;
    int columns;
    int cellSize;
    std::vector<Color> colors;
};   