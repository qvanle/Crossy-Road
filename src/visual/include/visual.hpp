#ifndef VISUAL 
#define VISUAL 

#include <raylib.h>

#include <frame.hpp>

class Visual : public Frame
{
private:
    Texture2D* m_texture;
protected:
    
public:
    Visual(Texture2D*, Frame*);
    Visual(Texture2D*, Frame*, Rectangle);
    Visual(Texture2D*, Rectangle);
    ~Visual();

    void draw();
};

#endif // VISUAL
