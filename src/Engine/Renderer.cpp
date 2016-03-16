#include "Renderer.h"

#include <FreeImage.h>

void Renderer::Start()
{
    FreeImage_Initialise();
}
void Renderer::Update(){}

void Renderer::RenderClear(){}
void Renderer::RenderPresent(){}
void Renderer::Clean()
{
    FreeImage_DeInitialise();
}

glm::mat4 Renderer::GetProjectionMatrix() { return glm::mat4(); }
glm::mat4 Renderer::GetViewMatrix() { return glm::mat4(); }
glm::mat4 Renderer::GetModelMatrix(glm::vec3 Location, glm::quat Rotation, glm::vec3 Scale) { return glm::mat4(); }
