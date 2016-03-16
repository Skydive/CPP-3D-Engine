#include "Engine.h"

class Game : public Engine
{
public:
	virtual void Precache() override;
	virtual void BeginPlay() override;

private:
	using Super = Engine;
};
