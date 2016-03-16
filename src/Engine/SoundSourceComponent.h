#pragma once
#include "Component.h"

#include "Sound.h"

class SoundSourceComponent : public Component
{
public:
    virtual void BeginPlay() override;
    virtual void Play();
    virtual void Pause();
    virtual void Rewind();
    virtual void Stop();
    virtual void Destroy() override;
    virtual void Tick(float dt) override;
    virtual void SetSourceSound(Sound* SoundResource);
    virtual ~SoundSourceComponent();
    Sound* SourceSound;

protected:
    unsigned int source;

private:
    using Super = Component;
};
