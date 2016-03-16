#include "Input.h"
#include "Engine.h"

#include <iostream>
#include <string>

bool Input::bFreezeMouse = false;

void Input::Start(){}

void Input::Update(float dt)
{
	glfwPollEvents();
	if(GameEngine && GameEngine->GameRenderer)
	{
		static glm::vec2 OldMousePosition;
		OldMousePosition = MousePosition;

		double x, y;
		glfwGetCursorPos(GameEngine->GameRenderer->GameWindow, &x, &y);
		MousePosition.x = x;
		MousePosition.y = y;

		MouseVelocity = (MousePosition-OldMousePosition) * dt;
	}
	else
	{
		MouseVelocity = {0, 0};
		MousePosition = {0, 0};
	}
}


void Input::SetMouseFrozen(bool bFreeze)
{
	bFreezeMouse = bFreeze;
	if(bFreeze)
		glfwSetInputMode(GameEngine->GameRenderer->GameWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

bool Input::GetMouseFrozen()
{
	return bFreezeMouse;
}

bool Input::GetKey(int KieCode)
{
	return glfwGetKey(GameEngine->GameRenderer->GameWindow, KieCode);
}

bool Input::GetMouse(int KieCode)
{
	return glfwGetMouseButton(GameEngine->GameRenderer->GameWindow, KieCode);
}

glm::vec2 Input::GetMousePosition()
{
	return MousePosition;
}

glm::vec2 Input::GetMouseVelocity()
{
	return MouseVelocity;
}
