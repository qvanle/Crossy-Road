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
#include <object.hpp>
#include <interface.hpp>


class Window 
{
private:
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

        void draw();
        Action* react();

    };
    class ActionPool 
    {
    private:
        std::queue<Action*> pool;
    public: 
        ActionPool() = default;
        ~ActionPool();
        void push(Action* act);
        Action* front();
        Action* pop();
        bool empty() const;
    };
    struct WinContent 
    {
        float width;
        float height;
        Color background;
        std::string title;
        bool status;
        std::vector<std::thread> thread_pool;
    };
    struct UI 
    {
        Frame* root_frame;
        Container* obj;
        InterfacePool* interface;
        UI();
        ~UI();
        void draw();
        Action* react();
    };

    friend class CloseAction;
    friend class resizeAction;

    WinContent Wcontent;
    UI UI;
    ActionPool immediate_pool, duration_pool;

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

class CloseAction : public Action
{
private: 
    Window * win;
public: 
    CloseAction(Window* win);
    ~CloseAction() = default;
    void execute();
    void forceEnd();
    void interrupt();
};

class resizeAction : public Action
{
private: 
    float w, h;
    Window* win;
public: 
    resizeAction(Window* window, float w, float h);
    ~resizeAction() = default;
    void execute();
    void forceEnd();
    void interrupt();
};
#endif 
