#include <window.hpp>

Window::WinContent::~WinContent() 
{
    for(std::thread &i : thread_pool) 
    {
        if(i.joinable()) 
            i.join();
    }
}


void Window::WinContent::setStatus(bool b)
{
    status = b;
}

bool Window::WinContent::getStatus() const
{
    return status;
}

void Window::WinContent::setInputClock2Now()
{
    input_clock = std::chrono::steady_clock::now();
}

void Window::WinContent::setRuntimeClock2Now()
{
    runtime_clock = std::chrono::steady_clock::time_point();
}

bool Window::WinContent::isInputDelayOver() const
{
    return std::chrono::steady_clock::now() - input_clock > input_delay;
}

bool Window::WinContent::isRuntimeDelayOver() const
{
    return std::chrono::steady_clock::now() - runtime_clock > runtime_delay;
}

