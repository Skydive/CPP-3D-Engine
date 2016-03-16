#include "CubeMapTexture.h"

#include <FreeImage.h>
#include <GL/glew.h>
#include <sstream>
#include <iostream>
bool CubeMapTexture::Load()
{
    FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;

    glGenTextures(1, &ID);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, ID);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        for(int i=0; i < 6; i++)
        {
            std::string GeneratedPath = Path + std::to_string(i) + ".png";
            std::cout << GeneratedPath << std::endl;
            fif = FreeImage_GetFileType(GeneratedPath.c_str(), 0);
            if(fif == FIF_UNKNOWN)
                  fif = FreeImage_GetFIFFromFilename(GeneratedPath.c_str());
            if(fif == FIF_UNKNOWN)
                return false;

            if(FreeImage_FIFSupportsReading(fif))
            {
                FIBITMAP* dib = FreeImage_Load(fif, GeneratedPath.c_str());
                FIBITMAP* dib32 = FreeImage_ConvertTo32Bits(dib);
                if(dib32)
                {
                    uint8_t* TextureBits = FreeImage_GetBits(dib32);
                    unsigned int TextureWidth = FreeImage_GetWidth(dib);
                    unsigned int TextureHeight = FreeImage_GetHeight(dib);
                    if(TextureBits && TextureWidth && TextureHeight)
                    {
                        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+i, 0, GL_RGBA, TextureWidth, TextureHeight, 0, GL_BGRA, GL_UNSIGNED_BYTE, TextureBits);
                    }
                }
                FreeImage_Unload(dib);
            }
            else
            {
                return false;
            }
        }
    glBindTexture(GL_TEXTURE_2D, 0);
    return true;
}
