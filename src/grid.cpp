#include "grid.h"

Grid::Grid()
{
    rows = 20;
    columns = 10;
    cellSize = 30;
    Init();
    colors = GetCellColors();
}

// Initialized the grid matrix values
void Grid::Init()
{
    for(int row = 0; row < rows; row++)
    {
        for(int column = 0; column < columns; column++)
        {
            grid[row][column] = 0;
        }
    }
}

// Prints the grid matrix values to the console
void Grid::Print()
{
    for(int row = 0; row < rows; row++)
    {
        for(int column = 0; column < columns; column++)
        {
            std::cout << grid[row][column] << " ";
        }
        std::cout << std::endl;
    }
}

// Draws the cells and fills them with color values
void Grid::Draw()
{
    for(int row = 0; row < rows; row++)
    {
        for(int column = 0; column < columns; column++)
        {
            int cellValue = grid[row][column];
            DrawRectangle(column * cellSize + 11, row * cellSize + 11, cellSize - 1, cellSize - 1, colors[cellValue]);
        }
    }
}

// Checks it the individual cell is outside the game window boundaries
bool Grid::IsCellOutside(const int& row, const int& column)
{
    if(row >= 0 && row < rows && column >= 0 && column < columns)
    { 
        return false;
    }
    else
    {
        return true;
    }
}

// Checks if the given cell is empty or equal to 0
bool Grid::IsCellEmpty(const int& row, const int& column)
{
    if(grid[row][column] == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Clears rows that are full of non 0 values
int Grid::ClearFullRows()
{
    int complete = 0;
    for(int row = rows - 1; row >=0; row--)
    {
        if(IsRowFull(row))
        {
            ClearRow(row);
            complete++;
        }
        else if(complete > 0)
        {
            MoveRowsDown(row, complete);
        }
    }
    return complete;
}

// Checks if the given row of the grid matrix has only non 0 values
bool Grid::IsRowFull(const int& row)
{
    for(int column = 0; column < columns; column++)
    {
        if(grid[row][column] == 0)
        {
            return false;
        }
    }
    return true;
}

// Clears the row 
void Grid::ClearRow(const int& row)
{
    for(int column = 0; column < columns; column++)
    {
        grid[row][column] = 0;
    }
}

// Moves the structure down when a row is filled
void Grid::MoveRowsDown(const int& row, const int& numRows)
{
    for(int column = 0; column < columns; column++)
    {
        grid[row + numRows][column] = grid[row][column];
    }
}