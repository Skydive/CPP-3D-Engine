#include "ResourceManager.h"
#include <algorithm>

bool ResourceManager::ResourceExists(Resource* PassedResource)
{
    bool bExists = false;
    for(auto& res : ResourceList)
    {
        if(PassedResource->Name == res->Name)
        {
            bExists = true;
        }
    }
    return bExists;
}

Resource* ResourceManager::PrecacheResource(Resource* PassedResource)
{
    if(ResourceExists(PassedResource) || PassedResource->Name.empty() || PassedResource->Path.empty())
    {
        delete PassedResource; // Shame on me.
        return nullptr;
    }
    PassedResource->Load();
    ResourceList.push_back(std::unique_ptr<Resource>(PassedResource));
    return PassedResource;
}

void ResourceManager::FreeResource(Resource* PassedResource)
{
    ResourceList.erase(
        std::remove_if(
            ResourceList.begin(),
            ResourceList.end(),
            [&] (auto& res)
            {
                return PassedResource == res.get();
            }),
            ResourceList.end()
        );
}

void ResourceManager::FreeResource(std::string ResourceName)
{
    ResourceList.erase(
        std::remove_if(
            ResourceList.begin(),
            ResourceList.end(),
            [&] (auto& res)
            {
                return res->Name == ResourceName;
            }),
            ResourceList.end()
        );
}
