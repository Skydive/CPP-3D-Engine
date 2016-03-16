#pragma once
#include "Component.h"

#include <memory>
#include <vector>

#include "Shader.h"
#include "Model.h"
#include "Texture.h"

class RenderComponent : public Component
{
public:
	virtual void BeginPlay() override;
	virtual void Render() override;
	virtual void AttachShader(Shader* shader);

	bool bActive{true};
	Model* RenderModel;
	Texture* RenderTexture;
	glm::vec3 Scale;
	glm::vec4 Color;

private:
	std::vector<Shader*> RenderShaders;
	using Super = Component;
};
