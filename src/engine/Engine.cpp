#include "Engine.h"
#include "game/GameObject.h"
#include "systems/RenderSystem.h"
#include "managers/TextureManager.h"

#include <assert.h>
#include <algorithm>

Engine::Engine() :
	mIsRunning(false)
	,mRenderSystem(nullptr)
	,mWindow(nullptr)
	,mUpdatingObjects(false)
{}

bool Engine::StartUp()
{
	if (!InitializeGL()) { return false; }

	mRenderSystem = RenderSystem::Get();
	mRenderSystem->StartUp();

	TextureManager::Get()->StartUp();

	mIsRunning = true;
	return true;
}

void Engine::RunLoop()
{
	while (mIsRunning)
	{
		if (glfwWindowShouldClose(mWindow)) { mIsRunning = false; }

		Update();
		GenerateOutput();

		glfwPollEvents();
	}
}

void Engine::Shutdown()
{
	UnInitializeGL();
	mRenderSystem->Shutdown();

	TextureManager::Get()->Shutdown();
}

void Engine::Update()
{
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

bool Engine::InitializeGL()
{
	if (!glfwInit()) {
		return false;
	}

	mWindow = glfwCreateWindow(800, 600, "TEngine", nullptr, nullptr);
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

void Engine::UnInitializeGL()
{
	glfwDestroyWindow(mWindow);
	glfwTerminate();
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