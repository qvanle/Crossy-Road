#include <chunk.hpp>

Container* Chunk::randomEntity() 
{
    int value = GetRandomValue(0, 100);

    for(auto i : visiter)
    {
        value -= i->getProbability();
        if(value <= 0) return i;
    }

    return visiter[GetRandomValue(0, visiter.size() - 1)];
}
Action* Chunk::getRuntimeEvent() 
{
    Action* action = Interface::getRuntimeEvent();
    

    return action;
}
