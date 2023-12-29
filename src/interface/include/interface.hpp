#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include "action.hpp"
#include <raylib.h>

#include <frame.hpp>
#include <container.hpp>
#include <keystroke.hpp>
#include <button.hpp>

/**
 * @class Interface
 *
 * @brief where user can interact with the game
 * 
 * manages containers, all actions, subframes etc.
 * 
**/
class Interface : public Container
{
private: 
    friend class moveObjectAction;

    std::vector<Container*> containers;
    std::vector<Interface*> nested;
    std::vector<KeyStroke*> keystrokes;
protected:
    void loadObject(YAML::Node);
    void loadControl(YAML::Node);
    void loadButton(YAML::Node);
    void drawNested();
    void drawContainers();

public: 
    Interface(Frame*, Rectangle);
    Interface(Interface*);
    Interface(Interface*, Rectangle);
    Interface(Interface*, Frame*, Rectangle);

    ~Interface();

    Container* getContainers(int);
    int getContainersSize();

    std::string linkContent(std::string path) override;
    std::string linkContentAbsolute(std::string path) override;

    Action* react() override;
    Action* getRuntimeEvent() override;
    void draw() override;
};

/**
 * @class moveObjectAction
 *
 * @brief manages the features of a movement, including which object, speed, direction etc.
 * 
**/
class moveObjectAction : public Action
{
private: 
    Container* obj; 
    fPoint delta;
    fPoint dir;
    float speed;
public: 
    moveObjectAction(Container* obj, fPoint delta);
    moveObjectAction(Container* obj, fPoint dir, float speed);
    ~moveObjectAction();

    void execute() override;
    Action* clone() override;
};
#endif 
