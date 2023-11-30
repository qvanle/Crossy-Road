#include <visual.hpp>


void Visual::draw()
{
    if(m_texture == nullptr) return ;
    Rectangle rec = getFrame();
    // draw texture 
    DrawTexture(*m_texture, rec.x, rec.y, WHITE);
}

void Visual::fitFrame()
{
    if(m_texture == nullptr) return ;
    const Rectangle &rec = Frame::getFrame();

    Image img = LoadImageFromTexture(*m_texture);
    UnloadTexture(*m_texture);
    delete m_texture;
    
    ImageResize(&img, rec.width, rec.height);
    m_texture = new Texture2D(LoadTextureFromImage(img));
    UnloadImage(img);
}

void Visual::resize(fPoint rel)
{
    Frame::resize(rel);
    updateFrame(true);
}

void Visual::updateFrame(bool recursive)
{
    if(m_texture == nullptr) return ;
    float prx = getFrame().width; 
    float pry = getFrame().height;
    Frame::updateFrame(recursive);

    float rx = getFrame().width - prx;
    float ry = getFrame().height - pry;
    if(rx < 1e-3 && ry < 1e-3) return ;
    fitFrame();
}
