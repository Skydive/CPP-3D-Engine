#pragma once
#include "Component.h"

class SoundListenerComponent : public Component
{
public:
	virtual void Tick(float dt) override;
	virtual void SetCurrentListener();

	static SoundListenerComponent* CurrentListener;
private:
	using Super = Component;
};
