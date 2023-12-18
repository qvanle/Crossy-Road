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
    std::vector<KeyStroke*> keystrokes;

protected:
    void loadObject(YAML::Node);
    void loadCollide(YAML::Node);
    void loadChunk(YAML::Node);
    void loadControl(YAML::Node);
    void loadEvent(YAML::Node);
public: 
    Interface(Frame*, Rectangle);
    Interface(Interface*);
    Interface(Interface*, Rectangle);
    Interface(Interface*, Frame*, Rectangle);

    ~Interface();

    std::string linkContent(std::string path) override;
    std::string linkContentAbsolute(std::string path) override;

    Action* react() override;

    void draw() override;
	
	void push(Container* contain) override;
	void pop() override;
	Container* get() override;
	
	Action* getRuntimeEvent() override;
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
    void Interrupt() override;
    void ForceEnd() override;
    Action* clone() override;
};
#endif 
