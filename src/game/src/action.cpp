#include <game.hpp>

Action* Game::react()
{
    return Interface::react();
}

Action* Game::getRuntimeEvent()
{
    // if now - mapSpeedClock < 10 millisecond, return nullptr 

    if(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - mapSpeedClock).count() < 20) 
        return nullptr;

    PacketAction* packet = nullptr;
    
    Action* action = Interface::getRuntimeEvent();
    if(action != nullptr) 
    {
        packet = new PacketAction();
        packet->addAction(action);
    }
    
    action = new moveChunksAction(this, mapSpeed);
    if(packet == nullptr) packet = new PacketAction();
    packet->addAction(action);

    for(auto i : chunks)
    {
        action = i->getRuntimeEvent();
        if(action == nullptr) 
            continue;
        if(packet == nullptr) 
            packet = new PacketAction();
        packet->addAction(action);
    }

    mapSpeedClock = std::chrono::system_clock::now();

    return packet;
}
