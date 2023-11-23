#include <window.hpp>
#include <file.hpp>

Window::Window()
{
    width = 1200;
    height = 668;
    title = "Crossy Road clone";

    InitWindow(width, height, title.c_str());
    SetTargetFPS(60);

    root_frame = new Frame({0, 0, width, height});
}

Window::Window(std::string path)
{
    YAML::Node config = YAML_FILE::readFile(path);
    width = config["width"].as<int>();
    height = config["height"].as<int>();
    title = config["title"].as<std::string>();

    root_frame = new Frame({0, 0, width, height});

    InitWindow(width, height, title.c_str());
    SetTargetFPS(60);
    status = true;

    obj = new Object(root_frame, Rectangle({0.5, 0.5, 1.0, 1.0}));
    YAML::Node main = YAML_FILE::readFile("atb/object/main.yaml");
    obj->setContent(&main);

}

