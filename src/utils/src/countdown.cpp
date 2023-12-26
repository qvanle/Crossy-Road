#include <countdown.hpp>

CountDown::CountDown(int milliseconds) 
{
    start = std::chrono::system_clock::now();
    finished = false;
    elapsed_seconds = std::chrono::milliseconds(milliseconds);
}

CountDown::~CountDown() 
{
}

bool CountDown::isFinished() 
{
    return finished || (std::chrono::system_clock::now() - start) > elapsed_seconds;
}

void CountDown::run() 
{
    finished = false;
    start = std::chrono::system_clock::now();
}

int CountDown::get() 
{
    return elapsed_seconds.count() * 1000;
}
