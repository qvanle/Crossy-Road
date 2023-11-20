#include <storage_raw.hpp>

RawStorage::~RawStorage()
{
    for(auto& i : materials)
    {
        delete i.second;
    }
}

