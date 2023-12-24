#include <window.hpp>

void Window::ActionPool::push(Action* action)
{
    pool.push(action);
}

void Window::ActionPool::push(PacketAction* action)
{
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
    return pool.front();
}

Action* Window::ActionPool::pop()
{
    Action* action = pool.front();
    pool.pop();
    return action;
}

bool Window::ActionPool::empty() const
{
    return pool.empty();
}


void Window::immediateActing()
{
    if(immediate_pool.empty()) return ;
    Action* action = immediate_pool.pop();
    
    action->execute();
    delete action;

}

void Window::userActing()
{
    if(immediate_user_pool.empty()) return ;
    Action* action = immediate_user_pool.pop();

    action->execute();
    delete action;
}

void Window::requestActing()
{
    return ;
}
