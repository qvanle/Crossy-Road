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
    width = config["width"].as<int>();
    height = config["height"].as<int>();
    title = config["title"].as<std::string>();

    root_frame = new Frame({0, 0, width, height});

    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    InitWindow(width, height, title.c_str());
    SetTargetFPS(60);
    status = true;
    
    interface = new Interface(root_frame, {0.02, 0.04, 0.96, 0.92});
    interface->linkContent("test.yaml");
}

