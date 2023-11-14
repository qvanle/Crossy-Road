#include <iostream>
#include <fstream>
#include <file.hpp>

bool YAML_FILE::isFile(std::string path)
{
    // return true if file exists
    
    std::ifstream fin(path);
    return fin.good();
}

YAML::Node YAML_FILE::readFile(std::string path)
{
    // return YAML::Node from file
    
    YAML::Node node;
    try
    {
        node = YAML::LoadFile(path);
    }
    catch (YAML::BadFile& e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }
    return node;
}
