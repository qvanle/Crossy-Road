#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include <vector>

#include <visual.hpp>
#include <frame.hpp>

class Container : public Frame
{
private:
    std::vector<Sprite> sprites;
protected:
    void loadSprites(YAML::Node& node);
public:
    Container(Frame*, Rectangle);
    void linkContent(std::string);
};

#endif 
