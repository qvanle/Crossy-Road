#include "raylib.h"
#include <window.hpp>

void Window::run()
{
    while (isRun())
    {
        draw();
        sound_effect();
        getUserEvent();
        getRuntimeEvent();
        update();
    }
}

void Window::draw()
{
    // clear screen 
    BeginDrawing();
    ClearBackground(WHITE);
    DrawTexture(
            *((Texture2D*)texturesStorage["background"]),
            0, 0, WHITE);
    EndDrawing();
    
}

void Window::getUserEvent()
{
    // Esc to exit 
    if (IsKeyPressed(KEY_ESCAPE))
    {
        status = false;
    }

    if (WindowShouldClose())
    {
        status = false;
    }
}

void Window::getRuntimeEvent()
{
    // do nothing 
}

void Window::update()
{
    // do nothing
}

void Window::sound_effect()
{
    // do nothing
}

bool Window::isRun()
{
    return status;
}

bool Window::isClose()
{
    return !status;
}
