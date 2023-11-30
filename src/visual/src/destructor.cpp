#include <visual.hpp>

Visual::~Visual()
{
    if(m_texture != nullptr)
        UnloadTexture(*m_texture);
    delete m_texture;
}

void deleteSprite(Sprite sprite)
{
    for(auto& frame : sprite)
        delete frame;
    sprite.clear();
}

void deleteSprites(std::vector<Sprite>*& sprites)
{
    for(Sprite & sprite : *sprites)
    {    
        deleteSprite(sprite);
    }
    delete sprites;
}
