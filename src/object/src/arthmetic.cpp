#include "container.hpp"
#include <object.hpp>
int id = 0;
Action* Object::react() 
{
    if(!IsKeyDown(KEY_SPACE)) return nullptr;
    if(currentDelay != -1)
    {
        if(std::chrono::steady_clock::now() - lastAction < actionDelay[currentDelay]) 
            return nullptr;
    }
    id %= actions[0].size();
    currentDelay = id;
    lastAction = std::chrono::steady_clock::now();

    return actions[0][id++]->clone();
}

void Object::draw()
{
    Container::draw();
    return ;
}
