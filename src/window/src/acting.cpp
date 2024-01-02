#include <const/request.hpp>
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
    delete action;

    for(Action*& a : unpacked)
    {
        pool.push(a);
    }

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
    while(isRun()) 
    {
        Action* action = request_pool.pop();
        if(action == nullptr) continue;
        if(!isRun()) break;
        switch(action->isRequest())
        {
            case (REQUEST::ID::NONE):
                break;
            case (REQUEST::ID::INVALID): 
                break;
            case (REQUEST::ID::CHANGE_INF): 
                {
                    UI.top()->pause();
                    std::string id = action->getArgs().getInterfaceName();
                    UI.push(id);
                    UI.top()->cont();
                    break;
                }
            case (REQUEST::ID::POP_THEN_CHANGE_INF): 
                {
                    UI.top()->pause();
                    UI.pop();
                    std::string id = action->getArgs().getInterfaceName();
                    UI.push(id);
                    UI.top()->cont();
                    break;
                }
            case (REQUEST::ID::POP_INF): 
                {
                    UI.top()->pause();
                    UI.pop();
                    UI.top()->cont();
                    break;
                }
            case (REQUEST::ID::LOSE): 
                {
                    // UI.top()->reset();
                    // break;
                    
                    UI.top()->pause();
                    UI.top()->reset();
                    std::string id = "gameover";
                    std::this_thread::sleep_for(std::chrono::milliseconds(200));
                    UI.push(id);
                    UI.top()->cont();
                
                    break;
                }
            default: 
                break;
        };

        delete action;
    }
}
