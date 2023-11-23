#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <thread>
#include <chrono>
#include <vector>

#include <raylib.h>

#include <visual.hpp>
#include <object.hpp>

class Window 
{
private:
    float width;
    float height;
    std::string title;
    Color background;
    std::vector<std::thread> thread_pool;
    
    bool status;

    Frame* root_frame;
    
    Object* obj;
    
    std::chrono::time_point<std::chrono::system_clock> last_frame;

protected:
    void draw();
    void getUserEvent();
    void getRuntimeEvent();
    void update();
    void sound_effect();
public:
    Window();
    Window(std::string path);
    ~Window();

    bool isRun();
    bool isClose();
    void run();
};

#endif 
