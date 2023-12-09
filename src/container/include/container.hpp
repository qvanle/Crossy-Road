#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include <vector>
#include <memory>

#include <visual.hpp>
#include <frame.hpp>

class Container : public Frame
{
private:
    static int id_count;
    int instance_id;

    std::shared_ptr< std::vector<Sprite> > sprites;
    std::string name;
    iPoint focus;
    bool visible;

protected:
    void loadSprites(YAML::Node node);
public:
    Container(Frame*, Rectangle);
    Container(Container*);
    Container(Container*, Rectangle);
    Container(Container*, Frame*, Rectangle);
    ~Container();

    std::string linkContent(std::string);
    std::string linkContentAbsolute(std::string);

    void chooseSprite(int);
    void chooseImage(int);
    void chooseImage(int, int);

    void draw();
    void show();
    void hide();
    void toggleVisibility();
    bool isVisible();
    int getInstanceId();
};

#endif 
