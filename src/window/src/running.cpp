#include "raylib.h"
#include <window.hpp>

void Window::run() {
    // last_chrismas = now() 
    Wcontent.setInputClock2Now();
    Wcontent.setRuntimeClock2Now();
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
    if(!Wcontent.isInputDelayOver())
    {
        return ;
    }
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
    //
    Wcontent.setInputClock2Now();
}

void Window::getRuntimeEvent()
{
    if(!Wcontent.isRuntimeDelayOver())
    {
        return ;
    }
    Action* action = UI.getRuntimeEvent();
    if(action != nullptr) 
    {
        immediate_pool.push(action);
    }
    Wcontent.setRuntimeClock2Now();
}

void Window::sound_effect()
{
    // do nothing
}

bool Window::isRun()
{
    return Wcontent.getStatus();
}

bool Window::isClose()
{
    return !Wcontent.getStatus();
}
