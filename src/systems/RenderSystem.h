#pragma once

#include <vector>

class RenderSystem
{
private:
	RenderSystem();

public:
	bool StartUp();
	void Shutdown();

	void Draw();

	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);

	static RenderSystem& Get();

private:
	class Engine* mEngine;

	std::vector<class SpriteComponent*> mSprites;

};