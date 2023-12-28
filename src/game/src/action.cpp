#include <game.hpp>

Action* Game::react()
{
    if(!isVisible()) return nullptr;
    return Interface::react();
}

Action* Game::getRuntimeEvent()
{
    if(!isVisible()) return nullptr;
    // if now - mapSpeedClock < 10 millisecond, return nullptr 

    if(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - mapSpeedClock).count() < 20) 
        return nullptr;
    Action* action; 
    PacketAction* packet = nullptr;
    action = Interface::getRuntimeEvent();

    if(action != nullptr)
    {
        packet = new PacketAction();
        packet->addAction(action);
    }

    action = new moveChunksAction(this, mapDisplacement);
    if(packet == nullptr) packet = new PacketAction();
    packet->addAction(action);

    for(auto i : chunks)
    {
        Action* act = i->getRuntimeEvent();
        if(act == nullptr) 
            continue;
        if(packet == nullptr) 
            packet = new PacketAction();
        packet->addAction(act);
    }

    action = new moveObjectAction(main, mapDisplacement);
    if(packet == nullptr) packet = new PacketAction();
    packet->addAction(action);

    mapSpeedClock = std::chrono::system_clock::now();

    return packet;
}
