#ifndef CHUNK_HPP
#define CHUNK_HPP 

#include <chrono> 
#include <deque>

#include <interface.hpp>

class Chunk : public Interface 
{
private: 
    fPoint velocity;
    std::vector<Container*> visiter;
    std::deque<Container*> Entity;
    std::chrono::time_point<std::chrono::system_clock> spawnClock;
    constexpr static std::chrono::duration<double> spawnTime = std::chrono::duration<double>(1.0);

protected:
    void drawEntity();
    Container* randomEntity();
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

    std::string linkContent(std::string path) override;
    Action* getRuntimeEvent() override;

    void draw() override;
};

#endif 

