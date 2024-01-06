#include <const/request.hpp>
#include <window.hpp>

void Window::ActionPool::push(Action* action)
{
    std::lock_guard<std::mutex> lock(mtx);
    if(stop) 
    {
        delete action; 
        return ;
    }
    pool.push(action);
}

void Window::ActionPool::push(PacketAction* action)
{
    std::lock_guard<std::mutex> lock(mtx);
    if(stop) 
    {
        delete action; 
        return ;
    }
    std::vector<Action*> unpacked = action->unpack();
    delete action;

    for(Action*& a : unpacked)
    {
        pool.push(a);
    }

}

void Window::ActionPool::clear() 
{
    std::lock_guard<std::mutex> lock(mtx);
    while(!pool.empty())
    {
        delete pool.front();
        pool.pop();
    }
}

void Window::ActionPool::stopReceiving()
{
    std::lock_guard<std::mutex> lock(mtx);
    stop = true;
}

void Window::ActionPool::continueReceiving()
{
    std::lock_guard<std::mutex> lock(mtx);
    stop = false;
}

Window::ActionPool::~ActionPool()
{
    clear();
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
    if(stop) return nullptr;
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
        immediate_user_pool.stopReceiving();
        immediate_pool.stopReceiving();
        request_pool.stopReceiving();
        system_pool.stopReceiving();


        immediate_user_pool.clear();
        immediate_pool.clear();
        request_pool.clear();
        system_pool.clear();
    
        std::this_thread::sleep_for(std::chrono::milliseconds(200));

        action->execute();
        delete action;

        immediate_user_pool.continueReceiving();
        immediate_pool.continueReceiving();
        request_pool.continueReceiving();
        system_pool.continueReceiving();

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
            case (REQUEST::ID::LOAD_GAME): 
                {
                    UI.push(lastGame);
                    std::this_thread::sleep_for(std::chrono::milliseconds(400));
                    UI.top()->cont();
                    break;
                }
            case (REQUEST::ID::SAVE_GAME): 
                {
                    UI.top()->pause();
                    UI.pop();
                    UI.top()->pause();
                    lastGame = UI.top()->getName();
                    UI.pop();
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
                    // inputBox->show();
                    UI.top()->pause();
                    UI.top()->reset();
                    std::string id = "gameover";
                    std::this_thread::sleep_for(std::chrono::milliseconds(200));
                    UI.push(id);
                    UI.top()->cont();
                    
                    break;
                }
            case (REQUEST::ID::TOGGLE_MUSIC): 
                {
                    musicController.toggle();
                    break;
                }
            default: 
                break;
        };

        delete action;
    }
}
