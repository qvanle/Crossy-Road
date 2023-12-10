#include "container.hpp"
#include <object.hpp>
int id = 0;
Action* Object::react() 
{
    if(!IsKeyDown(KEY_SPACE)) return nullptr;
    id %= actions[0].size();
    return actions[0][id++]->clone();
}

void Object::draw()
{
    Container::draw();
    return ;
}
