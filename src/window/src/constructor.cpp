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
    root_frame = new Frame({0, 0, width, height});

    title = config["title"].as<std::string>();
    InitWindow(width, height, title.c_str());
    SetTargetFPS(60);
    status = true;
    
    Image img = LoadImage("assets/graphics/45908.png");
    Texture2D* txtr = new Texture2D();
    *txtr = LoadTextureFromImage(img);
    texturesStorage.insert("background", txtr);
    std::cout << "root: " << root_frame << "\n";
    Frame* subframe = new Frame({root_frame, {0, 0, 1, 1}});
    Window::img = new Visual(txtr, subframe);
}

