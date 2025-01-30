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

	void OnResize(int width, int height);

	bool ShouldClose();

	static Window* Get();

	GLFWwindow* GetWindow() const { return mWindow; }
	int GetWidth() const { return mWidth; }
	int GetHeight() const { return mHeight; }

private:
	GLFWwindow* mWindow;
	int mWidth;
	int mHeight;

};