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

    chooseImage(0, 0);

    return "";
}
