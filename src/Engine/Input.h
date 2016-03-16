#pragma once
#include "Object.h"

#include <glm/glm.hpp>

#include "InputScancodes.hpp"


class Input : public Object
{
public:
	void Start();
	void Update(float dt);

	bool GetKey(int Key);
	bool GetMouse(int Key);


	void SetMouseFrozen(bool bFreeze);
	bool GetMouseFrozen();
	static bool bFreezeMouse;

	glm::vec2 GetMouseVelocity();
	glm::vec2 GetMousePosition();

protected:
	glm::vec2 MousePosition;
	glm::vec2 MouseVelocity;
};
