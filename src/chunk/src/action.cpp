#include "action.hpp"
#include <chunk.hpp>

Container* Chunk::randomEntity() 
{
    int value = GetRandomValue(0, 100);
    int id = 0;
    for(auto i : visiter)
    {
        value -= i->getProbability();
        if(value <= 0) 
        {
            entityOrder.push_back(id);
            return i;
        }
        id++;
    }
    id = GetRandomValue(0, visiter.size() - 1);
    entityOrder.push_back(id);
    return visiter[id];
}

void Chunk::movingEntity() 
{
    for(auto i : Entity)
    {
        i->moveBy(velocity);
        i->nextImage();
    }
}

Action* Chunk::getRuntimeEvent() 
{
    if(!isVisible()) return nullptr;
    PacketAction* packet = nullptr; 
    Action* action = Interface::getRuntimeEvent();
    
    if(action != nullptr) 
    {
        packet = new PacketAction();
        packet->addAction(action);
    }

    if(std::chrono::system_clock::now() - moveClock >= moveTime) 
    {
        Action* action = new moveEntityAction(this);
        if(packet == nullptr) 
        {
            packet = new PacketAction();
        }
        packet->addAction(action);
        moveClock = std::chrono::system_clock::now();
    }
    return packet;
}
