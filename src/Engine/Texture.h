#pragma once
#include "Resource.h"

class Texture : public Resource
{
public:
    Texture(std::string NewName, std::string NewPath) : Resource(NewName, NewPath) {}
    virtual bool Load() override;
	virtual void Destroy() override;
    unsigned int ID;
};
