#ifndef STORAGE_RAW_HPP 
#define STORAGE_RAW_HPP

#include <vector>
#include <map>
#include <string>

class RawStorage 
{
private: 
    std::map<std::string, void*> materials;
public: 
    RawStorage();
    ~RawStorage();

    void* at(std::string index);
    void insert(std::string index, void* material);

    void erase(std::string index);
    void erase(void* material);

    void clear();
    int size();

    void* find(void* material);

    void* operator[](std::string index);
};

#endif 
