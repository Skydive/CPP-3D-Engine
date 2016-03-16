#include "Texture.h"

#include <FreeImage.h>
#include <GL/glew.h>

bool Texture::Load()
{
    FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;

    fif = FreeImage_GetFileType(Path.c_str(), 0);
    if(fif == FIF_UNKNOWN)
          fif = FreeImage_GetFIFFromFilename(Path.c_str());

    if(fif == FIF_UNKNOWN)
        return false;

    if(FreeImage_FIFSupportsReading(fif))
    {
        FIBITMAP* dib = FreeImage_Load(fif, Path.c_str());
        FIBITMAP* dib32 = FreeImage_ConvertTo32Bits(dib);
        if(dib32)
        {
            uint8_t* TextureBits = FreeImage_GetBits(dib32);
            unsigned int TextureWidth = FreeImage_GetWidth(dib);
            unsigned int TextureHeight = FreeImage_GetHeight(dib);
            if(TextureBits && TextureWidth && TextureHeight)
            {
                glGenTextures(1, &ID);
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, ID);
            		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TextureWidth, TextureHeight, 0, GL_BGRA, GL_UNSIGNED_BYTE, TextureBits);
                glBindTexture(GL_TEXTURE_2D, 0);
            }

        }
        FreeImage_Unload(dib);
        return true;
    }
    return false;
}

void Texture::Destroy()
{
    glDeleteTextures(1, &ID);
}
