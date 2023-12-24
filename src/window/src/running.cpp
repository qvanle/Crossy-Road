#include "raylib.h"
#include <window.hpp>

void Window::run() {
    // last_chrismas = now() 
    Wcontent.setInputClock2Now();
    Wcontent.setRuntimeClock2Now();

    //Wcontent.thread_pool.push_back(std::thread(&Window::draw, this));
    Wcontent.thread_pool.push_back(std::thread(&Window::getUserEvent, this));
    Wcontent.thread_pool.push_back(std::thread(&Window::getRuntimeEvent, this));
    //Wcontent.thread_pool.push_back(std::thread(&Window::sound_effect, this));
    Wcontent.thread_pool.push_back(std::thread(&Window::userActing, this));
    Wcontent.thread_pool.push_back(std::thread(&Window::userActing, this));
    Wcontent.thread_pool.push_back(std::thread(&Window::userActing, this));
    Wcontent.thread_pool.push_back(std::thread(&Window::immediateActing, this));
    Wcontent.thread_pool.push_back(std::thread(&Window::immediateActing, this));
    Wcontent.thread_pool.push_back(std::thread(&Window::immediateActing, this));

    while (isRun())
    {
        draw();
        systemEvent();
        systemActing();
        //getUserEvent();
        //getRuntimeEvent();
        //sound_effect();
        //userActing();
        //immediateActing();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

void Window::draw()
{
    {
        BeginDrawing();
        UI.draw();
        EndDrawing();
    }

}

void Window::systemEvent() 
{
    {
        // alt + F4 to exit 
        if (IsKeyDown(KEY_LEFT_ALT) && IsKeyDown(KEY_F4))
        {
            system_pool.push(new CloseAction(this));
        }
        if (WindowShouldClose())
        {
            system_pool.push(new CloseAction(this));
        }

        if (IsWindowResized() && !IsWindowFullscreen())
        {
            int width = GetScreenWidth();
            int height = GetScreenHeight();
            system_pool.push(new resizeAction(this, width, height));
        }
    }
}

void Window::getUserEvent()
{
    while(isRun())
    {
        if(!Wcontent.isInputDelayOver())
        {
            continue;
        }

        PacketAction* action = UI.react();
        if(action != nullptr) 
        {
            if(!action->isRequest()) 
                immediate_user_pool.push(action);
        }

        Wcontent.setInputClock2Now();
    }
}

void Window::getRuntimeEvent()
{
    while(isRun())
    {

        if(!Wcontent.isRuntimeDelayOver())
        {
            continue;
        }
        PacketAction* action = UI.getRuntimeEvent();
        if(action != nullptr) 
        {
            immediate_pool.push(action);
        }
        Wcontent.setRuntimeClock2Now();
    }
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
