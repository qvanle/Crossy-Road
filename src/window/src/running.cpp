#include "raylib.h"
#include <window.hpp>

void Window::run() {
    last_frame = std::chrono::system_clock::now();
    while (isRun())
    {
        draw();
        sound_effect();
        getUserEvent();
        getRuntimeEvent();
        immediateActing();
        durationActing();
    }
}

void Window::draw()
{
    // clear screen 
    BeginDrawing();
    ClearBackground(BLACK);
    interface->draw();
    EndDrawing();
    
}

void Window::getUserEvent()
{
    // alt + F4 to exit 
    if (IsKeyDown(KEY_LEFT_ALT) && IsKeyDown(KEY_F4))
    {
        immediate_pool.push(new CloseAction(this));
    }
    if (WindowShouldClose())
    {
        immediate_pool.push(new CloseAction(this));
    }

    if (IsWindowResized() && !IsWindowFullscreen())
    {
        int width = GetScreenWidth();
        int height = GetScreenHeight();
        immediate_pool.push(new resizeAction(this, width, height));
    }
    Action* action = interface->react();
    if(action != nullptr) 
    {
        if(action->getRepeat() > 1) 
            duration_pool.push(action);
        else if(action->getRepeat() == 1) 
            immediate_pool.push(action);
    }
}

void Window::getRuntimeEvent()
{
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
