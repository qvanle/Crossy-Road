#include "container.hpp"
#include <object.hpp>
PacketAction* Object::react() 
{
    if(std::chrono::steady_clock::now() < waitUntil) 
        return nullptr;
    for(int i = 0; i < strokes.size(); i++)
    {
        Action* a = strokes[i].stroke->react();
        if(a == nullptr) continue;
        else strokes[i].stroke->nextAction();
        PacketAction* packet = new PacketAction(); 
        packet->addAction(a);
        return packet;
    }


    return nullptr;
}

void Object::draw()
{
    Container::draw();
    return ;
}
