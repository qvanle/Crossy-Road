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
    void updateFrame(bool recursive = false);
    bool isroot();
    void addSubframe(Frame* subframe);
    void removeSubframe(Frame* subframe);
public:
    Frame(Frame* par, fRect rel);
    Frame(Rectangle rec);
    ~Frame();
    
    void plug(Frame* par, fRect rel);
    void plug(Frame* par);
    void unplug();

    void moveTo(fPoint rel);
    void moveCenterTo(fPoint rel);

    void moveBy(fPoint rel);

    void resize(fPoint rel);

    const Rectangle& getFrame() const;
    const fRect& getRelative() const;

    const fPoint& getCenter() const;
    
    const int& getX() const;
    const int& getY() const;
    const int& getW() const;
    const int& getH() const;
    
    operator Rectangle() const;
    operator fRect() const;
    operator iRect() const;

};

#endif 
