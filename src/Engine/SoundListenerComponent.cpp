#include "SoundListenerComponent.h"

#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>

#include "Entity.h"
#include "PhysicsComponent.h"

SoundListenerComponent* SoundListenerComponent::CurrentListener = nullptr;

void SoundListenerComponent::Tick(float dt)
{
	Super::Tick(dt);
	if(CurrentListener == this && Owner)
	{
        alListenerfv(AL_POSITION, &Owner->Location[0]);
		ALfloat OrientationArray[6];
        OrientationArray[0] = Owner->GetForwardVector().x;
        OrientationArray[1] = Owner->GetForwardVector().y;
        OrientationArray[2] = Owner->GetForwardVector().z;
        OrientationArray[3] = 0.f;
        OrientationArray[4] = 1.f;
        OrientationArray[5] = 0.f;
        alListenerfv(AL_ORIENTATION, OrientationArray);
		PhysicsComponent* PhysComp = Owner->GetComponent<PhysicsComponent>();
        if(PhysComp)
        {
        	alListenerfv(AL_VELOCITY, &PhysComp->Velocity[0]);
        }
	}
}

void SoundListenerComponent::SetCurrentListener()
{
    CurrentListener = this;
}
