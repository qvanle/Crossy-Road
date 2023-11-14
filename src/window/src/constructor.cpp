#include <window.hpp>
#include <file.hpp>

Window::Window()
{
    width = 1200;
    height = 668;
    title = "Crossy Road clone";
    InitWindow(width, height, title.c_str());
    SetTargetFPS(60);

    BeginDrawing();
        ClearBackground(RAYWHITE);
    EndDrawing();

    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
}

Window::Window(std::string path)
{
    YAML::Node config = YAML_FILE::readFile(path);
    width = config["width"].as<int>();
    height = config["height"].as<int>();
    title = config["title"].as<std::string>();
    InitWindow(width, height, title.c_str());
    SetTargetFPS(60);

    BeginDrawing();
        ClearBackground(RAYWHITE);
    EndDrawing();

    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
}

