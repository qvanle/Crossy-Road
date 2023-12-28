#include <button.hpp>
#include <request.hpp>


// Button for image

void ButtonImage::draw() {
    if(!isVisible()) return;
    this->Container::draw();
}

PacketAction* ButtonImage::react() {
   
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
        request = new popInfRequest(); 
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