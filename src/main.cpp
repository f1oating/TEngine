#include <Windows.h>

#include "engine/Engine.h"
#include "engine/game/GameObject.h"
#include "managers/TextureManager.h"
#include "components/SpriteComponent.h"
#include "components/OrthographicCameraComponent.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Engine* engine = Engine::Get();

	if (!engine->StartUp()) return 1;

	GameObject* sprite = new GameObject();
	SpriteComponent* spriteComponent = new SpriteComponent(sprite);
	spriteComponent->SetTexture(TextureManager::Get()->GetTexture("cat.jpg"));
	sprite->SetScale(0.4f);
	sprite->SetPosition({0.2f, 0.2f, 1.0f});
	OrthographicCameraComponent* camera = new OrthographicCameraComponent(sprite);
	camera->SetResolution(1920, 1080);

	engine->RunLoop();
	engine->Shutdown();

	return 0;
}