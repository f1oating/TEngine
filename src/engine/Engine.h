#pragma once

#include <vector>

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

private:
	void Update();
	void GenerateOutput();

	class Window* mWindow;
	class RenderSystem* mRenderSystem;

	bool mIsRunning;

	std::vector<class GameObject*> mObjects;
	std::vector<class GameObject*> mPendingObjects;

	bool mUpdatingObjects;

};