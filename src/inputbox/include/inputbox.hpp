#ifndef INPUTBOX_HPP
#define INPUTBOX_HPP 

#include <interface.hpp>
#include <string>
#include <cstring>
class InputBox : public Interface
{
private:

    // handle constant in file yaml
    static constexpr int MAX_LENGTH = 15;
    static constexpr int  FRAMES_PER_SECOND = 30;
    Texture textureBlank;

    // crucial parameters
    int fontSize, framesCounter;
    Font* font;
    std::string showText, rawText;

    bool isActivated, isFlicked;
    int letterCount;

    Frame* root;
protected:
    void loadEvent(YAML::Node node);
public:
    InputBox(int fontSize, Rectangle relative, Frame* root, Font* font);

    void draw();
    void handle();
    void update();

    /*void setList(std::vector<std::pair<std::string, std::string>> list);*/
    int getChoseId();
    std::string getText();
    PacketAction* react();
    std::string linkContent(std::string);
    std::string linkContentAbsolute(std::string);
};



#endif 

