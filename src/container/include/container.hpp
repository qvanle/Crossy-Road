#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include <vector>

#include <visual.hpp>
#include <frame.hpp>
#include <action.hpp>
#include <const/datatype.hpp>
#include <const/path/atb.hpp>
#include <file.hpp>

/**
 * @class Container
 *
 * @brief contains specific sprites and their behavior
 *
**/
class Container : public Frame
{
private:
    friend class changeImageAction;
    static int id_count; ///< counter of all containers created
    int instance_id; ///< ID of the container
    int probability;

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

    void setProbability(int);
    int getProbability();
    
    /**
     * @brief choose a specific sprite from a vector of sprites
     */
    void chooseSprite(int);

    /**
     * @brief choose the state of the sprite
     */
    void chooseImage(int);

    /**
     * @brief choose the state of the sprite
     */
    void chooseImage(int, int);

    /**
     * @brief move to next state of the sprite
     */
    void nextImage();

    /**
     * @brief move to previous state of the sprite
     */
    void prevImage();

    /**
     * @brief move to the next sprite
     */
    void nextSprite();

    /**
     * @brief move to the previous sprite
     */
    void prevSprite();

    bool isOverlapping(fPoint);
    bool isOverlapping(Rectangle);
    bool isOverlapping(Container*);
    float OverlappingArea(Rectangle);
    float OverlappingArea(Container*);

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
