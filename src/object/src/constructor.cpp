#include <object.hpp>

Object::Object(Frame* par, Rectangle rel) : Frame(par, rel)
{
    visible = true;
    focus = {0, 0};
}

Object::Object(Frame* self) : Frame(self) 
{
    visible = true;
    focus = {0, 0};
}

Object::Object(Rectangle frame) : Frame(frame) 
{
    visible = true;
    focus = {0, 0};
}

void Object::setContent(YAML::Node* content)
{
    // if not have "name" throw error 
    
    if (!(*content)["name"]) 
    {
        throw std::runtime_error("Object must have name");
        return ;
    }

    name = (*content)["name"].as<std::string>();
    if ((*content)["visible"]) 
        visible = (*content)["visible"].as<bool>();
    if((*content)["textures"])
        loadTextures((*content)["textures"]);
}

void Object::loadTextures(YAML::Node content)
{
    for (auto i : content)
    {

        sprites.emplace_back();
        std::string path = i["path"].as<std::string>();
        Image img = LoadImage(path.c_str());

        for(auto spr : i["graphics"])
        {
            float x = 0, y = 0, w = 1, h = 1;
            int repeat = 1;
            float gapX = 0, gapY = 0;

            std::string direction = "right";

            if(spr["x"]) x = spr["x"].as<float>();
            if(spr["y"]) y = spr["y"].as<float>();
            if(spr["w"]) w = spr["w"].as<float>();
            if(spr["h"]) h = spr["h"].as<float>();
            if(spr["gapX"]) gapX = spr["gapX"].as<float>();
            if(spr["gapY"]) gapY = spr["gapY"].as<float>();

            if(spr["repeat"]) repeat = spr["repeat"].as<int>();
            if(spr["direction"])direction = spr["direction"].as<std::string>();
            

            if(direction == "right")
            {
                for(float i = x; i < 1; i += w + gapX)
                {
                    for(float j = y; j < 1 && repeat-- > 0; j += h + gapY)
                    {
                        float cx = img.width * i;
                        float cy = img.height * j;
                        float cw = img.width * w;
                        float ch = img.height * h;
                        
                        Image crop = ImageFromImage(img, Rectangle{cx, cy, cw, ch});
                        Texture2D *tex = new Texture2D(LoadTextureFromImage(crop));
                        sprites.back().push_back(new Visual(tex, getFrame()));
                    }
                }
            }else if(direction == "left")
            {
                for(float i = x; i < 1; i += w + gapX)
                {
                    for(float j = y; j >= 0 && repeat-- > 0; j -= h + gapY)
                    {
                        float cx = img.width * i;
                        float cy = img.height * j;
                        float cw = img.width * w;
                        float ch = img.height * h;
                        
                        Image crop = ImageFromImage(img, Rectangle{cx, cy, cw, ch});
                        Texture2D *tex = new Texture2D(LoadTextureFromImage(crop));
                        sprites.back().push_back(new Visual(tex, this));
                    }
                }

            }else if(direction == "up")
            {
                for(float j = y; j < 1; j += h + gapY)
                {
                    for(float i = x; i < 1 && repeat-- > 0; i += w + gapX)
                    {
                        float cx = img.width * i;
                        float cy = img.height * j;
                        float cw = img.width * w;
                        float ch = img.height * h;
                        
                        Image crop = ImageFromImage(img, Rectangle{cx, cy, cw, ch});
                        Texture2D *tex = new Texture2D(LoadTextureFromImage(crop));
                        sprites.back().push_back(new Visual(tex, this));
                    }
                }

            }else if(direction == "down")
            {
                for(float j = y; j >= 0; j -= h + gapY)
                {
                    for(float i = x; i < 1 && repeat-- > 0; i += w + gapX)
                    {
                        float cx = img.width * i;
                        float cy = img.height * j;
                        float cw = img.width * w;
                        float ch = img.height * h;
                        
                        Image crop = ImageFromImage(img, Rectangle{cx, cy, cw, ch});
                        Texture2D *tex = new Texture2D(LoadTextureFromImage(crop));
                        sprites.back().push_back(new Visual(tex, this));
                    }
                }
            }
        }
    }
}
