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
    sprites = nullptr;
    visible = true;
}

Container::Container(Container* other) : Frame(other)
{
    instance_id = id_count++;
    focus = {0, 0};
    name = other->name;
    sprites = other->sprites;
    visible = true;
}

Container::Container(Container* other, Rectangle rect) : Frame(other)
{
    instance_id = id_count++;
    sprites = nullptr;
    focus = {0, 0};
    name = other->name;
    sprites = other->sprites;
    setRelative({rect.x, rect.y, rect.width, rect.height});
    visible = true;
}

Container::Container(Container* other, Frame* parent, Rectangle rect) : Frame(parent, rect)
{
    instance_id = id_count++;
    sprites = nullptr;
    focus = {0, 0};
    name = other->name;
    sprites = other->sprites;
    visible = true;
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
    sprites = std::make_shared< std::vector<Sprite> >();
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
        
        sprites->emplace_back();
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
                        sprites->back().push_back(vis);

                        UnloadImage(img2);
                    }
                }
            }
        }
        UnloadImage(image);
    }
}

void Container::chooseSprite(int index)
{
    if(!sprites) return;
    if(index < 0 || index >= sprites->size()) return;
    focus[0] = index;
}

void Container::chooseImage(int index)
{
    if(!sprites) return;
    if(index < 0 || index >= sprites->size()) return;
    focus[1] = index;
}

void Container::chooseImage(int index, int index2)
{
    if(!sprites) return;
    if(index < 0 || index >= sprites->size()) return;
    if(index2 < 0 || index2 >= sprites->at(index).size()) return;
    focus[0] = index;
    focus[1] = index2;
}

std::string Container::getName()
{
    return name;
}
