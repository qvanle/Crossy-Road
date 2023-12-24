#include <window.hpp>

void Window::ActionPool::push(Action* action)
{
    std::lock_guard<std::mutex> lock(mtx);
    pool.push(action);
}

void Window::ActionPool::push(PacketAction* action)
{
    std::lock_guard<std::mutex> lock(mtx);
    std::vector<Action*> unpacked = action->unpack();
    for(Action* a : unpacked)
        pool.push(a);
}

Window::ActionPool::~ActionPool()
{
    while(!pool.empty())
    {
        delete pool.front();
        pool.pop();
    }
}

Action* Window::ActionPool::front()
{
    std::lock_guard<std::mutex> lock(mtx);
    return pool.front();
}

Action* Window::ActionPool::pop()
{
    std::lock_guard<std::mutex> lock(mtx);
    Action* action = pool.front();
    pool.pop();
    return action;
}

bool Window::ActionPool::empty() 
{
    std::lock_guard<std::mutex> lock(mtx);
    return pool.empty();
}


void Window::immediateActing()
{
    while(isRun())
    {
        if(immediate_pool.empty()) continue;
        Action* action = immediate_pool.pop();

        action->execute();
        delete action;
    }
}

void Window::userActing()
{
    while(isRun())
    {
        if(immediate_user_pool.empty()) continue;
        Action* action = immediate_user_pool.pop();

        action->execute();
        delete action;
    }
}

void Window::systemActing()
{
    {
        if(system_pool.empty()) return ;
        Action* action = system_pool.pop();
        action->execute();
        delete action;
    }
}

void Window::requestActing()
{
    return ;
}
