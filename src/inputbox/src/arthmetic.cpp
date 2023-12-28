#include "raylib.h"
#include <inputbox.hpp>
#include<thread>

void InputBox::draw()
{
    DrawRectangleRec(this->getFrame(), LIGHTGRAY); // can change by texture in yaml file

    if (isActivated) DrawRectangleLines((int)this->getFrame().x, (int)this->getFrame().y, (int)this->getFrame().width, (int)this->getFrame().height, RED);
    else DrawRectangleLines((int)this->getFrame().x, (int)this->getFrame().y, (int)this->getFrame().width, (int)this->getFrame().height, DARKGRAY);

    DrawText(rawText.c_str(), (int)this->getFrame().x + 5, (int)this->getFrame().y + 8, this->fontSize, MAROON);
    if (isActivated)
    {
        if (letterCount < MAX_LENGTH)
        {
            // Draw blinking underscore char
            if (((framesCounter/20)%2) == 0) 
                DrawText("_", (int)this->getFrame().x + 8 + MeasureText(rawText.c_str(), this->fontSize), (int)this->getFrame().y + 12, this->fontSize, MAROON);
        }
        else
            DrawText("You reach the MAX LENGHT of name !!!", (int)this->getFrame().x + this->fontSize * 1.1, (int)this->getFrame().y + this->fontSize * 2, this->fontSize * 0.5, RED);
    }
    //std::cout<<rawText<<std::endl; // for debug
}


PacketAction* InputBox::react()
{
    bool cur = (CheckCollisionPointRec(GetMousePosition(), this->getFrame()));

    PacketAction* packet = nullptr;
    if(cur != isActivated)
    {
        Action* action = new setActivateAction(this, cur);
        packet = new PacketAction();
        packet->addAction(action);
    }
    if(cur == false) return packet;
    if(std::chrono::steady_clock::now() - lastTyping < typing_delay) 
        return packet;
    int c = -1;
    std::string s = rawText;
    

    for(int i = 32; i <= 96 && s.size() < MAX_LENGTH; i++) 
    {
        if(!IsKeyDown(i)) continue; 
        c = i;
        if(KEY_ZERO <= c && c <= KEY_NINE) 
            c = c;
        else if(KEY_A <= c && c <= KEY_Z && !IsKeyDown(KEY_LEFT_SHIFT) && !IsKeyDown(KEY_RIGHT_SHIFT) && !IsKeyDown(KEY_CAPS_LOCK)) 
            c += 32;
        else if((c < KEY_A || c > KEY_Z) && IsKeyDown(KEY_LEFT_SHIFT) && IsKeyDown(KEY_RIGHT_SHIFT)) 
            c += 32;
        s += c;
        break; 
    }

    if(IsKeyDown(KEY_BACKSPACE) && rawText.size() > 0) 
    {
        s.pop_back();
        c = 0;
    }

    if(c == -1) 
    {
        lastTyping = std::chrono::steady_clock::now();
        return packet;
    }
    Action* action = new setRawTextAction(this, s);
    if(packet == nullptr) packet = new PacketAction();
    packet->addAction(action);
    lastTyping = std::chrono::steady_clock::now();
    return packet;
}


std::string InputBox::linkContent(std::string path)
{
    return linkContentAbsolute(PATB::INPUTBOX_ + path);
}

std::string InputBox::linkContentAbsolute(std::string path)
{
    YAML::Node node = YAML_FILE::readFile(path);
    if(!loadName(node)) return "";

    // if(node["object"]) 
    //     loadObject(node["object"]);

    // if(node["textures"])
    // {
    //     loadSprites(node["textures"]);
    //     chooseImage(0, 0);
    // }
    // if(node["events"])
    // {
    //     loadEvent(node["events"]);
    // }
    if(node["fontsize"])
    {
        this->fontSize = node["fontsize"].as<int>();
    }
    if(node["object"])
    {
        //     this->getFrame().x = node["object"]["x"].as<float>() / 100 * this->root->getFrame().width + this->root->getFrame().x;
        //     this->getFrame().y = node["object"]["y"].as<float>() / 100 * this->root->getFrame().height + this->root->getFrame().y;
        //     this->getFrame().width = node["object"]["w"].as<float>() / 100 * this->root->getFrame().width;
        //     this->getFrame().height = node["object"]["h"].as<float>() / 100 * this->root->getFrame().height;
    }
    return getName();
}

void InputBox::loadEvent(YAML::Node node)
{
    // if(node["hover"])
    // {

    //     for(auto sprite : node["hover"]["sprite"])
    //     {
    //         iPoint p;
    //         int delay = 0;
    //         p[0] = sprite[0].as<int>();
    //         p[1] = sprite[1].as<int>();
    //         if(p.size() >= 3) 
    //             delay = sprite[2].as<int>();
    //         actions.push_back(new changeImageAction(this, p));
    //     }
    //     this->hoverID = actions.size() - 1;
    // }

    // if(node["release"])
    // {
    //     for(auto sprite : node["release"]["sprite"])
    //     {
    //         iPoint p;
    //         int delay = 0;
    //         p[0] = sprite[0].as<int>();
    //         p[1] = sprite[1].as<int>();
    //         if(p.size() >= 3) 
    //             delay = sprite[2].as<int>();
    //         actions.push_back(new changeImageAction(this, p));

    //     }
    //     this->releaseID = actions.size() - 1;
    // }

    // if(node["clicked"])
    // {
    //     for(auto sprite : node["clicked"]["sprite"])
    //     {
    //         iPoint p;
    //         int delay = 0;
    //         p[0] = sprite[0].as<int>();
    //         p[1] = sprite[1].as<int>();
    //         if(p.size() >= 3) 
    //             delay = sprite[2].as<int>();
    //         actions.push_back(new changeImageAction(this, p));
    //     }
    //     this->clickedID = actions.size() - 1;
    // }

    // if(node["pressing"])
    // {
    //     for(auto sprite : node["pressing"]["sprite"])
    //     {
    //         iPoint p;
    //         int delay = 0;
    //         p[0] = sprite[0].as<int>();
    //         p[1] = sprite[1].as<int>();
    //         if(p.size() >= 3) 
    //             delay = sprite[2].as<int>();
    //         actions.push_back(new changeImageAction(this, p));
    //     }
    //     this->pressingID = actions.size() - 1;
    // }  
}

std::string InputBox::getText()
{
    return rawText;
}

void InputBox::clear()
{
    rawText = "";
    letterCount = 0;
}


std::vector<std::pair<int, std::string>> highScore::getList()
{
    return list;
}

void highScore::add(std::string name, int score)
{
    for(int i=0; i<list.size(); i++)
    {
        if(list[i].second == name)
        {
            if(list[i].first < score)
            {
                list[i].first = score;
                // std::cout<<"Update score of "<<name<<" to "<<score<<std::endl;
            }
            return;
        }
    }
    list.push_back(std::make_pair(score, name));
}

void highScore::save(std::string path)
{
    std::ofstream fo;
    fo.open(path);
    for(auto i : list)
    {
        fo<<i.first<<" "<<i.second<<std::endl;
    }
    fo.close();
}