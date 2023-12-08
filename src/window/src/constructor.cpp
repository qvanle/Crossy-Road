#include <window.hpp>
#include <const/path/atb.hpp>

#include <file.hpp>

Window::Window()
{
    width = 1200;
    height = 668;
    title = "Crossy Road clone";
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    InitWindow(width, height, title.c_str());
    SetTargetFPS(60);

    root_frame = new Frame({0, 0, width, height});
}

Window::Window(std::string path)
{
    path = PATB::WINDOW_ + path;
    YAML::Node config = YAML_FILE::readFile(path);
    initRaylib(config);
    
    loadInterface(config["interface-list"]);
    if(config["choose-interface"]) 
        interface->push(config["choose-interface"].as<std::string>());
}


void Window::initRaylib(YAML::Node config)
{
    width = config["width"].as<int>();
    height = config["height"].as<int>();
    title = config["title"].as<std::string>();

    InitWindow(width, height, title.c_str());
    SetTargetFPS(60);
    status = true;

    root_frame = new Frame({0, 0, width, height});
}

void Window::loadInterface(YAML::Node node)
{
    if(!node) return ;
    
    interface = new InterfacePool();
    for(auto i : node)
    {
        std::string path = i["file"].as<std::string>();
        float x = 1, y = 1, w = 98, h = 98;

        //if(i["x"]) x = i["x"].as<int>();
        //if(i["y"]) y = i["y"].as<int>();
        //if(i["w"]) w = i["w"].as<int>();
        //if(i["h"]) h = i["h"].as<int>();
        
        x = x / 100.0;
        y = y / 100.0;
        w = w / 100.0;
        h = h / 100.0;

        Interface* inf = new Interface(root_frame, {x, y, w, h});
        inf->linkContent(path);
        interface->load(inf);
    }
}
