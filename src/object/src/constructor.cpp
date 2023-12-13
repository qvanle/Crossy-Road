#include "container.hpp"
#include <object.hpp>
#include <const/path/atb.hpp>
#include <file.hpp>

Object::Object(Frame* f, Rectangle rel) : Container(f, rel)
{
}

Object::Object(Object* other) : Container(other)
{
}

Object::Object(Object* other, Rectangle rel) : Container(other, rel)
{
}

Object::Object(Object* other, Frame* f, Rectangle rel) : Container(other, f, rel)
{
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

    return "";
}

void Object::loadControl(YAML::Node node)
{
    currentDelay = -1;
    for(auto stroke : node)
    {
        KeyStroke* k = new KeyStroke();
        for(auto key : stroke["key"])
        {
            k->add(toKey(key.as<std::string>()));
        }
        for(auto sprite : stroke["sprite"])
        {
            iPoint p;
            p[0] = sprite[0].as<int>();
            p[1] = sprite[1].as<int>();
            k->addAction(new changeImageAction(this, p));
        }
        strokes.push_back(k);

        for(auto duration : stroke["duration"])
        {
            // milliseconds
            actionDelay.push_back(std::chrono::duration<double>(duration.as<int>()) / 1000.0);
        }

    }
}
