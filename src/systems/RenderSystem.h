#pragma once

#include <vector>

class RenderSystem
{
private:
	RenderSystem();

public:
	bool StartUp();
	void Shutdown();

	void OnResize(int width, int height);

	void Draw();

	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);

	void AddMeshComp(class MeshComponent* mesh);
	void RemoveMeshComp(class MeshComponent* mesh);

	static RenderSystem* Get();

private:
	bool LoadShaders();
	void CreateSpriteVerts();

	class Window* mWindow;

	class Shader* mSpriteShader;
	class VertexArray* mSpriteVerts;
	std::vector<class SpriteComponent*> mSprites;

	class Shader* mMeshShader;
	std::vector<class MeshComponent*> mMeshes;

};