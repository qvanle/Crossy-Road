#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <thread>
#include <chrono>
#include <vector>

#include <raylib.h>

#include <storage_raw.hpp>

class Window 
{
private:
    int width;
    int height;
    std::string title;
    Color background;
    std::vector<std::thread> thread_pool;
    
    bool status;
    
    RawStorage texturesStorage;    

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
