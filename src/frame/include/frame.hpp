#ifndef FRAME_HPP
#define FRAME_HPP

#include <iostream>
#include <vector>
#include <string>

#include <raylib.h>

#include <const/datatype.hpp>

class Frame 
{
private: 
    Rectangle frame;
    std::vector<Frame*> subframes;
    Frame* parent;
    
    fRect relative;
protected:
    virtual void updateFrame(bool recursive = false);
    bool isroot();
    void addSubframe(Frame* subframe);
    void removeSubframe(Frame* subframe);
public:
    Frame(Frame* par, Rectangle rel);
    Frame(Frame* self);
    Frame(Rectangle rec);
    ~Frame();
    
    void plug(Frame* par, fRect rel);
    void plug(Frame* par);
    void unplug();

    void moveTo(fPoint rel);
    void moveCenterTo(fPoint rel);

    void moveBy(fPoint rel);

    void resize(fPoint rel);
    void resize(int w, int h);

    const Rectangle& getFrame() const;
    const fRect& getRelative() const;

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
