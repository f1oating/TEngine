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
	bool LoadShaders();
	void CreateSpriteVerts();

	class Engine* mEngine;

	class Shader* mSpriteShader;
	class VertexArray* mSpriteVerts;
	std::vector<class SpriteComponent*> mSprites;

};