#include "container.hpp"
#include <object.hpp>
Action* Object::react() 
{
    for(int i = 0; i < strokes.size(); i++)
    {
        Action* a = strokes[i]->react();
        if(a == nullptr) continue;
        if(i != currentDelay) strokes[i]->chooseAction(0);
        else strokes[i]->nextAction();
        currentDelay = i;
        lastAction = std::chrono::steady_clock::now();
        return a;
    }


    return nullptr;
}

void Object::draw()
{
    Container::draw();
    return ;
}
