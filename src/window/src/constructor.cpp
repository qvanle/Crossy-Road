#include <window.hpp>
#include <const/path/atb.hpp>

#include <file.hpp>

Window::Window()
{
    Wcontent.width = 1200;
    Wcontent.height = 668;
    Wcontent.title = "Crossy Road clone";
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    InitWindow(Wcontent.width, Wcontent.height, Wcontent.title.c_str());
    SetTargetFPS(60);

    UI.root_frame = new Frame({0, 0, Wcontent.width, Wcontent.height});
}

Window::Window(std::string path)
{
    path = PATB::WINDOW_ + path;
    YAML::Node config = YAML_FILE::readFile(path);
    initRaylib(config);
    
    loadInterface(config["interface-list"]);
    if(config["choose-interface"]) 
        UI.interface->push(config["choose-interface"].as<std::string>());

    if(config["input-delay"]) 
    {
        double delay = config["input-delay"].as<int>() / 1000.0;
        Wcontent.input_delay = std::chrono::duration<double>(delay);
    }else 
    {
        Wcontent.input_delay = std::chrono::duration<int>(50) / 1000.0;
    }
}


void Window::initRaylib(YAML::Node config)
{
    Wcontent.width = config["width"].as<int>();
    Wcontent.height = config["height"].as<int>();
    Wcontent.title = config["title"].as<std::string>();
    // enable resizeable window and vsync
    
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    InitWindow(Wcontent.width, Wcontent.height, Wcontent.title.c_str());
    SetTargetFPS(60);
    Wcontent.status = true;

    UI.root_frame = new Frame({0, 0, Wcontent.width, Wcontent.height});
}

void Window::loadInterface(YAML::Node node)
{
    if(!node) return ;
    
    UI.interface = new InterfacePool();
    for(auto i : node)
    {
        std::string path = i["file"].as<std::string>();
        float x = 0, y = 0, w = 100, h = 100;

        //if(i["x"]) x = i["x"].as<int>();
        //if(i["y"]) y = i["y"].as<int>();
        //if(i["w"]) w = i["w"].as<int>();
        //if(i["h"]) h = i["h"].as<int>();
        
        x = x / 100.0;
        y = y / 100.0;
        w = w / 100.0;
        h = h / 100.0;

        Interface* inf = new Interface(UI.root_frame, {x, y, w, h});
        inf->linkContent(path);
        UI.interface->load(inf);
    }
}
