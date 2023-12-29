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
    std::lock_guard<std::mutex> lock(status_mtx);
    status = b;
}

bool Window::WinContent::getStatus() 
{
    std::lock_guard<std::mutex> lock(status_mtx);
    return status;
}

void Window::WinContent::setInputClock2Now()
{
    std::lock_guard<std::mutex> lock(input_mtx);
    input_clock = std::chrono::steady_clock::now();
}

void Window::WinContent::setRuntimeClock2Now()
{
    std::lock_guard<std::mutex> lock(runtime_mtx);
    runtime_clock = std::chrono::steady_clock::time_point();
}

bool Window::WinContent::isInputDelayOver() 
{
    std::lock_guard<std::mutex> lock(input_mtx);
    return std::chrono::steady_clock::now() - input_clock > input_delay;
}

bool Window::WinContent::isRuntimeDelayOver() 
{
    std::lock_guard<std::mutex> lock(runtime_mtx);
    return std::chrono::steady_clock::now() - runtime_clock > runtime_delay;
}

