#include "raylib.h"
#include <visual.hpp>
#include <container.hpp>
#include <const/path/atb.hpp>
#include <const/path/assets.hpp>
#include <file.hpp>

int Container::id_count = 0;

Container::Container(Frame* parent, Rectangle rect) : Frame(parent, rect)
{
    instance_id = id_count++;
    focus = {0, 0};
    visible = true;
}

Container::Container(Container* other) : Frame(other)
{
    instance_id = id_count++;
    focus = {0, 0};
    name = other->name;
    visible = true;

    for(auto s : other->sprites) 
    {
        sprites.emplace_back();
        Rectangle rect;
        rect.x = other->getRelative()[0];
        rect.y = other->getRelative()[1];
        rect.width = other->getRelative()[2];
        rect.height = other->getRelative()[3];

        for(auto v : s)
        {
            sprites.back().push_back(new Visual(v, this, rect));
        }
    }
}

Container::Container(Container* other, Rectangle rect) : Frame(other)
{
    instance_id = id_count++;
    focus = {0, 0};
    name = other->name;
    setRelative({rect.x, rect.y, rect.width, rect.height});
    visible = true;

    for(auto s : other->sprites) 
    {
        sprites.emplace_back();
        Rectangle rect;
        rect.x = other->getRelative()[0];
        rect.y = other->getRelative()[1];
        rect.width = other->getRelative()[2];
        rect.height = other->getRelative()[3];

        for(auto v : s)
        {
            sprites.back().push_back(new Visual(v, this, rect));
        }
    }
}

Container::Container(Container* other, Frame* parent, Rectangle rect) : Frame(parent, rect)
{
    instance_id = id_count++;
    focus = {0, 0};
    name = other->name;
    visible = true;
    for(auto s : other->sprites) 
    {
        sprites.emplace_back();
        Rectangle rect;
        rect.x = other->getRelative()[0];
        rect.y = other->getRelative()[1];
        rect.width = other->getRelative()[2];
        rect.height = other->getRelative()[3];

        for(auto v : s)
        {
            sprites.back().push_back(new Visual(v, this, rect));
        }
    }
}

std::string Container::linkContent(std::string path)
{
    focus = {0, 0};
    return linkContentAbsolute(PATB::CONTAINER_ + path);
}

std::string Container::linkContentAbsolute(std::string path)
{
    YAML::Node node = YAML_FILE::readFile(path);
    if(!loadName(node)) return "";
    
    if(node["textures"])
    {
        
        loadSprites(node["textures"]);
    }

    if(node["focus"])
    {
        loadFocus(node["focus"]);
    }

    return name;
}

bool Container::loadName(YAML::Node node)
{
    if(!node["name"]) 
    {
        name = "";
        return false;
    }
    name = node["name"].as<std::string>();
    return true;
}

void Container::loadSprites(YAML::Node node)
{
    for(auto sprite : node)
    {
        if(!sprite["path"]) continue;
        if(!sprite["graphics"]) continue;

        std::string path = PASSETS::GRAPHIC_ + sprite["path"].as<std::string>();
        Image image = LoadImage(path.c_str());
            
        if(sprite["resize"])
        {
            int x = image.width * sprite["resize"][0].as<float>();
            int y = image.height * sprite["resize"][1].as<float>();
            ImageResize(&image, x, y);
        }
        
        sprites.emplace_back();
        for(auto img : sprite["graphics"]) 
        {
            float x, y, w, h;
            int repeat = 1;
            int gapX = 0;
            int gapY = 0;

            int dx = 1;
            int dy = 1;

            if(img["x"]) 
                x = img["x"].as<float>() / 100.0;
            else x = 0;
            if(img["y"]) 
                y = img["y"].as<float>() / 100.0;
            else y = 0;
            if(img["w"]) 
                w = img["w"].as<float>() / 100.0;
            else w = 1;
            if(img["h"]) 
                h = img["h"].as<float>() / 100.0;
            else h = 1;
            if(img["repeat"]) 
                repeat = img["repeat"].as<int>();
            if(img["gapX"])
                gapX = img["gapX"].as<int>();
            if(img["gapY"])
                gapY = img["gapY"].as<int>();

            if(img["dx"])
                dx = img["dx"].as<int>();
            if(dx < 0) dx = -1;
            else dx = 1;

            if(img["dy"])
                dy = img["dy"].as<int>();
            if(dy < 0) dy = -1;
            else dy = 1;
            
            int imgw = image.width;
            int imgh = image.height;

            if(img["axis"] && img["axis"].as<std::string>() == "horizontal")
            {
                for(float j = y; j >= 0 && j + h < 1 + 1e-2; j += dy * (gapY + h))
                {
                    for(float i = x; i >= 0 && i + w <= 1 + 1e-2 && repeat--; i += dx * (gapX + w))
                    {
                        Rectangle rect = {i * imgw, j * imgh, w * imgw, h * imgh};
                        Image img2 = ImageFromImage(image, rect);
                        Texture2D *txt = new Texture2D(LoadTextureFromImage(img2)); 
                        Visual *vis = new Visual(txt, this, {0, 0, 1, 1});
                        sprites.back().push_back(vis);

                        UnloadImage(img2);
                    }
                }
            }else 
            {
                for(float i = x; i >= 0 && i + w <= 1 + 1e-2; i += dx * (gapX + w))
                {
                    for(float j = y; j >= 0 && j + h < 1 + 1e-2 && repeat--; j += dy * (gapY + h))
                    {
                        Rectangle rect = {i * imgw, j * imgh, w * imgw, h * imgh};
                        Image img2 = ImageFromImage(image, rect);
                        Texture2D *txt = new Texture2D(LoadTextureFromImage(img2)); 
                        Visual *vis = new Visual(txt, this, {0, 0, 1, 1});
                        sprites.back().push_back(vis);

                        UnloadImage(img2);
                    }
                }
            }
        }
        UnloadImage(image);
    }
}

void Container::loadFocus(YAML::Node node)
{
    focus[0] = node[0].as<int>();
    focus[1] = node[1].as<int>();
}

void Container::chooseSprite(int index)
{
    if(sprites.empty()) return;
    if(index < 0 || index >= sprites.size()) return;
    focus[0] = index;
}

void Container::chooseImage(int index)
{
    if(sprites.empty()) return;
    if(index < 0 || index >= sprites.size()) return;
    focus[1] = index;
}

void Container::chooseImage(int index, int index2)
{
    if(sprites.empty()) return;
    if(index < 0 || index >= sprites.size()) return;
    if(index2 < 0 || index2 >= sprites.at(index).size()) return;
    focus[0] = index;
    focus[1] = index2;
}

void Container::nextImage()
{
    if(sprites.empty()) return;
    focus[1]++;
    if(focus[1] >= sprites.at(focus[0]).size()) focus[1] = 0;
}

void Container::prevImage()
{
    if(sprites.empty()) return;
    focus[1]--;
    if(focus[1] < 0) focus[1] = sprites.at(focus[0]).size() - 1;
}

void Container::nextSprite()
{
    if(sprites.empty()) return;
    focus[0]++;
    if(focus[0] >= sprites.size()) focus[0] = 0;
}

void Container::prevSprite()
{
    if(sprites.empty()) return;
    focus[0]--;
    if(focus[0] < 0) focus[0] = sprites.size() - 1;
}

std::string Container::getName()
{
    return name;
}

void Container::setProbability(int prob)
{
    probability = prob;
}

int Container::getProbability()
{
    return probability;
}
