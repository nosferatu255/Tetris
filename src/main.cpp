#include <raylib.h>
#include "game.h"

double lastUpdateTime = 0;
 
bool EventTriggerd(double interval);

int main()
{
    InitWindow(500, 620, "Tetris");

    // Sets on how many FPS the game is going to run
    SetTargetFPS(60);

    Font font = LoadFontEx("font/LeadCoat-nAr.ttf", 64, 0, 0);

    Game game = Game();

    // When the ESC key is pressed end the loop
    while(WindowShouldClose() == false)
    {
        UpdateMusicStream(game.music);
        game.HandleInput();
        if(EventTriggerd(0.2))
        {
            game.MoveShapeDown();
        }
        BeginDrawing();
        ClearBackground(DARKGREEN);
        DrawTextEx(font, "Score", {365, 15}, 38, 2, WHITE);
        DrawTextEx(font, "Next", {370, 175}, 38, 2, WHITE);
        if(!game.gameRunning)
        {
            DrawTextEx(font, "GAME OVER", {320, 450}, 38, 2, WHITE);
        }
        DrawRectangleRounded({320, 55, 170, 60}, 0.3, 6, DARKPURPLE);
        
        char score[10];
        sprintf(score, "%d", game.score);
        Vector2 textSize = MeasureTextEx(font, score, 38, 2);
        DrawTextEx(font, score, {320 + (170 - textSize.x) / 2, 65}, 38, 2, WHITE);

        DrawTextEx(font, "Next", {370, 175}, 38, 2, WHITE);  
        DrawRectangleRounded({320, 215, 170, 180}, 0.3, 6, BLACK);
        game.Draw();
        EndDrawing();
    }

    CloseWindow();
}

bool EventTriggerd(double interval)
{
    double currentTime = GetTime();
    if(currentTime - lastUpdateTime >= interval)
    {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}