#include <window.hpp>
#include <file.hpp>

Window::Window()
{
    width = 1200;
    height = 668;
    title = "Crossy Road clone";

    InitWindow(width, height, title.c_str());
    SetTargetFPS(60);
}

Window::Window(std::string path)
{
    YAML::Node config = YAML_FILE::readFile(path);
    width = config["width"].as<int>();
    height = config["height"].as<int>();
    title = config["title"].as<std::string>();
    InitWindow(width, height, title.c_str());
    SetTargetFPS(60);
    status = true;
}

