#ifndef VISUAL 
#define VISUAL 

#include <memory>
#include <raylib.h>
#include <yaml-cpp/yaml.h>

#include <frame.hpp>

/**
 * @class Visual
 *
 * @brief images displayed on screen
 * 
**/
class Visual : public Frame
{
private:
    std::shared_ptr<Texture2D> m_texture;
    bool resizeable;
    static void deleteTexture2D(Texture2D*&);
protected:
    void fitFrame();   
    void updateFrame(bool recursive = false) override;
public:
    Visual(Texture2D*, Frame*, Rectangle);
    Visual(Visual*);
    Visual(Visual*, Rectangle);
    Visual(Visual*, Frame*, Rectangle);
    ~Visual();
    
    void resize(fPoint);

    void draw();
};
using Sprite = std::vector<Visual*>;
void deleteSprite(Sprite*&);
void deleteSprites(std::vector<Sprite>*&);
#endif // VISUAL
