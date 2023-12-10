#include <window.hpp>

void Window::ActionPool::push(Action* action)
{
    pool.push(action);
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

void Window::durationActing()
{
    if(duration_pool.empty()) return ;
    Action* action = duration_pool.pop();

    action->execute();
    if(action->getRepeat() > 0) 
        duration_pool.push(action);
    else delete action;
}
