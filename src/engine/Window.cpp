#include "Window.h"

#include <assert.h>

Window::Window() :
	mWindow(nullptr)
	,mWidth(0)
	,mHeight(0)
{}

bool Window::StartUp(const char* title, int width, int height)
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

	if (glewInit() != GLEW_OK) {
		glfwTerminate();
		return false;
	}

	return true;
}

void Window::Shutdown()
{
	glfwDestroyWindow(mWindow);
	glfwTerminate();
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