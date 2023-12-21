#include <game.hpp>

Action* Game::react()
{
    return Interface::react();
}

Action* Game::getRuntimeEvent()
{
    PacketAction* packet = nullptr;
    
    Action* action = Interface::getRuntimeEvent();
    if(action != nullptr) 
    {
        packet = new PacketAction();
        packet->addAction(action);
    }
    
    action = new moveChunksAction(this, {0, 0.002});
    if(packet == nullptr) packet = new PacketAction();
    packet->addAction(action);
    return packet;
}
