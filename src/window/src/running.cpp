#include "raylib.h"
#include <window.hpp>

void Window::run() {
    // last_chrismas = now() 
    Wcontent.input_clock = std::chrono::steady_clock::now();
    while (isRun())
    {
        draw();
        sound_effect();
        getUserEvent();
        getRuntimeEvent();
        immediateActing();
    }
}

void Window::draw()
{
    // clear screen 
    BeginDrawing();
    ClearBackground(BLACK);
    UI.draw();
    // test draw button
    button->draw();
    EndDrawing();
    
}

void Window::getUserEvent()
{
    // do nothing if input_delay is not finish 
    if( Wcontent.input_delay >  std::chrono::steady_clock::now() - Wcontent.input_clock)
    {
        return ;
    }
    Wcontent.input_clock = std::chrono::steady_clock::now();
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
    
    Action* action = UI.react();
    if(action != nullptr) 
    {
        if(!action->isRequest()) 
            immediate_pool.push(action);
    }

    // button event
    button->handleEvents();
    button->update();
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
    return Wcontent.status;
}

bool Window::isClose()
{
    return !Wcontent.status;
}
