#pragma once
#include "Texture.h"

class CubeMapTexture : public Texture
{
public:
    CubeMapTexture(std::string NewName, std::string NewPath) : Texture(NewName, NewPath) {}
    std::string PathSuffix;
    virtual bool Load() override;
};
