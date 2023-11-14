#include "raylib.h"
#include <window.h>

Window::Window()
{
    width = 800;
    height = 600;
    title = "Default Title";
    InitWindow(width, height, title.c_str());
    SetTargetFPS(60);

    BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
    EndDrawing();

    std::this_thread::sleep_for(std::chrono::milliseconds(4000));
}

Window::~Window()
{
}
