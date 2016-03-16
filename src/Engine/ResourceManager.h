#include "Object.h"
#include "Resource.h"
#include <vector>
#include <memory>

class ResourceManager : public Object
{
public:
    template<class T> void GetResources(std::vector<T*>* ResourceVector)
    {
        for(auto& res : ResourceList)
        {
            T* ResourceObject = dynamic_cast<T*>(res.get());
            if(ResourceObject)
            {
                ResourceVector.push_back(ResourceObject);
            }
        }
    }
    template<class T> T* GetResource(std::string Name)
    {
        for(auto& res : ResourceList)
        {
            T* ResourceObject = dynamic_cast<T*>(res.get());
            if(ResourceObject && ResourceObject->Name == Name)
            {
                return ResourceObject;
            }
        }
        return nullptr;
    }
    bool ResourceExists(Resource* PassedResource);
    Resource* PrecacheResource(Resource* PassedResource);
    void FreeResource(Resource* PassedResource);
    void FreeResource(std::string ResourceName);

private:

    std::vector<std::unique_ptr<Resource>> ResourceList;
};
