#include <interface.hpp>
#include <const/path/atb.hpp>
#include <file.hpp>
#include <object.hpp>

Interface::Interface(Frame* frame, Rectangle rect) : Container(frame, rect)
{
    main = nullptr;
}

Interface::Interface(Interface* other) : Container(other)
{
    main = nullptr;
}

Interface::Interface(Interface* other, Rectangle rect) : Container(other, rect)
{
    main = nullptr;
}

Interface::Interface(Interface* other, Frame* frame, Rectangle rect) : Container(other, frame, rect)
{
    main = nullptr;
}

std::string Interface::linkContent(std::string path)
{
    return linkContentAbsolute(PATB::INTERFACE_ + path);
}

std::string Interface::linkContentAbsolute(std::string path)
{
    YAML::Node node = YAML_FILE::readFile(path);
    if(!loadName(node)) return "";
    
    if(node["textures"]) 
        loadSprites(node["textures"]);
    
    if(node["focus"]) 
        loadFocus(node["focus"]);
    else chooseImage(0, 0);

    if(node["object"]) 
        loadObject(node["object"]);

    if(node["collide"])
        loadCollide(node["collide"]);

    if(node["chunk"])
        loadChunk(node["chunk"]);

    if(node["control"])
        loadControl(node["control"]);

    if(node["event"])
        loadEvent(node["event"]);

    return getName();
}

void Interface::loadObject(YAML::Node node)
{
    for(auto i : node) 
    {
        Rectangle rel({0, 0, 0, 0});
        if(i["x"]) rel.x = i["x"].as<float>() / 100; 
        if(i["y"]) rel.y = i["y"].as<float>() / 100;
        if(i["w"]) rel.width = i["w"].as<float>() / 100;
        if(i["h"]) rel.height = i["h"].as<float>() / 100;
        Container *obj;
        obj = new Object(this, rel);
        obj->linkContent(i["path"].as<std::string>());
        containers.push_back(obj);
        if(i["main"] && i["main"].as<bool>()) 
            main = obj;
    }
}

void Interface::loadCollide(YAML::Node node)
{
}

void Interface::loadChunk(YAML::Node node)
{
}

void Interface::loadControl(YAML::Node node)
{
    for(auto stroke : node) 
    {
        KeyStroke* k = new KeyStroke();
        for(auto key : stroke["key"])
        {
            k->add(toKey(key.as<std::string>()));
        }
        std::string action = stroke["action"].as<std::string>();
        
        if(action == "move-object") 
        {
            int id = stroke["args"][0].as<int>();
            float x = stroke["args"][1].as<float>() / 100.0;
            float y = stroke["args"][2].as<float>() / 100.0;
            moveObjectAction* action = new moveObjectAction(containers[id], fPoint({x, y}));
            k->addAction(action);
        }

        keystrokes.push_back(k);
    }
}

void Interface::loadEvent(YAML::Node node)
{
}


