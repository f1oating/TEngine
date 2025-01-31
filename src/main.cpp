#include <Windows.h>

#include "engine/Engine.h"
#include "engine/game/GameObject.h"
#include "components/SpriteComponent.h"
#include "managers/TextureManager.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Engine* engine = Engine::Get();

	if (!engine->StartUp()) return 1;

	GameObject* object = new GameObject();
	object->SetScale(0.5f);
	object->SetPosition({0.2f, 0.2f, 1.0f});
	SpriteComponent* sprite = new SpriteComponent(object);
	sprite->SetTexture(TextureManager::Get()->GetTexture("res\\textures\\cat.jpg"));

	engine->RunLoop();
	engine->Shutdown();

	return 0;
}