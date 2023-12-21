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
    }
}

void Interface::loadCollide(YAML::Node node)
{
}

void Interface::loadMap() 
{
    if(nested.empty()) return ;

    while(!chunks.empty())
    {
        fRect rec = chunks.back()->getRelative();
        if(rec[1] > 1) chunks.pop_back();
        else break;
    }
    if(chunks.empty()) 
    {
        int id = GetRandomValue(0, nested.size() - 1);
        Rectangle rel;
        rel.width = nested[id]->getRelative()[2];
        rel.height = nested[id]->getRelative()[3];
        rel.x = 0;
        rel.y = (1.01 - rel.height);

        Interface* chunk = new Interface(nested[id], this, rel);
        chunks.push_front(chunk);
    }
    while(chunks.front()->getRelative()[1] > 0)
    {
        Rectangle rel;
        rel.width = chunks.front()->getRelative()[2];
        rel.height = chunks.front()->getRelative()[3];
        rel.x = 0;
        rel.y = (chunks.front()->getRelative()[1] + 0.005 - rel.height);

        int id = GetRandomValue(0, nested.size() - 1);
        Interface* chunk = new Interface(nested[id], this, rel);
        chunks.push_front(chunk);
    }
}

void Interface::loadChunk(YAML::Node node)
{
    for(auto i : node) 
    {
        float x = 0, y = 0, w = 1, h = 1;
        int repeat = 1;
        std::string path = i["file"].as<std::string>();
        if(i["x"]) x = i["x"].as<float>() / 100;
        if(i["y"]) y = i["y"].as<float>() / 100;
        if(i["w"]) w = i["w"].as<float>() / 100;
        if(i["h"]) h = i["h"].as<float>() / 100;
        if(i["repeat"]) repeat = i["repeat"].as<int>();

        Chunk* chunk = new Chunk(this, {x, y, w, h}); 
        chunk->linkContent(path);
        nested.push_back(chunk);
        while(--repeat > 0) 
            nested.push_back(new Interface(nested[0]));
    }
    if(!nested.empty()) loadMap();
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


