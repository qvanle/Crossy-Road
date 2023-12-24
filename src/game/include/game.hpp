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
    std::deque<Chunk*> chunks;
    std::vector<Chunk*> cache;
    fPoint mapSpeed;
    std::chrono::time_point<std::chrono::system_clock> mapSpeedClock;
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

    PacketAction* react() override;
    PacketAction* getRuntimeEvent() override;
    void draw() override;

};

class moveChunksAction : public Action
{
private: 
    Game* game;
    fPoint delta;
public:
    moveChunksAction(Game*, fPoint);
    ~moveChunksAction();

    void execute() override;
    Action* clone() override;
};
#endif 
