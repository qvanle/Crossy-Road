#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <thread>
#include <chrono>

#include "raylib.h"

class Window 
{
private:
    int width;
    int height;
    std::string title;
    Color background;

protected:
public:
    Window();
    ~Window();

    void run();
};

#endif 
