#include <window.hpp>

void Window::ActionPool::push(Action* action)
{
    pool.push(action);
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

void Window::requestActing()
{
    return ;
}
