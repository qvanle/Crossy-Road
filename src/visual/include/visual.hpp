#ifndef VISUAL 
#define VISUAL 

#include <raylib.h>
#include <yaml-cpp/yaml.h>

#include <frame.hpp>

class Visual : public Frame
{
private:
    Texture2D* m_texture;
protected:
    void fitFrame();   
    void updateFrame(bool recursive = false) override;
public:
    Visual(Texture2D*, Frame*, Rectangle);
    ~Visual();
    
    void resize(fPoint);

    void draw();
};
using Sprite = std::vector<Visual*>;

#endif // VISUAL
