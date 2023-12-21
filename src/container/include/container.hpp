#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include <vector>

#include <visual.hpp>
#include <frame.hpp>
#include <action.hpp>

class Container : public Frame
{
private:
    friend class changeImageAction;
    static int id_count;
    int instance_id;

    std::vector<Sprite> sprites;
    std::string name;
    iPoint focus;
    bool visible;

protected:
    bool loadName(YAML::Node node);
    void loadSprites(YAML::Node node);
    void loadFocus(YAML::Node node);
public:
    Container(Frame*, Rectangle);
    Container(Container*);
    Container(Container*, Rectangle);
    Container(Container*, Frame*, Rectangle);
    virtual ~Container();

    virtual std::string linkContent(std::string);
    virtual std::string linkContentAbsolute(std::string);
    std::string getName();
    
    void chooseSprite(int);
    void chooseImage(int);
    void chooseImage(int, int);

    virtual void draw();
    void show();
    void hide();
    void toggleVisibility();
    bool isVisible();
    int getInstanceId();

    virtual Action* react();
    virtual Action* getRuntimeEvent();
};
class changeImageAction : public Action
{
private: 
    Container* container;
    iPoint focus; 
public: 
    changeImageAction(Container*, iPoint);
    changeImageAction(changeImageAction*);
    ~changeImageAction();
    void execute() override; 
    Action* clone() override;
};
#endif 
