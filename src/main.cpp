#include "engine/Engine.h"

#include <Windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Engine engine = Engine::Get();

	if (!engine.StartUp()) return 1;
	engine.RunLoop();
	engine.Shutdown();

	return 0;
}