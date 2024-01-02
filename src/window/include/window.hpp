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
#include <inputbox.hpp>


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
        Action* getRuntimeEvent();

    };
    class ActionPool 
    {
    private:
        std::queue<Action*> pool;
        std::mutex mtx;
    public: 
        ActionPool() = default;
        ~ActionPool();
        void push(Action* act);
        void push(PacketAction* act);
        Action* front();
        Action* pop();
        bool empty();
    };
    class WinContent 
    {
    private:
        bool status;
        std::chrono::time_point<std::chrono::steady_clock> input_clock;
        std::chrono::time_point<std::chrono::steady_clock> runtime_clock;

        std::mutex status_mtx;
        std::mutex input_mtx;
        std::mutex runtime_mtx;
    public: 
        std::chrono::duration<double> input_delay;
        std::chrono::duration<double> runtime_delay;
        float width;
        float height;
        Color background;
        std::string title;

        std::vector<std::thread> thread_pool;
        
        ~WinContent();

        void setStatus(bool);
        bool getStatus();

        void setInputClock2Now();
        void setRuntimeClock2Now();

        bool isInputDelayOver();
        bool isRuntimeDelayOver();

    };
    class UI 
    {
    private: 
        Frame* root_frame;
        InterfacePool* interface;

        std::mutex mtx;
        int reader;
        int writer;
        bool noRead;
        bool noWrite;
    protected: 
        bool isReadable();
        bool isWritable();

        void reading();
        bool tryReading();
        void endReading();

        void writing();
        bool tryWriting();
        void endWriting();

    public: 
        UI();
        ~UI();
        void draw();
        Action* react();
        Action* getRuntimeEvent();

        void setRootFrame(Frame*);
        Frame* getRootFrame();
        void resize(float, float);

        void setInterfacePool(InterfacePool*);

        void load(Interface*);
        void unload(Interface*);
        Interface* getInterface(std::string);

        void push(std::string);
        std::string pop();
        Interface* top();

        void DenyRead();
        void AllowRead();

        void DenyWrite();
        void AllowWrite();
    };

    friend class CloseAction;
    friend class resizeAction;

    WinContent Wcontent;
    UI UI;
    ActionPool immediate_user_pool, immediate_pool, request_pool, system_pool;

    // test inputBox
    InputBox* inputBox;

protected:
    void draw();
    void systemEvent();
    void getUserEvent();
    void getRuntimeEvent();
    void sound_effect();
    void immediateActing();
    void userActing();
    void requestActing();
    void systemActing();

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

/**
 * @class CloseAction
 *
 * @brief manages the closing of the application
 * 
**/
class CloseAction : public Action
{
private: 
    Window * win;
public: 
    CloseAction(Window* win);
    ~CloseAction() = default;
    void execute();
};

/**
 * @class resizeAction
 *
 * @brief manages the resizing of the window
 * 
**/
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
