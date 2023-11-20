#include <storage_raw.hpp>

void* RawStorage::at(std::string index)
{
    return materials[index];
}

void RawStorage::insert(std::string index, void* material)
{
    materials[index] = material;
}

void RawStorage::erase(std::string index)
{
    materials.erase(index);
}

void RawStorage::erase(void* material)
{
    for (auto it = materials.begin(); it != materials.end(); it++)
    {
        if (it->second == material)
        {
            materials.erase(it);
            break;
        }
    }
}

void RawStorage::clear()
{
    materials.clear();
}

int RawStorage::size()
{
    return materials.size();
}

void* RawStorage::operator[](std::string index)
{
    return materials[index];
}

void* RawStorage::find(void* material)
{
    for (auto it = materials.begin(); it != materials.end(); it++)
    {
        if (it->second == material)
        {
            return it->second;
        }
    }
    return nullptr;
}
