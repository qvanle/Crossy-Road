#ifndef OBJECT_HPP 
#define OBJECT_HPP

#include <container.hpp>
#include <keystroke.hpp>
#include <chrono>
class Object : public Container
{
private: 
    struct ObjectKeyStroke
    {
        KeyStroke* stroke;
    };
    std::vector<ObjectKeyStroke> strokes;
    std::chrono::time_point<std::chrono::steady_clock> waitUntil;


protected: 
    void loadControl(YAML::Node node);

public: 
    Object(Frame*, Rectangle);
    Object(Object*);
    Object(Object*, Rectangle);
    Object(Object*, Frame*, Rectangle);
    ~Object();

    virtual std::string linkContent(std::string) override;
    virtual std::string linkContentAbsolute(std::string) override;
    
    virtual Action* react() override;
    void draw() override;
};

#endif 
