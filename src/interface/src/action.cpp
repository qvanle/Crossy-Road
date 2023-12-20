#include <interface.hpp>

Action* Interface::runtimeEvent()
{
    PacketAction* packet = nullptr; 
        
    Action* action = Container::runtimeEvent();
    if(action != nullptr) 
    {
        packet = new PacketAction();
        packet->addAction(action);
    }

    for(auto i : containers) 
    {
        action = i->runtimeEvent();
        if(action != nullptr) 
        {
            if(packet == nullptr) packet = new PacketAction();
            packet->addAction(action);
        }
    }

    return packet;
}

Action* Interface::react()
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

    for(auto i : nested) 
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
