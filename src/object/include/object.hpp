#ifndef OBJECT_HPP 
#define OBJECT_HPP

#include <container.hpp>
#include <keystroke.hpp>

class Object : public Container
{
private: 
    std::vector<KeyStroke*> strokes;
    std::vector<std::vector<Action*> > actions;
protected: 
    void loadControl(YAML::Node node);

public: 
    Object(Frame*, Rectangle);
    Object(Object*);
    Object(Object*, Rectangle);
    Object(Object*, Frame*, Rectangle);
    ~Object();

    virtual std::string linkContent(std::string) override;
    virtual std::string linkContentAbsolute(std::string) override;
    
    virtual Action* react() override;
    void draw() override;
};

#endif 
