#include "action.hpp"
#include <interface.hpp>

PacketAction* Interface::getRuntimeEvent()
{
    PacketAction* packet = Container::getRuntimeEvent();
    Action* action = nullptr;
    
    for(auto i : nested)
    {
        action = i->getRuntimeEvent();
        if(action != nullptr) 
        {
            if(packet == nullptr) packet = new PacketAction();
            packet->addAction(action);
        }
    }

    for(auto i : containers) 
    {
        action = i->getRuntimeEvent();
        if(action != nullptr) 
        {
            if(packet == nullptr) packet = new PacketAction();
            packet->addAction(action);
        }
    }

    return packet;
}

PacketAction* Interface::react()
{
    if(!isVisible()) return nullptr;
    PacketAction* packet = Container::react();

    for(auto i : keystrokes)
    {
        Action* action = i->react();
        if(action != nullptr) 
        {
            if(packet == nullptr) packet = new PacketAction();
            packet->addAction(action);
        }
    }

    for(auto i : containers) 
    {
        Action* action = i->react();
        if(action != nullptr) 
        {
            if(packet == nullptr) packet = new PacketAction();
            packet->addAction(action);
        }
    }

    return packet;
}
