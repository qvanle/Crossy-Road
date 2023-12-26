#include <interface.hpp>


Interface::~Interface()
{
    for (auto& i : containers) 
        delete i;
    containers.clear();

    for (auto& i : nested) 
        delete i;
    nested.clear();

    for (auto& i : keystrokes) 
        delete i;
}
