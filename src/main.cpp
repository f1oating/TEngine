#include <Windows.h>

#include "engine/Engine.h"
#include "engine/game/GameObject.h"
#include "components/SpriteComponent.h"
#include "managers/TextureManager.h"
#include "graphics/Mesh.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Engine* engine = Engine::Get();

	if (!engine->StartUp()) return 1;

	Mesh* mesh = new Mesh();
	mesh->Load("res\\meshes\\LowpolySoldier.fbx");

	engine->RunLoop();
	engine->Shutdown();

	return 0;
}