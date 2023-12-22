#include "raylib.h"
#include <interface.hpp>
#include <const/path/atb.hpp>
#include <file.hpp>
#include <object.hpp>
#include <chunk.hpp>

Interface::Interface(Frame* frame, Rectangle rect) : Container(frame, rect)
{
}

Interface::Interface(Interface* other) : Container(other)
{
    for(auto i : other->nested)
    {
        Rectangle rel;
        rel.x = i->getRelative()[0];
        rel.y = i->getRelative()[1];
        rel.width = i->getRelative()[2];
        rel.height = i->getRelative()[3];
        nested.push_back(new Interface(i, this, rel));
    }
    for(auto i : other->containers)
    {
        Rectangle rel;
        rel.x = i->getRelative()[0];
        rel.y = i->getRelative()[1];
        rel.width = i->getRelative()[2];
        rel.height = i->getRelative()[3];
        containers.push_back(new Container(i, this, rel));
    }

    for(auto i : other->visiter)
    {
        Rectangle rel;
        rel.x = 1;
        rel.y = -0.375;
        rel.width = i->getRelative()[2];
        rel.height = i->getRelative()[3];
        visiter.push_back(new Container(i, this, rel));
    }
}

Interface::Interface(Interface* other, Rectangle rect) : Container(other, rect)
{
    for(auto i : other->nested)
    {
        Rectangle rel;
        rel.x = i->getRelative()[0];
        rel.y = i->getRelative()[1];
        rel.width = i->getRelative()[2];
        rel.height = i->getRelative()[3];
        nested.push_back(new Interface(i, this, rel));
    }
    for(auto i : other->containers)
    {
        Rectangle rel;
        rel.x = i->getRelative()[0];
        rel.y = i->getRelative()[1];
        rel.width = i->getRelative()[2];
        rel.height = i->getRelative()[3];
        containers.push_back(new Container(i, this, rel));
    }
    for(auto i : other->visiter)
    {
        Rectangle rel;
        rel.x = 1;
        rel.y = -0.375;
        rel.width = i->getRelative()[2];
        rel.height = i->getRelative()[3];
        visiter.push_back(new Container(i, this, rel));
    }
}

Interface::Interface(Interface* other, Frame* frame, Rectangle rect) : Container(other, frame, rect)
{
    for(auto i : other->nested)
    {
        Rectangle rel;
        rel.x = i->getRelative()[0];
        rel.y = i->getRelative()[1];
        rel.width = i->getRelative()[2];
        rel.height = i->getRelative()[3];
        nested.push_back(new Interface(i, this, rel));
    }
    for(auto i : other->containers)
    {
        Rectangle rel;
        rel.x = i->getRelative()[0];
        rel.y = i->getRelative()[1];
        rel.width = i->getRelative()[2];
        rel.height = i->getRelative()[3];
        containers.push_back(new Container(i, this, rel));
    }
    for(auto i : other->visiter)
    {
        Rectangle rel;
        rel.x = 1;
        rel.y = -0.375;
        rel.width = i->getRelative()[2];
        rel.height = i->getRelative()[3];
        visiter.push_back(new Container(i, this, rel));
    }
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

    if(node["control"])
        loadControl(node["control"]);

//    if(node["collide"])
//        loadCollide(node["collide"]);

//    if(node["chunk"])
//        loadChunk(node["chunk"]);


//    if(node["event"])
//        loadEvent(node["event"]);

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
    }
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

void Interface::addVisiter(Container* obj)
{
    Rectangle rel;
    rel.x = obj->getRelative()[0];
    rel.y = obj->getRelative()[1];
    rel.width = obj->getRelative()[2];
    rel.height = obj->getRelative()[3];

    Container* c = new Container(obj, this, rel);
    visiter.push_back(c);
}

void Interface::addVisiter(Container* obj, Rectangle rel)
{
    Container* c = new Container(obj, this, rel);
    visiter.push_back(c);
}

Container* Interface::getContainers(int id)
{
    if(id < 0 || id >= containers.size()) return nullptr;
    return containers[id];
}
