#include "const/path/atb.hpp"
#include <chunk.hpp>
#include <raylib.h>

Chunk::Chunk(Frame* frame, Rectangle rect) : Interface(frame, rect)
{
    trafficLight = nullptr;
    score = 1;
}

Chunk::Chunk(Chunk* other) : Interface(other)
{

    trafficLight = nullptr;
    score = 1;
    for(auto i : other->visiter)
    {
        Rectangle rel;
        rel.x = -0.4;
        rel.y = -0.1;
        rel.width = i->getRelative()[2] - 0.04;
        rel.height = 0.6;
        visiter.push_back(new Container(i, this, rel));
    }
    velocity = other->velocity;
    if(other->trafficLight != nullptr)
    {
        Rectangle rel;
        rel.x = GetRandomValue(0, 90) / 100.0;
        rel.y = other->trafficLight->getRelative()[1];
        rel.width = other->trafficLight->getRelative()[2];
        rel.height = other->trafficLight->getRelative()[3];
        trafficLight = new Container(other->trafficLight, this, rel);
        trafficLight->show();
    }
    generateEntity();
}

Chunk::Chunk(Chunk* other, Rectangle rect) : Interface(other, rect)
{
    trafficLight = nullptr;
    score = 1;
    for(auto i : other->visiter)
    {
        Rectangle rel;
        rel.x = -0.4;
        rel.y = -0.1;
        rel.width = i->getRelative()[2] - 0.04;
        rel.height = 0.6;
        visiter.push_back(new Container(i, this, rel));
    }
    velocity = other->velocity;
    if(other->trafficLight != nullptr)
    {
        Rectangle rel;
        rel.x = GetRandomValue(0, 90) / 100.0;
        rel.y = other->trafficLight->getRelative()[1];
        rel.width = other->trafficLight->getRelative()[2];
        rel.height = other->trafficLight->getRelative()[3];
        trafficLight = new Container(other->trafficLight, this, rel);
        trafficLight->show();
    }
    generateEntity();
}

Chunk::Chunk(Chunk* other, Frame* frame, Rectangle rect) : Interface(other, frame, rect)
{
    trafficLight = nullptr;
    score = 1;
    for(auto i : other->visiter)
    {
        Rectangle rel;
        rel.x = -0.7;
        rel.y = -0.8;
        rel.width = i->getRelative()[2] - 0.06;
        rel.height = 0.4;
        visiter.push_back(new Container(i, this, rel));
    }
    velocity = other->velocity;
    generateEntity();
    if(other->trafficLight != nullptr)
    {
        Rectangle rel;
        rel.x = GetRandomValue(0, 90) / 100.0;
        rel.y = other->trafficLight->getRelative()[1];
        rel.width = other->trafficLight->getRelative()[2];
        rel.height = other->trafficLight->getRelative()[3];
        trafficLight = new Container(other->trafficLight, this, rel);
        trafficLight->show();
    }
}

void Chunk::generateEntity() 
{

    if(visiter.empty()) return;
    float x = -0.3;
    
    while(x < 1.3)
    {
        Container* c = randomEntity();
        Rectangle rel;
        rel.x = x;
        rel.y = 0;
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

void Chunk::setVelocity(fPoint vel)
{
    velocity = vel;
}

bool Chunk::isEntityCollide(Container* main)
{
    for(auto i : Entity)
    {
        if(i->isCollide(main)) 
        {
            //throw i;
            return true;
        }
    }
    return false;
}

YAML::Node Chunk::createSpecialContent()
{
    YAML::Node node = Interface::createSpecialContent();
    for(int i = 0; i < visiter.size(); i++)
    {
        node["visiter"][i] = visiter[i]->createSpecialContent();
    }
    node["velocity"][0] = velocity[0];
    node["velocity"][1] = velocity[1];

    for(int i = 0; i < Entity.size(); i++)
    {
        node["entity"][i] = Entity[i]->createSpecialContent();
    }
    for(int i = 0; i < entityOrder.size(); i++)
    {
        node["order"][i] = entityOrder[i];
    }

    return node;
}

void Chunk::loadSpecialContent(YAML::Node node)
{
    Interface::loadSpecialContent(node);
    while(!Entity.empty())
    {
        delete Entity.back();
        Entity.pop_back();
    }
    
    for(int i = 0; i < visiter.size(); i++) 
    {
        visiter[i]->loadSpecialContent(node["visiter"][i]);
    }
    velocity[0] = node["velocity"][0].as<float>();
    velocity[1] = node["velocity"][1].as<float>();
    
    for(auto i : node["order"])
    {
        entityOrder.push_back(i.as<int>());
        Container* c = visiter[i.as<int>()];
        Rectangle rel;
        rel.x = c->getRelative()[0];
        rel.y = c->getRelative()[1];
        rel.width = c->getRelative()[2];
        rel.height = c->getRelative()[3];
        Container* cont = new Container(c, this, rel);
        Entity.push_back(cont);
    }
    for(int i = 0; i < Entity.size(); i++)
    {
        Entity[i]->loadSpecialContent(node["entity"][i]);  
    }
}

int Chunk::getScore()
{
    if(score == 1) return score--;
    return 0;
}

void Chunk::attachLight(Container* light)
{
    stop = false;
    Rectangle rel;
    rel.x = 0.5;
    rel.y = -0.5;
    rel.width = light->getRelative()[2];
    rel.height = 0.5;

    trafficLight = new Container(light, this, rel);
    trafficLight->show();
}
