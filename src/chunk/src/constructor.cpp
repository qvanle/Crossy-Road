#include "const/path/atb.hpp"
#include <chunk.hpp>

Chunk::Chunk(Frame* frame, Rectangle rect) : Interface(frame, rect)
{

}

Chunk::Chunk(Chunk* other) : Interface(other)
{

    for(auto i : other->visiter)
    {
        Rectangle rel;
        rel.x = 1;
        rel.y = -0.375;
        rel.width = i->getRelative()[2];
        rel.height = i->getRelative()[3];
        visiter.push_back(new Container(i, this, rel));
    }
    generateEntity();
}

Chunk::Chunk(Chunk* other, Rectangle rect) : Interface(other, rect)
{
    for(auto i : other->visiter)
    {
        Rectangle rel;
        rel.x = 1;
        rel.y = -0.375;
        rel.width = i->getRelative()[2];
        rel.height = i->getRelative()[3];
        visiter.push_back(new Container(i, this, rel));
    }
    generateEntity();
}

Chunk::Chunk(Chunk* other, Frame* frame, Rectangle rect) : Interface(other, frame, rect)
{
    for(auto i : other->visiter)
    {
        Rectangle rel;
        rel.x = 1;
        rel.y = -0.375;
        rel.width = i->getRelative()[2];
        rel.height = i->getRelative()[3];
        visiter.push_back(new Container(i, this, rel));
    }
    generateEntity();
}

void Chunk::generateEntity() 
{

    if(visiter.empty()) return;
    float x = GetRandomValue(0, 5) / 10.0;
    
    while(x < 0.9)
    {
        Container* c = randomEntity();
        Rectangle rel;
        rel.x = x;
        rel.y = -0.375;
        rel.width = c->getRelative()[2];
        rel.height = c->getRelative()[3];
        Container* cont = new Container(c, this, rel);
        Entity.push_back(cont);
        x += GetRandomValue(20, 60) / 100.0;
    }
}


std::string Chunk::linkContent(std::string path)
{
    return linkContentAbsolute(PATB::CHUNK_ + path);
}


void Chunk::addVisiter(Container* obj)
{
    Rectangle rel;
    rel.x = obj->getRelative()[0];
    rel.y = obj->getRelative()[1];
    rel.width = obj->getRelative()[2];
    rel.height = obj->getRelative()[3];

    Container* c = new Container(obj, this, rel);
    visiter.push_back(c);
}

void Chunk::addVisiter(Container* obj, int prob)
{
    Rectangle rel;
    rel.x = obj->getRelative()[0];
    rel.y = obj->getRelative()[1];
    rel.width = obj->getRelative()[2];
    rel.height = obj->getRelative()[3];

    Container* c = new Container(obj, this, rel);
    c->setProbability(prob);
    visiter.push_back(c);
}

void Chunk::addVisiter(Container* obj, Rectangle rel)
{
    Container* c = new Container(obj, this, rel);
    visiter.push_back(c);
}

void Chunk::addVisiter(Container* obj, int prob, Rectangle rel)
{
    Container* c = new Container(obj, this, rel);
    c->setProbability(prob);
    visiter.push_back(c);
}
