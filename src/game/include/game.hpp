#ifndef GAME_HPP
#define GAME_HPP

#include "action.hpp"
#include <deque>
#include <chrono>

#include <raylib.h>

#include <frame.hpp>
#include <container.hpp>
#include <keystroke.hpp>
#include <interface.hpp>
#include <chunk.hpp>

class Game : public Interface
{
private: 
    friend class moveChunksAction;
    friend class startInitClockAction;
    std::deque<Chunk*> chunks;
    std::vector<Chunk*> cache;
    Container* main;
    fPoint mapDisplacement;
    fPoint mapDirection;
    float mapSpeed;
    std::chrono::time_point<std::chrono::system_clock> mapSpeedClock;
    std::chrono::time_point<std::chrono::system_clock> initStateClock;
    bool initState;
protected:
    void loadChunk(YAML::Node);
    void loadCollide(YAML::Node);
    void loadEvent(YAML::Node);
    void loadAttactObject(YAML::Node);
    void loadMap();
public: 
    Game(Frame*, Rectangle);
    Game(Game*);
    Game(Game*, Rectangle);
    Game(Game*, Frame*, Rectangle);

    ~Game();

    std::string linkContentAbsolute(std::string path) override;
    
    void reset() override;

    Action* react() override;
    Action* getRuntimeEvent() override;
    void draw() override;

};

class moveChunksAction : public Action
{
private: 
    Game* game;
    fPoint delta;
    fPoint direction;
    float speed;
public:
    moveChunksAction(Game*, fPoint);
    moveChunksAction(Game*, fPoint, float);
    ~moveChunksAction();

    void execute() override;
    Action* clone() override;
};

class startInitClockAction : public Action
{
private: 
    Game* game;
public:
    startInitClockAction(Game*);
    ~startInitClockAction() = default;

    void execute() override;
    Action* clone() override;
};
#endif 
