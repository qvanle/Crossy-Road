#include "raylib.h"
#include <window.hpp>

void Window::run()
{
    last_frame = std::chrono::system_clock::now();
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
    ClearBackground(BLACK);
    obj->draw();
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
    std::chrono::duration<double> elapsed_seconds = std::chrono::system_clock::now() - last_frame;
    if(elapsed_seconds.count() >= 1.0)
    {
        last_frame = std::chrono::system_clock::now();
        obj->nextTexture();
    }
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
