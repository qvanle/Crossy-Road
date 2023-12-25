#include "raylib.h"
#include <const/path/atb.hpp>
#include <file.hpp>
#include <object.hpp>
#include <chunk.hpp>
#include <game.hpp>

Game::Game(Frame* frame, Rectangle rect) : Interface(frame, rect)
{
}

Game::Game(Game* other) : Interface(other)
{
}

Game::Game(Game* other, Rectangle rect) : Interface(other, rect)
{
}

Game::Game(Game* other, Frame* frame, Rectangle rect) : Interface(other, frame, rect)
{
}

std::string Game::linkContentAbsolute(std::string path)
{
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
        for(int i = 0; i < getContainersSize(); ++i)
        {
            Container* container = getContainers(i);
            container->hide();
        }   
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
        if(rec[1] > 1) chunks.pop_back();
        else break;
    }
    if(chunks.empty()) 
    {
        int id = GetRandomValue(0, cache.size() - 1);
        Rectangle rel;
        rel.width = cache[id]->getRelative()[2];
        rel.height = cache[id]->getRelative()[3];
        rel.x = 0;
        rel.y = (1.01 - rel.height);

        Chunk* chunk = new Chunk(cache[id], this, rel);
        chunks.push_front(chunk);
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

        Chunk* chunk = new Chunk(this, {x, y, w, h}); 
        chunk->linkContent(path);
        chunk->setVelocity({0.002, 0});
        cache.push_back(chunk);
        while(--repeat > 0) 
            cache.push_back(new Chunk(cache[0]));
    }
}

void Game::loadAttactObject(YAML::Node node) 
{
    for(auto i : node) 
    {
        int id = i["chunk"].as<int>();
        int objID = i["object"][0].as<int>();
        int prob = i["object"][1].as<int>();
        Container* container = getContainers(objID);
        container->setProbability(prob);
        cache[id]->addVisiter(container);
    }
}

void Game::loadEvent(YAML::Node node)
{
    if(node["map-speed"])
    {
        mapSpeed[0] = node["map-speed"][0].as<float>();
        mapSpeed[1] = node["map-speed"][1].as<float>();
    }
}
