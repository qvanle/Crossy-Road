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
    friend class switchTrafficLightAction;
    fPoint velocity;
    std::vector<Container*> visiter;
    std::deque<Container*> Entity;
    Container* trafficLight;
    bool stop;
    std::chrono::time_point<std::chrono::system_clock> spawnClock;
    std::chrono::time_point<std::chrono::system_clock> moveClock;
    std::chrono::time_point<std::chrono::system_clock> LightClock;
    constexpr static std::chrono::duration<double> spawnTime = std::chrono::duration<double>(1.0);
    constexpr static std::chrono::duration<double> moveTime = std::chrono::duration<double>(0.1);
    std::chrono::duration<double> lightGreen = std::chrono::duration<double>(4 + GetRandomValue(-200, 200) / 100.0);
    std::chrono::duration<double> lightRed = std::chrono::duration<double>(1.5 + GetRandomValue(-100, 50) / 100.0);
    std::vector<int> entityOrder;
    int score;
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

    void attachLight(Container*);

    void setVelocity(fPoint);
    bool isEntityCollide(Container* main);
    int getScore();

    std::string linkContent(std::string path) override;
    YAML::Node createSpecialContent() override;
    void loadSpecialContent(YAML::Node) override;
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

class switchTrafficLightAction : public Action
{
private: 
    Chunk* chunk;
public:
    switchTrafficLightAction(Chunk*);
    ~switchTrafficLightAction();

    void execute() override;
    Action* clone() override;
};
#endif 

