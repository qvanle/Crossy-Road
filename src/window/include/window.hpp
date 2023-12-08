#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <queue>
#include <stack>

#include <raylib.h>

#include <visual.hpp>
#include <action.hpp>
#include <container.hpp>
#include <interface.hpp>


class Window 
{
private:
    friend class Action;

    float width;
    float height;
    std::string title;
    Color background;
    std::vector<std::thread> thread_pool;
    
    bool status;

    Frame* root_frame;
    
    std::chrono::time_point<std::chrono::system_clock> last_frame;
    
    class InterfacePool 
    {
    private: 
        std::stack<Interface*> inf;
        std::map<std::string, Interface*> storage;
        void clearStack();
    public:
        InterfacePool();
        ~InterfacePool();
        void load(Interface*);
        void unload(Interface*);
        void clear();
        Interface* getInterface(std::string);

        void push(std::string);
        std::string pop();
        Interface* top();

    }* interface;

    class ActionPool 
    {
    private:
        std::queue<Action*> pool;
    public: 
        ActionPool() = default;
        void push(Action* act);
        Action* front();
        Action* pop();
        bool empty() const;
    } immediate_pool, duration_pool;

protected:
    void draw();
    void getUserEvent();
    void getRuntimeEvent();
    void sound_effect();
    void immediateActing();
    void durationActing();

    void initRaylib(YAML::Node node);
    void loadInterface(YAML::Node node);
public:
    Window();
    Window(std::string path);
    ~Window();

    bool isRun();
    bool isClose();
    void run();
};

#endif 
