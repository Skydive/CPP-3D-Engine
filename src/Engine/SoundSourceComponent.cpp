#include "SoundSourceComponent.h"

#include <iostream>
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>

#include "Entity.h"
#include "PhysicsComponent.h"

void SoundSourceComponent::BeginPlay()
{
    alGenSources(1, &source);
    int error = alGetError();
    if(error != AL_NO_ERROR)
    {
        std::cout << "alGenSources: error: " << error;
        alDeleteSources(1, &source);
    }
    Super::BeginPlay();
}

void SoundSourceComponent::SetSourceSound(Sound* SoundResource)
{
    alSourcei(source, AL_BUFFER, SoundResource->buffer);
    int error = alGetError();
    if(error != AL_NO_ERROR)
    {
        std::cout << "alGenSources: error: " << error;
        alDeleteSources(1, &source);
        return;
    }
}

void SoundSourceComponent::Tick(float dt)
{
    Super::Tick(dt);
    if(Owner)
    {
        alSourcefv(source, AL_POSITION, &Location[0]);
        ALfloat OrientationArray[6];
        OrientationArray[0] = Owner->GetForwardVector().x;
        OrientationArray[1] = Owner->GetForwardVector().y;
        OrientationArray[2] = Owner->GetForwardVector().z;
        OrientationArray[3] = 0.f;
        OrientationArray[4] = 1.f;
        OrientationArray[5] = 0.f;
        alSourcefv(source, AL_ORIENTATION, OrientationArray);
        PhysicsComponent* PhysComp = Owner->GetComponent<PhysicsComponent>();
        if(PhysComp)
        {
        	alSourcefv(source, AL_VELOCITY, &PhysComp->Velocity[0]);
        }
    }
}

void SoundSourceComponent::Play()
{
    alSourcePlay(source);
}
void SoundSourceComponent::Pause()
{
    alSourcePause(source);
}
void SoundSourceComponent::Rewind()
{
    alSourceRewind(source);
}
void SoundSourceComponent::Stop()
{
    alSourceStop(source);
}

void SoundSourceComponent::Destroy()
{
    Stop();
    Super::Destroy();
}

SoundSourceComponent::~SoundSourceComponent()
{
    alDeleteSources(1, &source);
}
