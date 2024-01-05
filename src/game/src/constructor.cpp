#include "raylib.h"
#include <const/path/atb.hpp>
#include <file.hpp>
#include <vector.hpp>
#include <object.hpp>
#include <chunk.hpp>
#include <game.hpp>

Game::Game(Frame* frame, Rectangle rect) : Interface(frame, rect)
{
    initState = true;
}

Game::Game(Game* other) : Interface(other)
{
    initState = true;
}

Game::Game(Game* other, Rectangle rect) : Interface(other, rect)
{
    initState = true;
}

Game::Game(Game* other, Frame* frame, Rectangle rect) : Interface(other, frame, rect)
{
    initState = true;
}

void Game::reset()
{
    initState = true;
}

std::string Game::linkContentAbsolute(std::string path)
{
    isPause = false;
    YAML::Node node = YAML_FILE::readFile(path);
    if(!loadName(node)) return "";

    if(node["textures"]) 
        loadSprites(node["textures"]);

    if(node["focus"]) 
        loadFocus(node["focus"]);
    else chooseImage(0, 0);

    if(node["object"]) 
    {
        loadObject(node["object"]);
        for(int i = 0; i < getContainersSize(); i++) 
            getContainers(i)->hide();
        main = getContainers(0);
        main->show();
    }
    if(node["collide"])
        loadCollide(node["collide"]);

    if(node["chunk"])
        loadChunk(node["chunk"]);

    if(node["attach-object"])
        loadAttactObject(node["attach-object"]);

    if(node["control"])
        loadControl(node["control"]);

    if(node["event"])
        loadEvent(node["event"]);

    if(node["button"])
        loadButton(node["button"]);
    return getName();
}

void Game::loadCollide(YAML::Node node)
{
}

void Game::loadMap() 
{
    if(cache.empty()) return ;
    while(!chunks.empty())
    {
        fRect rec = chunks.back()->getRelative();
        if(rec[1] > 1) 
        {
            delete chunks.back();
            chunkOrder.pop_back();
            chunks.pop_back();
        }else break;
    }
    if(chunks.empty()) 
    {
        Rectangle rel;
        rel.width = cache[0]->getRelative()[2];
        rel.height = cache[0]->getRelative()[3];
        rel.x = 0;
        rel.y = (1.01 - rel.height);

        Chunk* chunk = new Chunk(cache[0], this, rel);
        chunkOrder.push_front(0);
        chunks.push_front(chunk);
        for(int i = 0; i < 6; i++)
        {
            rel.y += 0.005 - rel.height;
            chunk = new Chunk(cache[0], this, rel);
            chunks.push_front(chunk);
            chunkOrder.push_front(0);
        }
    }
    while(chunks.front()->getRelative()[1] > 0)
    {
        Rectangle rel;
        rel.width = chunks.front()->getRelative()[2];
        rel.height = chunks.front()->getRelative()[3];
        rel.x = 0;
        rel.y = (chunks.front()->getRelative()[1] + 0.005 - rel.height);

        int id = GetRandomValue(0, cache.size() - 1);
        Chunk* chunk = new Chunk(cache[id], this, rel);
        chunks.push_front(chunk);
        chunkOrder.push_front(id);
    }
}

void Game::loadChunk(YAML::Node node)
{
    for(auto i : node) 
    {
        float x = 0, y = 0, w = 1, h = 1;
        int repeat = 1;
        std::string path = i["file"].as<std::string>();
        if(i["x"]) x = i["x"].as<float>() / 100;
        if(i["y"]) y = i["y"].as<float>() / 100;
        if(i["w"]) w = i["w"].as<float>() / 100;
        if(i["h"]) h = i["h"].as<float>() / 100;
        if(i["repeat"]) repeat = i["repeat"].as<int>();
        fPoint direction = {1, 0};
        float velo = 0.002;
        if(i["velocity"]) 
        {
            velo = i["velocity"][0].as<float>();
            direction = {i["velocity"][1].as<float>(), i["velocity"][2].as<float>()};
        }
        float angle = VECTOR2D::getAngle(direction);
        fPoint displacement = {velo * cos(angle), velo * sin(angle)};
        Chunk* chunk = new Chunk(this, {x, y, w, h}); 
        chunk->linkContent(path);
        chunk->setVelocity(displacement);
        cache.push_back(chunk);
        while(--repeat > 0) 
            cache.push_back(new Chunk(cache[0]));
    }
}

void Game::loadAttactObject(YAML::Node node) 
{
    for(auto i : node) 
    {
        int objID = i["object"][0].as<int>();
        Container* container = getContainers(objID);
        int prob = i["object"][1].as<int>();
        for(auto j : i["chunk"])
        {
            int id = j.as<int>();
            container->setProbability(prob);
            cache[id]->addVisiter(container);
        }
    }
}

void Game::loadEvent(YAML::Node node)
{
    if(node["map-speed"])
    {
        mapSpeed = node["map-speed"].as<float>();
    }
    if(node["map-direction"])
    {
        mapDirection[0] = node["map-direction"][0].as<float>();
        mapDirection[1] = node["map-direction"][1].as<float>();
    }
    float angle = VECTOR2D::getAngle(mapDirection);
    std::cout << "hehe: " << angle << std::endl;
    mapDisplacement[0] = mapSpeed * cos(angle);
    mapDisplacement[1] = mapSpeed * sin(angle);
}

YAML::Node Game::createSpecialContent() 
{
    YAML::Node node = Interface::createSpecialContent();
    node["map-speed"] = mapSpeed;
    node["map-direction"][0] = mapDirection[0];
    node["map-direction"][1] = mapDirection[1];
    node["map-displacement"][0] = mapDisplacement[0];
    node["map-displacement"][1] = mapDisplacement[1];
    node["main"] = main->createSpecialContent();

    for(int i = 0; i < chunkOrder.size(); i++)
    {
        node["chunk-order"][i] = chunkOrder[i];
    }
    
    for(int i = 0; i < chunks.size(); i++)
    {
        node["chunks"][i] = chunks[i]->createSpecialContent();
    }

    for(int i = 0; i < cache.size(); i++)
    {
        node["cache"][i] = cache[i]->createSpecialContent();
    }
    return node;
}

void Game::loadSpecialContent(YAML::Node node)
{
    Interface::loadSpecialContent(node);
    mapSpeed = node["map-speed"].as<float>();
    mapDirection[0] = node["map-direction"][0].as<float>();
    mapDirection[1] = node["map-direction"][1].as<float>();
    mapDisplacement[0] = node["map-displacement"][0].as<float>();
    mapDisplacement[1] = node["map-displacement"][1].as<float>();
    main->loadSpecialContent(node["main"]);

    for(auto i : node["chunk-order"])
    {
        chunkOrder.push_back(i.as<int>());
        Chunk* c = cache[i.as<int>()];
        Rectangle rel;
        rel.x = c->getRelative()[0];
        rel.y = c->getRelative()[1];
        rel.width = c->getRelative()[2];
        rel.height = c->getRelative()[3];

        Chunk* chunk = new Chunk(c, this, rel);
        chunks.push_back(chunk);
    }

    for(int i = 0; i < chunks.size(); i++)
    {
        chunks[i]->loadSpecialContent(node["chunks"][i]);
    }

    for(int i = 0; i < cache.size(); i++)
    {
        cache[i]->loadSpecialContent(node["cache"][i]);
    }

}
