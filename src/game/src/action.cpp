#include <game.hpp>

PacketAction* Game::react()
{
    return Interface::react();
}

PacketAction* Game::getRuntimeEvent()
{
    // if now - mapSpeedClock < 10 millisecond, return nullptr 

    if(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - mapSpeedClock).count() < 20) 
        return nullptr;
    Action* action ; 
    PacketAction* packet = Interface::getRuntimeEvent();

    action = new moveChunksAction(this, mapSpeed);
    if(packet == nullptr) packet = new PacketAction();
    packet->addAction(action);

    for(auto i : chunks)
    {
        PacketAction* act = i->getRuntimeEvent();
        if(act == nullptr) 
            continue;
        if(packet == nullptr) 
            packet = new PacketAction();
        packet->addAction(act);
    }

    mapSpeedClock = std::chrono::system_clock::now();

    return packet;
}
