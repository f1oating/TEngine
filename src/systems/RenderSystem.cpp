#include "RenderSystem.h"
#include "engine/Engine.h"

#include <assert.h>

RenderSystem::RenderSystem() :
	mEngine(&Engine::Get())
{}

bool RenderSystem::StartUp()
{
	return true;
}

void RenderSystem::Shutdown()
{

}

RenderSystem& RenderSystem::Get()
{
	static RenderSystem* engine = new RenderSystem();
	if (!engine) { engine = new RenderSystem(); }
	assert(engine);
	return *engine;
}