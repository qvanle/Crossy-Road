#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <raylib.h>

#include <frame.hpp>
#include <container.hpp>

class Interface : public Container
{
private: 
    std::vector<Container*> containers;

public: 
    Interface(Frame*, Rectangle);
    Interface(Interface*);
    Interface(Interface*, Rectangle);
    Interface(Interface*, Frame*, Rectangle);

    ~Interface();

    std::string linkContent(std::string path) override;

    Action* react() override;

    void draw() override;
};

#endif 
