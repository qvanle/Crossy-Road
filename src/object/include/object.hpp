#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <string>

#include <raylib.h>

#include <file.hpp>
#include <visual.hpp>
#include <const/datatype.hpp>

class Object : public Frame 
{
private:
    std::vector<Sprite> sprites;
    bool visible;   
    iPoint focus;

    std::string name;
protected:
    void loadLocation(YAML::Node content);
    void loadTextures(YAML::Node content);

    void clearSprites();
public: 
    Object(Frame* par, Rectangle rel);
    Object(Frame* self);
    Object(Rectangle);
    ~Object();
    
    void setContent(YAML::Node* content);

    void draw();

    void hide();
    void show();
    void toggleVisibility();
    bool isVisible();

    void nextSprite();
    void prevSprite();
    void setSprite(int index);

    void nextTexture();
    void prevTexture();
    void setTexture(int index);
};

#endif 
