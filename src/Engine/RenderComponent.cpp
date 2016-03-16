
#include "RenderComponent.h"
#include "Engine.h"

#include <iostream>

#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

void RenderComponent::BeginPlay()
{
	Super::BeginPlay();
	Scale = {1, 1, 1};
	Color = {1, 1, 1, 1};
}

void RenderComponent::AttachShader(Shader* shader)
{
	RenderShaders.push_back(shader);
}

void RenderComponent::Render()
{
	Super::Render();

	if(RenderShaders.size() == 0)
	{
		std::cout << "No shader loaded!" << std::endl;
		return;
	}

	if(!RenderModel)
	{
		std::cout << "No model loaded!" << std::endl;
		return;
	}

	glm::mat4 P = GameEngine->GameRenderer->GetProjectionMatrix();
	glm::mat4 V = GameEngine->GameRenderer->GetViewMatrix();
	glm::mat4 M = GameEngine->GameRenderer->GetModelMatrix(Location, Rotation, Scale);
	glm::mat3 NormalMatrix = glm::transpose(glm::inverse(glm::mat3(V * M)));

	for(auto& shader : RenderShaders)
	{
		if(shader)
		{
			shader->BindTexture = RenderTexture;
		    shader->Enable();
				glUniformMatrix4fv(shader->UModel, 1, GL_FALSE, glm::value_ptr(M));
				glUniformMatrix4fv(shader->UView, 1, GL_FALSE, glm::value_ptr(V));
				glUniformMatrix4fv(shader->UProjection, 1, GL_FALSE, glm::value_ptr(P));

			    glBindVertexArray(RenderModel->VAO);
			        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, RenderModel->IBO);
			            int size;
			            glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
			            glDrawElements(GL_TRIANGLES, size/sizeof(unsigned short), GL_UNSIGNED_SHORT, 0);
			        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
				glBindVertexArray(0);
			shader->Disable();
		}
	}
}
