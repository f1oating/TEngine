#pragma once

#include <vector>
#include <glm/glm.hpp>

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

	void AddMeshComp(class MeshComponent* mesh);
	void RemoveMeshComp(class MeshComponent* mesh);

	void SetProjMatrix(const glm::mat4& proj);
	void SetViewMatrix(const glm::mat4& view);

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