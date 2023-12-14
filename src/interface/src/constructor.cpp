#include <interface.hpp>
#include <const/path/atb.hpp>
#include <file.hpp>

Interface::Interface(Frame* frame, Rectangle rect) : Container(frame, rect)
{
}

Interface::Interface(Interface* other) : Container(other)
{
}

Interface::Interface(Interface* other, Rectangle rect) : Container(other, rect)
{
}

Interface::Interface(Interface* other, Frame* frame, Rectangle rect) : Container(other, frame, rect)
{
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
}

void Interface::loadCollide(YAML::Node node)
{
}

void Interface::loadChunk(YAML::Node node)
{
}

void Interface::loadControl(YAML::Node node)
{
}

void Interface::loadEvent(YAML::Node node)
{
}


