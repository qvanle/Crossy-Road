#include <visual.hpp>

void Visual::deleteTexture2D(Texture2D*& texture)
{
    if(texture != nullptr)
    {
        UnloadTexture(*texture);
        texture = nullptr;
    }
}

Visual::~Visual()
{
    m_texture.reset();
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
