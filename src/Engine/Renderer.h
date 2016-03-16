#pragma once
#include "Object.h"

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Shader.h"
#include "Model.h"
#include "Texture.h"
#include "CubeMapTexture.h"


class Renderer : public Object
{
public:
	virtual void Start();
	virtual void Update();
	virtual void RenderClear();
	virtual void RenderPresent();
	virtual void Clean();

	virtual glm::mat4 GetProjectionMatrix();
	virtual glm::mat4 GetViewMatrix();
	virtual glm::mat4 GetModelMatrix(glm::vec3 Location, glm::quat Rotation, glm::vec3 Scale);

	glm::vec3 RenderLocation;
	glm::quat RenderRotation;

	GLFWwindow* GameWindow;
};
