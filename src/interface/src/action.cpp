#include "action.hpp"
#include <interface.hpp>

PacketAction* Interface::getRuntimeEvent()
{
    PacketAction* packet = nullptr; 
        
    Action* action = Container::getRuntimeEvent();
    if(action != nullptr) 
    {
        packet = new PacketAction();
        packet->addAction(action);
    }
    
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
    PacketAction* packet = nullptr;

    Action* action = Container::react();
    if(action != nullptr) 
    {
        packet = new PacketAction();
        packet->addAction(action);
    }

    for(auto i : keystrokes)
    {
        action = i->react();
        if(action != nullptr) 
        {
            if(packet == nullptr) packet = new PacketAction();
            packet->addAction(action);
        }
    }

    for(auto i : containers) 
    {
        action = i->react();
        if(action != nullptr) 
        {
            if(packet == nullptr) packet = new PacketAction();
            packet->addAction(action);
        }
    }

    return packet;
}
