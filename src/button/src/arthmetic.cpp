#include <button.hpp>
#include <request.hpp>


// Button for image

void ButtonImage::draw() {
    if(!isVisible()) return;
    this->Container::draw();
}

PacketAction* ButtonImage::react() {
    if(!isVisible()) return nullptr;
    if (CheckCollisionPointRec(GetMousePosition(), rectangle)) {
        this->isHover = 1;
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) { // click -> pressing
            this->clicked = true;
            if(this->pressingID == -1)
                return nullptr;
            PacketAction* packet = new PacketAction();
            packet->addAction(actions[pressingID]->clone());
            return packet;
        }
        else if(this->clicked) { // release -> click
            
            this->clicked = false;
            if(this->clickedID == -1)
                return nullptr;
            PacketAction* packet = new PacketAction();
            packet->addAction(actions[clickedID]->clone());
            if(request != nullptr)
                {
                    std::cout << "request" << std::endl;
                    packet->addAction(request->clone());}
            return packet;
        }
        if(this->hoverID == -1)
            return nullptr;
        PacketAction* packet = new PacketAction();
            packet->addAction(actions[hoverID]->clone());
            return packet;
    }
    if (this->isHover == 1)
    {
        this->isHover = 0;
        if(this->releaseID == -1)
            return nullptr;
        PacketAction* packet = new PacketAction();
            packet->addAction(actions[releaseID]->clone());
            return packet;
    }
    return nullptr;
}



void ButtonImage::changeIndex(int newindex)
{
    tmpPath = newindex;
}

int ButtonImage::getClicked()
{
    return tmpPath;
}

bool ButtonImage::isClicked() const {
    return this->clicked;
}

void ButtonImage::loadAction(YAML::Node node)
{
    if(!node) return;
    if(!node["type"]) return;

    if(node["type"].as<std::string>() == "change-interface")
    {
        if(!node["str"]) return;
        request = new changeInfRequest(node["str"][0].as<std::string>());
    }

     if(node["type"].as<std::string>() == "pop-interface")
    {
        request = new popInfRequest(); // TODO
    }

    if(node["type"].as<std::string>() == "pop-then-change-interface")
    {
        if(!node["str"]) return;
        request = new popThenChangeInfRequest(node["str"][0].as<std::string>());
    }
    if(node["type"].as<std::string>() == "load-game") 
    {
        request = new loadGameRequest();
    }
    if(node["type"].as<std::string>() == "save") 
    {
        if(!node["str"]) return;
        request = new saveRequest(node["str"][0].as<std::string>());
    }
    if(node["type"].as<std::string>() == "toggle-music") 
    {
        request = new toggleMusicRequest();
    }
    if(node["type"].as<std::string>() == "close-inputbox") 
    {
        request = new closeInputboxRequest();
    }
     if(node["type"].as<std::string>() == "open-inputbox") 
    {
        request = new openInputboxRequest();
    }
}

popInfRequest::popInfRequest()
{  

}

popInfRequest::popInfRequest(popInfRequest* request)
{
    
}

int popInfRequest::isRequest()
{
    return REQUEST::ID::POP_INF;
}

Action* popInfRequest::clone()
{
    return new popInfRequest(this);
}

popThenChangeInfRequest::popThenChangeInfRequest(std::string s)
{  
    args.str.push_back(s);
}

popThenChangeInfRequest::popThenChangeInfRequest(popThenChangeInfRequest* other)
{
    args = other->args;
}

int popThenChangeInfRequest::isRequest()
{
    return REQUEST::ID::POP_THEN_CHANGE_INF;
}

Action* popThenChangeInfRequest::clone()
{
    return new popThenChangeInfRequest(this);
}

ARGS& popThenChangeInfRequest::getArgs() 
{
    return args;
}


int loadGameRequest::isRequest()
{
    return REQUEST::ID::LOAD_GAME;
}

Action* loadGameRequest::clone()
{
    return new loadGameRequest();
}

int toggleMusicRequest::isRequest()
{
    return REQUEST::ID::TOGGLE_MUSIC;
}

Action* toggleMusicRequest::clone()
{
    return new toggleMusicRequest();
}

closeInputboxRequest::closeInputboxRequest()
{  

}

closeInputboxRequest::closeInputboxRequest(closeInputboxRequest* request)
{

}
int closeInputboxRequest::isRequest()
{
    return REQUEST::ID::CLOSE_INPUTBOX;
}

Action* closeInputboxRequest::clone()
{
    return new closeInputboxRequest(this);
}

openInputboxRequest::openInputboxRequest()
{  

}

openInputboxRequest::openInputboxRequest(openInputboxRequest* request)
{

}

int openInputboxRequest::isRequest()
{
    return REQUEST::ID::OPEN_INPUTBOX;
}

Action* openInputboxRequest::clone()
{
    return new openInputboxRequest(this);
}
saveRequest::saveRequest(std::string s) : changeInfRequest(s)
{
}

int saveRequest::isRequest()
{
    return REQUEST::ID::SAVE_GAME;
}

Action* saveRequest::clone()
{
    return new saveRequest(args.str[0]);
}
