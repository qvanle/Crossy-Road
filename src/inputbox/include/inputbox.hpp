#ifndef INPUTBOX_HPP
#define INPUTBOX_HPP 

#include <interface.hpp>
#include <string>
#include <chrono>
#include <cstring>
#include <fstream>
#include <sstream>

static std::chrono::duration<double> typing_delay = std::chrono::duration<double>(70 / 1000.0);

class InputBox : public Interface
{
private:

    friend class setActivateAction;
    friend class setRawTextAction;
    // handle constant in file yaml
    static constexpr int MAX_LENGTH = 15;
    static constexpr int  FRAMES_PER_SECOND = 30;
    Texture textureBlank;
    // crucial parameters
    int fontSize, framesCounter;
    Font* font;
    std::string showText, rawText;
    std::chrono::time_point<std::chrono::steady_clock> lastTyping;

    bool isActivated, isFlicked;
    int letterCount;

    Frame* root;
protected:
    void loadEvent(YAML::Node node);
public:
    InputBox(int fontSize, Rectangle relative, Frame* root, Font* font);

    void draw();
    void clear();

    /*void setList(std::vector<std::pair<std::string, std::string>> list);*/
    int getChoseId();
    std::string getText();
    PacketAction* react();
    std::string linkContent(std::string);
    std::string linkContentAbsolute(std::string);
};

class setActivateAction : public Action 
{
private: 
    InputBox* but;
    bool b;
public: 
    setActivateAction(InputBox* but, bool b);
    setActivateAction(setActivateAction* other);
    void execute();
    Action* clone();
};

class setRawTextAction : public Action 
{
private: 
    InputBox* but;
    std::string s;
public:
    setRawTextAction(InputBox* but, std::string s);
    setRawTextAction(setRawTextAction* other);
    void execute();
    Action* clone();
};

class highScore
{
private:
    std::vector<std::vector<std::pair<int, std::string>>> list;
public:
    highScore(std::string path);
    std::vector<std::pair<int, std::string>> getList(int level);
    void add(std::string name, int score, int level);
    void save(std::string path, int level);
};

#endif 

