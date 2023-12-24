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
        userActing();
        immediateActing();
    }
}

void Window::draw()
{
    // clear screen 
    BeginDrawing();
    ClearBackground(BLACK);
    UI.draw();
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
        immediate_user_pool.push(new CloseAction(this));
    }
    if (WindowShouldClose())
    {
        immediate_user_pool.push(new CloseAction(this));
    }

    if (IsWindowResized() && !IsWindowFullscreen())
    {
        int width = GetScreenWidth();
        int height = GetScreenHeight();
        immediate_user_pool.push(new resizeAction(this, width, height));
    }
    
    PacketAction* action = UI.react();
    if(action != nullptr) 
    {
        if(!action->isRequest()) 
            immediate_user_pool.push(action);
    }

    // // button event
    // action = button->react();
    // if(action != nullptr) 
    // {
    //     if(!action->isRequest()) 
    //         {
    //             immediate_pool.push(action);
            
    //         }
    // }
}

void Window::getRuntimeEvent()
{
    if( Wcontent.runtime_delay >  std::chrono::steady_clock::now() - Wcontent.runtime_clock)
    {
        return ;
    }
    Wcontent.runtime_clock = std::chrono::steady_clock::now();
    Action* action = UI.getRuntimeEvent();
    if(action != nullptr) 
    {
        immediate_pool.push(action);
    }
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
