#pragma once
#include "Resource.h"

#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>

class Sound : public Resource
{
public:
	Sound(std::string NewName, std::string NewPath) : Resource(NewName, NewPath) {}
	virtual bool Load() override;
	virtual void Destroy() override;

	unsigned int buffer;
protected:
	int format;
    int size;
    int freq;
    char loop;
	void* data;
};
