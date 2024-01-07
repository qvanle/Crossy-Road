#include "interface.hpp"
#include <request.hpp>
#include <game.hpp>


void Game::pause()
{
    isPause = true;
}

void Game::cont()
{
    isPause = false;
}

int Game::getScore()
{
    return score;
}
Action* Game::react()
{
    if(!isVisible()) return nullptr;
    if(isPause) return nullptr;
    if(isLose) return nullptr;
    if(initState) 
    {
        return new startInitClockAction(this);
    }
    if(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - initStateClock).count() < 400) 
        return nullptr;
    return Interface::react();
}

Action* Game::getRuntimeEvent()
{
    if(!isVisible()) return nullptr;
    if(isPause) return nullptr;
    // if now - mapSpeedClock < 10 millisecond, return nullptr 
    if(initState) 
    {
        return new startInitClockAction(this);
    }
    if(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - initStateClock).count() < 400) 
        return nullptr;

    if(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - mapSpeedClock).count() < 20) 
        return nullptr;

    if(isLose && isDying) 
    {
        if(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - dyingClock).count() < 200) 
            return nullptr;

        dyingClock = std::chrono::system_clock::now();
        return new dyingAction(this);
    }

    if(isLose && !isDying)
    {
        if(dieIndex++ != 0) return nullptr;
        Action* act = new loseRequest(score);
        PacketAction* packet = nullptr;
        if(packet == nullptr) packet = new PacketAction();
        packet->addAction(act);
        return packet;
    }

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
        if(i->getRelative()[1] > 1.05) break;
        if(i->isEntityCollide(main)) 
        {
            Action* act = new dyingAction(this);
            if(packet == nullptr) packet = new PacketAction();
            packet->addAction(act);
            dyingClock = std::chrono::system_clock::now();
        }
        if(i->isCollide(main)) 
        {
            Action* act = new addScoreAction(this, i);
            if(packet == nullptr) packet = new PacketAction();
            packet->addAction(act);
        }
        Action* act = i->getRuntimeEvent();
        if(act == nullptr) 
            continue;
        if(packet == nullptr) 
            packet = new PacketAction();
        packet->addAction(act);
    }
    if(main->getRelative()[1] < 0.5)
    {
        action = new movetoObjectAction(main, fPoint({main->getRelative()[0], 0.5}));
        if(packet == nullptr) packet = new PacketAction();
        packet->addAction(action);

        action = new moveChunksAction(this, {mapDisplacement[0], mapDisplacement[1]});
        if(packet == nullptr) packet = new PacketAction();
        packet->addAction(action);

        action = new moveChunksAction(this, {mapDisplacement[0], mapDisplacement[1]});
        if(packet == nullptr) packet = new PacketAction();
        packet->addAction(action);
    }
    if(main->getRelative()[1] > 1.05) 
    {
        Action* act = new dyingAction(this);
        if(packet == nullptr) packet = new PacketAction();
        packet->addAction(act);
        dyingClock = std::chrono::system_clock::now();
    }
    if(main->getRelative()[0] < -0.4)
    {
        Action* act = new dyingAction(this);
        if(packet == nullptr) packet = new PacketAction();
        packet->addAction(act);
        dyingClock = std::chrono::system_clock::now();
    }
    if(main->getRelative()[0] > 1.2)
    {
        Action* act = new dyingAction(this);
        if(packet == nullptr) packet = new PacketAction();
        packet->addAction(act);
        dyingClock = std::chrono::system_clock::now();
    }
    action = new moveObjectAction(main, mapDisplacement);
    if(packet == nullptr) packet = new PacketAction();
    packet->addAction(action);

    mapSpeedClock = std::chrono::system_clock::now();

    return packet;
}
