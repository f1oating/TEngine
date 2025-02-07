#include "Engine.h"
#include "Window.h"
#include "game/GameObject.h"
#include "systems/RenderSystem.h"
#include "managers/TextureManager.h"
#include "managers/MeshManager.h"

#include <assert.h>
#include <algorithm>

Engine::Engine() :
	mIsRunning(false)
	,mWindow(nullptr)
	,mRenderSystem(nullptr)
	,mUpdatingObjects(false)
{}

bool Engine::StartUp()
{
	mWindow = Window::Get();
	if (!mWindow->Create("TEngine", 800, 600)) { return false; }

	mRenderSystem = RenderSystem::Get();
	if (!mRenderSystem->StartUp()) { return false; }

	if (!TextureManager::Get()->StartUp()) { return false; }
	if (!MeshManager::Get()->StartUp()) { return false; }

	mIsRunning = true;
	return true;
}

void Engine::RunLoop()
{
	while (mIsRunning)
	{
		Update();
		GenerateOutput();

		glfwPollEvents();
	}
}

void Engine::Shutdown()
{
	Window::Get()->Destroy();
	mRenderSystem->Shutdown();
	TextureManager::Get()->Shutdown();
	MeshManager::Get()->Shutdown();
}

void Engine::Update()
{
	if (mWindow->ShouldClose()) { mIsRunning = false; }

	static float deltaTime = 0.0f;
	static float lastFrame = 0.0f;

	float currentFrame = static_cast<float>(glfwGetTime());
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	mUpdatingObjects = true;
	for (auto actor : mObjects)
	{
		actor->Update(deltaTime);
	}
	mUpdatingObjects = false;

	for (auto pending : mPendingObjects)
	{
		mObjects.emplace_back(pending);
	}
	mPendingObjects.clear();
}

void Engine::GenerateOutput()
{
	mRenderSystem->Draw();
}

Engine* Engine::Get()
{
	static Engine* engine = new Engine();
	if (!engine) { engine = new Engine(); }
	assert(engine);
	return engine;
}

void Engine::AddObject(GameObject* actor)
{
	if (mUpdatingObjects)
	{
		mPendingObjects.emplace_back(actor);
	}
	else
	{
		mObjects.emplace_back(actor);
	}
}

void Engine::RemoveObject(GameObject* actor)
{
	auto iter = std::find(mPendingObjects.begin(), mPendingObjects.end(), actor);
	if (iter != mPendingObjects.end())
	{
		std::iter_swap(iter, mPendingObjects.end() - 1);
		mPendingObjects.pop_back();
	}

	iter = std::find(mObjects.begin(), mObjects.end(), actor);
	if (iter != mObjects.end())
	{
		std::iter_swap(iter, mObjects.end() - 1);
		mObjects.pop_back();
	}
}