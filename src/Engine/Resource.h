#pragma once
#include "Object.h"
#include <string>
class Resource : public Object
{
public:
    Resource(std::string NewName, std::string NewPath)
        : Name{NewName}, Path{NewPath} {}
    virtual ~Resource();
    std::string Name;
    std::string Path;
    virtual bool Load();
    virtual void Destroy();
};
