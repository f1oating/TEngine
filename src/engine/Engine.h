#pragma once

#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Engine
{
private:
	Engine();

public:
	bool StartUp();
	void RunLoop();
	void Shutdown();

	static Engine* Get();

	bool IsRunning() const { return mIsRunning; }

	void AddObject(class GameObject* object);
	void RemoveObject(class GameObject* object);

	GLFWwindow* GetWindow() const { return mWindow; }

private:
	void Update();
	void GenerateOutput();
	bool InitializeGL();
	void UnInitializeGL();

	class RenderSystem* mRenderSystem;

	bool mIsRunning;
	GLFWwindow* mWindow;

	std::vector<class GameObject*> mObjects;
	std::vector<class GameObject*> mPendingObjects;

	bool mUpdatingObjects;

};