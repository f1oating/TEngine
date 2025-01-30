#include "Window.h"
#include "systems/RenderSystem.h"

#include <assert.h>

void ReisizeCallback(GLFWwindow* window, int width, int height) {
	Window::Get()->OnResize(width, height);
	RenderSystem::Get()->OnResize(width, height);
	glViewport(0, 0, width, height);
}

Window::Window() :
	mWindow(nullptr)
	,mWidth(0)
	,mHeight(0)
{}

bool Window::Create(const char* title, int width, int height)
{
	mWidth = width;
	mHeight = height;

	if (!glfwInit()) {
		return false;
	}

	mWindow = glfwCreateWindow(mWidth, mHeight, title, nullptr, nullptr);
	if (!mWindow) {
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(mWindow);
	glfwSetFramebufferSizeCallback(mWindow, ReisizeCallback);

	if (glewInit() != GLEW_OK) {
		glfwTerminate();
		return false;
	}

	return true;
}

void Window::Destroy()
{
	glfwDestroyWindow(mWindow);
	glfwTerminate();
}

void Window::OnResize(int width, int height)
{
	mWidth = width;
	mHeight = height;
}

bool Window::ShouldClose()
{
	return glfwWindowShouldClose(mWindow);
}

Window* Window::Get()
{
	static Window* window = new Window();
	if (!window) { window = new Window(); }
	assert(window);
	return window;
}