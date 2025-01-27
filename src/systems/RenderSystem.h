#pragma once

class RenderSystem
{
private:
	RenderSystem();

public:
	bool StartUp();
	void Shutdown();

	static RenderSystem& Get();

private:
	class Engine* mEngine;

};