#include "game.h"
#include "shape_types.cpp"

Game::Game()
{
    grid = Grid();
    shapes = GetAllShapes();
    currentShape = GetRandomShape();
    nextShape = GetRandomShape();
    gameRunning = true;
    score = 0;
    InitAudioDevice();

    music = LoadMusicStream("sounds/music-loop.mp3");
    PlayMusicStream(music);

    gameOverSound = LoadSound("sounds/over-sound.mp3");
    scoreSound = LoadSound("sounds/score-sound.mp3");
}

Game::~Game()
{
    UnloadSound(gameOverSound);
    UnloadSound(scoreSound);
    UnloadMusicStream(music);
    CloseAudioDevice();
}

// Returns a random shape out of all the shape types
Shape Game::GetRandomShape()
{
    if(shapes.empty())
    {
        shapes = GetAllShapes();
    }
    int randomIndex = rand() % shapes.size();
    Shape shape = shapes[randomIndex];
    shapes.erase(shapes.begin() + randomIndex);
    return shape;
}

// Returns all the possible shapes in a vecotr
std::vector<Shape> Game::GetAllShapes()
{
    return {IShape(), JShape(), TShape(), OShape(), SShape(), ZShape()};
}

// Draws the game grid and draws the current shape on the grid
void Game::Draw()
{
    grid.Draw();
    currentShape.Draw(11, 11);
    switch (nextShape.id)
    {
    case 3:
        nextShape.Draw(255, 290);
        break;

    case 4:
        nextShape.Draw(255, 280);
        break;    
    
    default:
        nextShape.Draw(270, 270);
    }
}

// Handles the player's input 
void Game::HandleInput()
{
    int keyPressed = GetKeyPressed();
    if(!(gameRunning) && keyPressed != 0)
    {
        gameRunning = true;
        Reset();
    }
    switch (keyPressed)
    {
    case KEY_LEFT:
        MoveShapeLeft();
        break;

    case KEY_RIGHT:
        MoveShapeRight();
        break;

    case KEY_DOWN:
        MoveShapeDown();
        break;

    case KEY_R:
        RotateShape();
        break;

    default:
        break;
    }
}

// Moves the current shepe to the left
void Game::MoveShapeLeft()
{
    if(gameRunning)
    {
        currentShape.Move(0, -1);
        if(IsShapeOutside() || ShapeFits() == false)
        {
            currentShape.Move(0, 1);
        }
    }
}

// Moves the current shepe to the right
void Game::MoveShapeRight()
{
    if(gameRunning)
    {
        currentShape.Move(0, 1);
        if(IsShapeOutside() || ShapeFits() == false)
        {
            currentShape.Move(0, -1);
        }
    }
}

// Moves the current shepe down
void Game::MoveShapeDown()
{
    if(gameRunning)
    {
        currentShape.Move(1, 0);
        if(IsShapeOutside() || ShapeFits() == false)
        {
            currentShape.Move(-1, 0);
            LockShape();
        }
    }
}

// Checks  if the current shape is outside the game windows boundaries
bool Game::IsShapeOutside()
{
    std::vector<Position> tiles = currentShape.GetCellPositions();
    for(Position tile : tiles)
    {
        if(grid.IsCellOutside(tile.row, tile.column))
        {
            return true;
        } 
    }
    return false;
}

// Rotates the current shape
void Game::RotateShape()
{
    if(gameRunning)
    {
        currentShape.Rotate();
        if(IsShapeOutside() || ShapeFits() == false)
        {
            currentShape.UndoRotation();
        }
    }
}

// Once the shape raches the bottom of the screen it locks in place
void Game::LockShape()
{
    std::vector<Position> tiles = currentShape.GetCellPositions();
    for(Position tile : tiles)
    {
        grid.grid[tile.row][tile.column] = currentShape.id;
    }
    currentShape = nextShape;
    if(ShapeFits() == false)
    {
        gameRunning = false;
    }
    nextShape = GetRandomShape();
    int rowsCleared = grid.ClearFullRows();
    UpdateScore(rowsCleared);
}

// Check if a shape fits into the bracket that the user it trying to chenge its position to
bool Game::ShapeFits()
{
    std::vector<Position> tiles = currentShape.GetCellPositions();
    for(Position tile : tiles)
    {
        if(grid.IsCellEmpty(tile.row, tile.column) == false)
        {
            return false;
        } 
    }
    return true;
}

// Resets the game 
void Game::Reset()
{
    grid.Init();
    shapes = GetAllShapes();
    currentShape = GetRandomShape();
    nextShape = GetRandomShape();
    score = 0;
    PlaySound(gameOverSound);
}

// Updates the score when the player clears rows
void Game::UpdateScore(const int& rowsCleared)
{
    switch (rowsCleared)
    {
    case 1:
        score += 1;
        PlaySound(scoreSound);
        break;
    case 2:
        score += 2;
        PlaySound(scoreSound);
        break;

    case 3:
        score += 3;
        PlaySound(scoreSound);
        break;    
    
    default:
        break;
    }
}