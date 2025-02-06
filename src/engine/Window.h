#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window
{
private:
	Window();

public:
	bool Create(const char* title, int width, int height);
	void Destroy();

	bool ShouldClose();

	static Window* Get();

	GLFWwindow* GetWindow() const { return mWindow; }
	int GetWidth() { glfwGetWindowSize(mWindow, &mWidth, &mHeight); return mWidth; }
	int GetHeight() { glfwGetWindowSize(mWindow, &mWidth, &mHeight); return mHeight; }

private:
	GLFWwindow* mWindow;
	int mWidth;
	int mHeight;

};