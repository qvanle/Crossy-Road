#include "container.hpp"
#include <object.hpp>
#include <const/path/atb.hpp>
#include <file.hpp>

Object::Object(Frame* f, Rectangle rel) : Container(f, rel)
{
    waitUntil = std::chrono::steady_clock::now();
}

Object::Object(Object* other) : Container(other)
{
    waitUntil = std::chrono::steady_clock::now();
}

Object::Object(Object* other, Rectangle rel) : Container(other, rel)
{
    waitUntil = std::chrono::steady_clock::now();
}

Object::Object(Object* other, Frame* f, Rectangle rel) : Container(other, f, rel)
{
    waitUntil = std::chrono::steady_clock::now();
}

std::string Object::linkContent(std::string path)
{
    return linkContentAbsolute(PATB::OBJECT_ + path);
}

std::string Object::linkContentAbsolute(std::string path)
{
    YAML::Node node = YAML_FILE::readFile(path);
    if(!loadName(node)) return "";
    if(node["textures"]) loadSprites(node["textures"]);
    if(node["control"]) loadControl(node["control"]);

    chooseImage(0, 0);
    if(node["focus"]) 
        loadFocus(node["focus"]);

    return "";
}

void Object::loadControl(YAML::Node node)
{
    for(auto stroke : node)
    {
        strokes.emplace_back();
        KeyStroke* k = new KeyStroke();
        for(auto key : stroke["key"])
        {
            k->add(toKey(key.as<std::string>()));
        }
        for(auto sprite : stroke["sprite"])
        {
            iPoint p;
            int delay = 0;
            p[0] = sprite[0].as<int>();
            p[1] = sprite[1].as<int>();
            if(p.size() >= 3) 
                delay = sprite[2].as<int>();
            k->addAction(new changeImageAction(this, p));
        }
        strokes.back().stroke = k;
    }
}
