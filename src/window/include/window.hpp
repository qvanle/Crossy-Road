#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <thread>
#include <chrono>
#include <vector>

#include <raylib.h>

#include <storage_raw.hpp>
#include <visual.hpp>

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
    
    RawStorage texturesStorage;    
    Visual* img;

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
