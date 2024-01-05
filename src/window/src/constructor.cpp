#include <window.hpp>
#include <game.hpp>
#include <const/path/atb.hpp>
#include <const/path/assets.hpp>

#include <file.hpp>

Window::Window()
{
    Wcontent.width = 1200;
    Wcontent.height = 668;
    Wcontent.title = "Crossy Road clone";
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    InitWindow(Wcontent.width, Wcontent.height, Wcontent.title.c_str());
    SetTargetFPS(60);

    UI.setRootFrame(new Frame({0, 0, Wcontent.width, Wcontent.height}));
}

Window::Window(std::string path)
{
    path = PATB::WINDOW_ + path;
    YAML::Node config = YAML_FILE::readFile(path);
    initRaylib(config);

    loadInterface(config["interface-list"]);
    loadGame(config["game"]);
    if (config["choose-interface"])
        UI.push(config["choose-interface"].as<std::string>());

    if (config["input-delay"])
    {
        double delay = config["input-delay"].as<int>() / 1000.0;
        Wcontent.input_delay = std::chrono::duration<double>(delay);
    }
    else
    {
        Wcontent.input_delay = std::chrono::duration<int>(50) / 1000.0;
    }

    if (config["runtime-delay"])
    {
        double delay = config["runtime-delay"].as<int>() / 1000.0;
        Wcontent.runtime_delay = std::chrono::duration<double>(delay);
    }
    else
    {
        Wcontent.runtime_delay = std::chrono::duration<int>(40) / 1000.0;
    }
    if(config["music"]) 
    {
        loadMusic(config["music"]);
    }

    // test inputbox
    Font font = GetFontDefault();
    inputBox = new InputBox(20, {0.4, 0.2, 0.2, 0.2}, UI.getRootFrame(), &font);
    inputBox->linkContent("inputbox.yaml");
    inputBox->hide();

    highscore = new highScore("inputbox.yaml");
}

void Window::initRaylib(YAML::Node config)
{
    Wcontent.width = config["width"].as<int>();
    Wcontent.height = config["height"].as<int>();
    Wcontent.title = config["title"].as<std::string>();
    // enable resizeable window and vsync

    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    InitWindow(Wcontent.width, Wcontent.height, Wcontent.title.c_str());
    InitAudioDevice();
    SetTargetFPS(60);
    Wcontent.setStatus(true);
    UI.setRootFrame(new Frame({0, 0, Wcontent.width, Wcontent.height}));
}

void Window::loadInterface(YAML::Node node)
{
    if (!node)
        return;

    UI.setInterfacePool(new InterfacePool());
    for (auto i : node)
    {
        std::string path = i["file"].as<std::string>();
        float x = 0, y = 0, w = 1, h = 1;

        if (i["x"])
            x = i["x"].as<float>() / 100;
        if (i["y"])
            y = i["y"].as<float>() / 100;
        if (i["w"])
            w = i["w"].as<float>() / 100;
        if (i["h"])
            h = i["h"].as<float>() / 100;

        Interface *inf = new Interface(UI.getRootFrame(), {x, y, w, h});
        inf->linkContent(path);
        UI.load(inf);
    }
}


void Window::loadMusic(YAML::Node node)
{
    if(!node) return ;

    for(auto i : node)
    {
        std::string path = i["path"].as<std::string>();
        path = PASSETS::SOUND_ + path;
        Music music = LoadMusicStream(path.c_str());
        SetMusicVolume(music, 1);
        musicController.add(music);
    }
}

void Window::loadGame(YAML::Node f)
{
    if (!f)
        return;
    for (auto node : f)
    {
        std::string path = node["file"].as<std::string>();
        float x = 0, y = 0, w = 1, h = 1;

        if (node["x"])
            x = node["x"].as<float>() / 100;
        if (node["y"])
            y = node["y"].as<float>() / 100;
        if (node["w"])
            w = node["w"].as<float>() / 100;
        if (node["h"])
            h = node["h"].as<float>() / 100;

        Interface *inf = new Game(UI.getRootFrame(), {x, y, w, h});
        inf->linkContent(path);
        UI.load(inf);
    }
}
