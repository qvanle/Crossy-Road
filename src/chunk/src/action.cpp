#include "action.hpp"
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

void Chunk::movingEntity() 
{
    for(auto i : Entity)
    {
        if(!i->isVisible()) continue;
        i->moveBy(velocity);
        i->nextImage();
    }
}

PacketAction* Chunk::getRuntimeEvent() 
{
    if(!isVisible()) return nullptr;
    PacketAction* packet = Interface::getRuntimeEvent();
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
