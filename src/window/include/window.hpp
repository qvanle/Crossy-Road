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
#include <button.hpp>


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
        PacketAction* react();
        PacketAction* getRuntimeEvent();

    };
    class ActionPool 
    {
    private:
        std::queue<Action*> pool;
    public: 
        ActionPool() = default;
        ~ActionPool();
        void push(Action* act);
        void push(PacketAction* act);
        Action* front();
        Action* pop();
        bool empty() const;
    };
    class WinContent 
    {
    private:
        bool status;
        std::vector<std::thread> thread_pool;
        std::chrono::time_point<std::chrono::steady_clock> input_clock;
        std::chrono::time_point<std::chrono::steady_clock> runtime_clock;
    public: 
        std::chrono::duration<double> input_delay;
        std::chrono::duration<double> runtime_delay;
        float width;
        float height;
        Color background;
        std::string title;
        
        ~WinContent();

        void setStatus(bool);
        bool getStatus() const;

        void setInputClock2Now();
        void setRuntimeClock2Now();

        bool isInputDelayOver() const;
        bool isRuntimeDelayOver() const;

    };
    class UI 
    {
    private: 
        Frame* root_frame;
        InterfacePool* interface;
    public: 
        UI();
        ~UI();
        void draw();
        PacketAction* react();
        PacketAction* getRuntimeEvent();

        void setRootFrame(Frame*);
        Frame* getRootFrame() const;
        void resize(float, float);

        void setInterfacePool(InterfacePool*);

        void load(Interface*);
        void unload(Interface*);
        Interface* getInterface(std::string);

        void push(std::string);
        std::string pop();
        Interface* top();
    };

    friend class CloseAction;
    friend class resizeAction;

    WinContent Wcontent;
    UI UI;
    ActionPool immediate_user_pool, immediate_pool, request_pool;

protected:
    void draw();
    void getUserEvent();
    void getRuntimeEvent();
    void sound_effect();
    void immediateActing();
    void userActing();
    void requestActing();

    void initRaylib(YAML::Node node);
    void loadInterface(YAML::Node node);
    void loadGame(YAML::Node node);
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
};
#endif 
