#include "RendererOpenGL.h"

#include "Engine.h"
#include "Config.h"


#include <iostream>
#include <glm/gtc/type_ptr.hpp>

// Events
void RendererOpenGL::Start()
{
    bool bFullscreen = Config("./Display.cfg").GetValueBool("bFullscreen", false);

	if(!glfwInit())
    {
        glfwTerminate();
	    std::cout <<  "GLFW could not initialize!" << std::endl;
    	GameEngine->bQuit = true;
		return;
	}

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	// TODO: Windows: Core profile doesn't work?
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// TODO: Linux: GetPrimaryMonitor doesn't work correctly.
    const GLFWvidmode* vm = glfwGetVideoMode(glfwGetPrimaryMonitor());
    glfwWindowHint(GLFW_RED_BITS, vm->redBits);
    glfwWindowHint(GLFW_GREEN_BITS, vm->greenBits);
    glfwWindowHint(GLFW_BLUE_BITS, vm->blueBits);
    glfwWindowHint(GLFW_REFRESH_RATE, vm->refreshRate);
    if(bFullscreen)
    {
        GameEngine->Dimensions.x = vm->width;
        GameEngine->Dimensions.y = vm->height;
        GameWindow = glfwCreateWindow(GameEngine->Dimensions.x, GameEngine->Dimensions.y, GameEngine->GameName.c_str(), glfwGetPrimaryMonitor(), NULL);
    }
    else
    {
        GameWindow = glfwCreateWindow(GameEngine->Dimensions.x, GameEngine->Dimensions.y, GameEngine->GameName.c_str(), NULL, NULL);
    }

    if(!GameWindow)
    {
        glfwTerminate();
		std::cout <<  "Window could not be created!" << std::endl;
		GameEngine->bQuit = true;
		return;
    }
    glfwSetWindowSize(GameWindow, GameEngine->Dimensions.x, GameEngine->Dimensions.y);
    glfwMakeContextCurrent(GameWindow);

    std::cout << glGetString(GL_VERSION) << std::endl;
    std::cout << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    glewExperimental = GL_TRUE;
    GLenum GLEWStatus = glewInit();
    if (GLEWStatus != GLEW_OK)
    {
        std::cout <<  "GLEW could not be initialised! GL Error: " << glewGetErrorString(GLEWStatus) << std::endl;
		GameEngine->bQuit = true;
		return;
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

    glEnable(GL_CULL_FACE);

	RenderClear();

    int w, h;
    glfwGetFramebufferSize(GameWindow, &w, &h);

	// Wow, this actually works.
	glfwSetFramebufferSizeCallback(GameWindow,
		[](GLFWwindow* window, int w, int h)
		{
			glViewport(0, 0, w, h);
		}
	);
    glViewport(0, 0, w, h);


	std::cout << "Renderer Created" << std::endl;

}

void RendererOpenGL::Update()
{
    if(GameWindow)
        GameEngine->bQuit = glfwWindowShouldClose(GameWindow) ? true : GameEngine->bQuit;
}

void RendererOpenGL::RenderClear()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	P = glm::perspective(90.0f, 1.0f*GameEngine->Dimensions.x/GameEngine->Dimensions.y, 0.01f, 1000.0f);
}

void RendererOpenGL::RenderPresent()
{
	glfwSwapBuffers(GameWindow);
}

void RendererOpenGL::Clean()
{
    glfwDestroyWindow(GameWindow);
    glfwTerminate();
}

glm::mat4 RendererOpenGL::GetProjectionMatrix()
{
    return P;
}
glm::mat4 RendererOpenGL::GetViewMatrix()
{
    return glm::lookAt(glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.0, 0.0, 0), glm::vec3(0.0, 1.0, 0.0)) * glm::toMat4(glm::conjugate(RenderRotation)) * glm::translate(glm::mat4(1.0f), -RenderLocation);
}
glm::mat4 RendererOpenGL::GetModelMatrix(glm::vec3 Location, glm::quat Rotation, glm::vec3 Scale)
{
    return glm::translate(glm::mat4(1.0f), Location) * glm::toMat4(Rotation) * glm::scale(glm::mat4(1.0f), Scale);
}
