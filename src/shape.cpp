#include "shape.h"

Shape::Shape()
{
    cellSize = 30;
    rotationState = 0;
    colors = GetCellColors();
    rowOffset = 0;
    columnOffset = 0;
}

// Draws the shape on the grid
void Shape::Draw()
{
    std::vector<Position> tiles = GetCellPositions();
    for(Position tile : tiles)
    {
        DrawRectangle(tile.column * cellSize + 11, tile.row * cellSize + 11, cellSize - 1, cellSize - 1, colors[id]);
    }
}

void Shape::Draw(const int& offsetX, const int& offsetY)
{
    std::vector<Position> tiles = GetCellPositions();
    for(Position tile : tiles)
    {
        DrawRectangle(tile.column * cellSize + offsetX, tile.row * cellSize + offsetY, cellSize - 1, cellSize - 1, colors[id]);
    }
}

// Moves the shape to the new coordinates specified as arguments
void Shape::Move(const int& rows, const int& columns)
{
    rowOffset += rows;
    columnOffset += columns;
}

// Returns a vector of all shapes cells positions
std::vector<Position> Shape::GetCellPositions()
{
    std::vector<Position> tiles = cells[rotationState];
    std::vector<Position> movedTiles;
    for(Position tile: tiles)
    {
        Position newPos = Position(tile.row + rowOffset, tile.column + columnOffset);
        movedTiles.push_back(newPos);
    }
    return movedTiles;
}

// Rotates the shape
void Shape::Rotate()
{
    rotationState++;
    if(rotationState == cells.size())
    {
        rotationState = 0;
    }
}

// If the shape ends up in an ilegal position after rotation undo the rotation
void Shape::UndoRotation()
{
    rotationState--;
    if(rotationState == -1)
    {
        rotationState = cells.size() - 1;
    }
}