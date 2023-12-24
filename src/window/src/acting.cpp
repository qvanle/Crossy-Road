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
    while(pop() != nullptr);
}

Action* Window::ActionPool::front()
{
    std::lock_guard<std::mutex> lock(mtx);
    return pool.front();
}

Action* Window::ActionPool::pop()
{
    std::lock_guard<std::mutex> lock(mtx);
    if(pool.empty()) return nullptr;
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
        Action* action = immediate_pool.pop();
        if(action == nullptr) continue;
        if(!isRun()) break;
        action->execute();
        delete action;
    }
}

void Window::userActing()
{
    while(isRun())
    {
        Action* action = immediate_user_pool.pop();
        if(action == nullptr) continue;
        if(!isRun()) break;
        action->execute();
        delete action;
    }
}

void Window::systemActing()
{
    {
        Action* action = system_pool.pop();
        if(action == nullptr) return;
        if(!isRun()) return;
        action->execute();
        delete action;
    }
}

void Window::requestActing()
{
    return ;
}
