#include "raylib.h"
#include <window.hpp>

void Window::run()
{
    // last_chrismas = now()
    Wcontent.setInputClock2Now();
    Wcontent.setRuntimeClock2Now();

    // Wcontent.thread_pool.push_back(std::thread(&Window::draw, this));
    Wcontent.thread_pool.push_back(std::thread(&Window::getUserEvent, this));
    Wcontent.thread_pool.push_back(std::thread(&Window::getRuntimeEvent, this));
    // Wcontent.thread_pool.push_back(std::thread(&Window::sound_effect, this));
    Wcontent.thread_pool.push_back(std::thread(&Window::userActing, this));
    // Wcontent.thread_pool.push_back(std::thread(&Window::userActing, this));
    Wcontent.thread_pool.push_back(std::thread(&Window::immediateActing, this));
    // Wcontent.thread_pool.push_back(std::thread(&Window::immediateActing, this));
    // Wcontent.thread_pool.push_back(std::thread(&Window::immediateActing, this));
    Wcontent.thread_pool.push_back(std::thread(&Window::requestActing, this));

    musicController.choose(0);
    musicController.play();

    while (isRun())
    {
        musicController.update();
        draw();
        systemEvent();
        systemActing();
        // getUserEvent();
        // getRuntimeEvent();
        // sound_effect();
        // userActing();
        // immediateActing();
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
        // highscore->save(PATB::INPUTBOX_ +"inputbox.yaml");
    }
}

void Window::draw()
{
    {
        BeginDrawing();
        UI.draw();
        inputBox->draw();
        if (isOver)
        {
            Rectangle rel = UI.top()->getFrame();
            // std::cout<<rel.x<<" "<<rel.y<<" "<<rel.width<<" "<<rel.height<<std::endl;
            rel.x = rel.width * 1;
            rel.y = rel.height * 0.8;
            rel.width *= 0.3;
            rel.height *= 0.12;
            
            DrawText(TextFormat("%08i", highscore->getScore()), rel.x, rel.y, 40, RED);
        }
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
    while (isRun())
    {
        if (!Wcontent.isInputDelayOver())
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            continue;
        }

        Action *action = UI.react();
        if (action != nullptr)
        {
            if (action->isPackage())
            {
                for (auto act : action->unpack())
                {
                    if (act->isRequest())
                        request_pool.push(act);
                    else
                        immediate_user_pool.push(act);
                }
            }
            else if (!action->isRequest())
                immediate_user_pool.push(action);
        }
        // test inputBox
        action = inputBox->react();
        if (action != nullptr)
        {
            if (!action->isRequest())
                immediate_user_pool.push(action);
        }

        action = inputBox->react();
        if (action != nullptr)
        {
            if (!action->isRequest())
                immediate_user_pool.push(action);
        }

        Wcontent.setInputClock2Now();
    }
}

void Window::getRuntimeEvent()
{
    while (isRun())
    {

        if (!Wcontent.isRuntimeDelayOver())
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            continue;
        }
        Action *action = UI.getRuntimeEvent();
        if (action != nullptr)
        {
            if (action->isPackage())
            {
                for (auto act : action->unpack())
                {
                    if (act->isRequest())
                        request_pool.push(act);
                    else
                        immediate_user_pool.push(act);
                }
            }
            else if (!action->isRequest())
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
