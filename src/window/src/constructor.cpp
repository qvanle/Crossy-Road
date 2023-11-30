#include <window.hpp>
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
    YAML::Node config = YAML_FILE::readFile(path);
    width = config["width"].as<int>();
    height = config["height"].as<int>();
    title = config["title"].as<std::string>();

    root_frame = new Frame({0, 0, width, height});

    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    InitWindow(width, height, title.c_str());
    SetTargetFPS(60);
    status = true;

    Texture2D *txt = new Texture2D(LoadTexture("assets/graphics/45908.png"));

    graphics = new Visual(txt,root_frame, {0.25, 0.25, 0.5, 0.5});
    graphics->resize({0.5, 0.5});
}

