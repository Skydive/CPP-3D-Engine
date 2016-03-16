#include "SoundManager.h"

#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>

void SoundManager::Start()
{
    alutInit(0, 0);
    alGetError();

    ALCdevice* SoundDevice = alcOpenDevice(0);
    ALCcontext* SoundContext = alcCreateContext(SoundDevice, 0);
    alcMakeContextCurrent(SoundContext);
    alGetError();
}


SoundManager::~SoundManager()
{
    alutExit();
}
