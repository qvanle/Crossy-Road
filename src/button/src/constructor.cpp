#include <button.hpp>


// Button for Image
ButtonImage::ButtonImage(Frame* parrent, Rectangle rel) : Container(parrent, rel)
{
     // set default
    this->chooseImage(0, this->tmpPath);
    this->color = WHITE;
    this->pressing = false;
    this->isHover = false;
    this->clicked = false;

    this->releaseID = -1;
    this->hoverID = -1;
    this->pressingID = -1;
    this->clickedID = -1;

    this->request = nullptr;
}

std::string ButtonImage::linkContent(std::string path)
{
    return linkContentAbsolute(PATB::BUTTON_ + path);
}

std::string ButtonImage::linkContentAbsolute(std::string path)
{
    YAML::Node node = YAML_FILE::readFile(path);
    if(!loadName(node)) return "";
    
    if(node["textures"])
    {
        loadSprites(node["textures"]);
        chooseImage(0, 0);
    }
    if(node["events"])
    {
        loadEvent(node["events"]);
    }
    
    if(node["action"])
    {
        loadAction(node["action"]);
    }
    return getName();
}

void ButtonImage::loadEvent(YAML::Node node)
{
    if(node["hover"])
    {
        
        for(auto sprite : node["hover"]["sprite"])
        {
            iPoint p;
            int delay = 0;
            p[0] = sprite[0].as<int>();
            p[1] = sprite[1].as<int>();
            if(p.size() >= 3) 
                delay = sprite[2].as<int>();
            actions.push_back(new changeImageAction(this, p));
        }
        this->hoverID = actions.size() - 1;
    }

    if(node["release"])
    {
        for(auto sprite : node["release"]["sprite"])
        {
            iPoint p;
            int delay = 0;
            p[0] = sprite[0].as<int>();
            p[1] = sprite[1].as<int>();
            if(p.size() >= 3) 
                delay = sprite[2].as<int>();
            actions.push_back(new changeImageAction(this, p));

        }
        this->releaseID = actions.size() - 1;
    }

    if(node["clicked"])
    {
        for(auto sprite : node["clicked"]["sprite"])
        {
            iPoint p;
            int delay = 0;
            p[0] = sprite[0].as<int>();
            p[1] = sprite[1].as<int>();
            if(p.size() >= 3) 
                delay = sprite[2].as<int>();
            actions.push_back(new changeImageAction(this, p));
        }
        this->clickedID = actions.size() - 1;
    }

    if(node["pressing"])
    {
        for(auto sprite : node["pressing"]["sprite"])
        {
            iPoint p;
            int delay = 0;
            p[0] = sprite[0].as<int>();
            p[1] = sprite[1].as<int>();
            if(p.size() >= 3) 
                delay = sprite[2].as<int>();
            actions.push_back(new changeImageAction(this, p));
        }
        this->pressingID = actions.size() - 1;
    }  
}