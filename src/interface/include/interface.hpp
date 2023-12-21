#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <raylib.h>

#include <frame.hpp>
#include <container.hpp>
#include <keystroke.hpp>

class Interface : public Container
{
private: 
    friend class moveObjectAction;

    std::vector<Container*> containers;
    std::vector<Container*> visiter;
    std::vector<Interface*> nested;
    std::vector<KeyStroke*> keystrokes;
protected:
    void loadObject(YAML::Node);
    void loadControl(YAML::Node);

    void drawNested();
    void drawContainers();
    void drawVisiter();

public: 
    Interface(Frame*, Rectangle);
    Interface(Interface*);
    Interface(Interface*, Rectangle);
    Interface(Interface*, Frame*, Rectangle);

    ~Interface();

    void addVisiter(Container*);
    void addVisiter(Container*, Rectangle);
    Container* getContainers(int);

    std::string linkContent(std::string path) override;
    std::string linkContentAbsolute(std::string path) override;

    Action* react() override;
    Action* getRuntimeEvent() override;
    void draw() override;
};

class moveObjectAction : public Action
{
private: 
    Container* obj; 
    fPoint delta;
public: 
    moveObjectAction(Container* obj, fPoint delta);
    ~moveObjectAction();

    void execute() override;
    Action* clone() override;
};
#endif 
