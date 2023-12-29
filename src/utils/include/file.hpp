#ifndef UTILS_FILE_H
#define UTILS_FILE_H

#include <string>
#include <vector>

#include <yaml-cpp/yaml.h>

/**
 * @namespace YAML_FILE
 *
 * @brief opens and interacts with YAML files
 * 
**/
namespace YAML_FILE 
{
    bool isFile(std::string path);
    YAML::Node readFile(std::string path);
    bool writeFile(std::string path, YAML::Node content);
}

#endif 
