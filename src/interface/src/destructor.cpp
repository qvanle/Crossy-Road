#include <interface.hpp>


Interface::~Interface()
{
    for (auto& i : containers) 
        delete i;
    containers.clear();
}
