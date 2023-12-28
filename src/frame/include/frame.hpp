#ifndef FRAME_HPP
#define FRAME_HPP

#include <iostream>
#include <vector>
#include <string>
#include <mutex>

#include <raylib.h>
 
#include <const/datatype.hpp>

/**
 * @class Frame
 *
 * @brief position and size of object on screen
 * 
 * When change position or size, it also change position and size of all subframes
 * 
 * a subframe is relative to its parent by percentage (0.0f to 1.0f)
 *
**/

class Frame 
{
private: 
    Rectangle frame;
    std::vector<Frame*> subframes;
    Frame* parent;
    
    fRect relative;

    mutable std::mutex mtx;
protected:
    virtual void updateFrame(bool recursive = false);
    bool isroot() const;
    void addSubframe(Frame* subframe);
    void removeSubframe(Frame* subframe);

    void beginUpdate();
    void endUpdate();
public:
    Frame(Frame* par, Rectangle rel);
    Frame(Frame* self);
    Frame(Rectangle rec);
    ~Frame();
    
    void plug(Frame* par, fRect rel);
    void plug(Frame* par);
    void unplug();

    void moveTo(fPoint rel);
    void moveTo(int x, int y);

    void moveCenterTo(fPoint rel);
    void moveCenterTo(int x, int y);

    void moveBy(fPoint rel);
    void moveBy(int, int);

    void resize(fPoint rel);
    void resize(int w, int h);

    const Rectangle& getFrame() const;
    const fRect& getRelative() const;
    Frame* getParent();

    void setRelative(fRect rel);

    const fPoint& getCenter() const;
    
    const float& getX() const;
    const float& getY() const;
    const float& getW() const;
    const float& getH() const;
    
    operator Rectangle() const;
    operator fRect() const;
    operator iRect() const;

};

#endif 
