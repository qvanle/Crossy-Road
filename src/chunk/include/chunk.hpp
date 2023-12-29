#ifndef CHUNK_HPP
#define CHUNK_HPP 

#include "action.hpp"
#include <chrono> 
#include <deque>

#include <interface.hpp>

/**
 * @class Chunk
 *
 * @brief manages the spawning of chunks and how entities interact witht them
 * 
**/
class Chunk : public Interface 
{
private: 
    friend class moveEntityAction;
    fPoint velocity;
    std::vector<Container*> visiter;
    std::deque<Container*> Entity;
    std::chrono::time_point<std::chrono::system_clock> spawnClock;
    std::chrono::time_point<std::chrono::system_clock> moveClock;
    constexpr static std::chrono::duration<double> spawnTime = std::chrono::duration<double>(1.0);
    constexpr static std::chrono::duration<double> moveTime = std::chrono::duration<double>(0.1);

protected:
    void drawEntity();
    Container* randomEntity();
    void movingEntity();
public: 
    Chunk(Frame*, Rectangle);
    Chunk(Chunk*);
    Chunk(Chunk*, Rectangle);
    Chunk(Chunk*, Frame*, Rectangle);
    ~Chunk();

    void addVisiter(Container*);
    void addVisiter(Container*, int);
    void addVisiter(Container*, Rectangle);
    void addVisiter(Container*, int, Rectangle);
    void generateEntity();

    void setVelocity(fPoint);
    bool isEntityCollide(Container* main);

    std::string linkContent(std::string path) override;
    Action* getRuntimeEvent() override;

    void draw() override;
};

class moveEntityAction : public Action
{
private: 
    Chunk* chunk;
public:
    moveEntityAction(Chunk*);
    ~moveEntityAction();

    void execute() override;
    Action* clone() override;
};
#endif 

