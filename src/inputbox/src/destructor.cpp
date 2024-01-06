#include <inputbox.hpp>



highScore::~highScore()
{
    save("inputbox.yaml");
}