#include "Sound.h"

#include <iostream>
#include <string.h>

bool Sound::Load()
{
    buffer = alutCreateBufferFromFile(strdup(Path.c_str()));
    int error = alGetError();
    if(error != ALUT_ERROR_NO_ERROR)
    {
       std::cout << "alutCreateBufferFromFile: " << Path << " error: " << error;
       Destroy();
       return false;
    }
    return true;
}

void Sound::Destroy()
{
    alDeleteBuffers(1, &buffer);
}
