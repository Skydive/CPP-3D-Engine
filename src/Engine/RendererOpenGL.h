#pragma once
#include "Renderer.h"

#include "Model.h"
#include "Texture.h"

class RendererOpenGL : public Renderer
{
public:
	virtual void Start() override;
	virtual void Update() override;
	virtual void RenderClear() override;
	virtual void RenderPresent() override;

	virtual void Clean() override;

	virtual glm::mat4 GetProjectionMatrix() override;
	virtual glm::mat4 GetViewMatrix() override;
	virtual glm::mat4 GetModelMatrix(glm::vec3 Location, glm::quat Rotation, glm::vec3 Scale) override;

protected:
	glm::mat4 P;
private:
	using Super = Renderer;
};
