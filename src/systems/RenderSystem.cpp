#include "RenderSystem.h"
#include "engine/Window.h"
#include "components/SpriteComponent.h"
#include "components/MeshComponent.h"
#include "graphics/VertexArray.h"
#include "graphics/Shader.h"

#include <assert.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

RenderSystem::RenderSystem() :
	mWindow(nullptr)
	, mSpriteShader(nullptr)
	, mSpriteVerts(nullptr)
	, mMeshShader(nullptr)
{}

bool RenderSystem::StartUp()
{
	mWindow = Window::Get();

	if (!LoadShaders())
	{
		return false;
	}

	CreateSpriteVerts();

	return true;
}

void RenderSystem::Shutdown()
{
	delete mSpriteVerts;
	mSpriteShader->Unload();
	delete mSpriteShader;
	mMeshShader->Unload();
	delete mMeshShader;
}

void RenderSystem::OnResize(int width, int height)
{
	if (mSpriteShader)
	{
		mSpriteShader->SetActive();
		glm::mat4 viewProj = glm::ortho(
			0.0f,
			static_cast<float>(width),
			static_cast<float>(height),
			0.0f,
			-1.0f,
			1.0f
		);
		mSpriteShader->SetMatrixUniform("uViewProj", viewProj);
	}
}

void RenderSystem::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

	mSpriteShader->SetActive();
	mSpriteVerts->SetActive();
	for (auto sprite : mSprites)
	{
		if (sprite->GetVisible())
		{
			sprite->Draw(mSpriteShader);
		}
	}

	glfwSwapBuffers(mWindow->GetWindow());
}

void RenderSystem::AddSprite(SpriteComponent* sprite)
{
	int myDrawOrder = sprite->GetDrawOrder();
	auto iter = mSprites.begin();
	for (;
		iter != mSprites.end();
		++iter)
	{
		if (myDrawOrder < (*iter)->GetDrawOrder())
		{
			break;
		}
	}

	mSprites.insert(iter, sprite);
}

void RenderSystem::RemoveSprite(SpriteComponent* sprite)
{
	auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
	mSprites.erase(iter);
}

void RenderSystem::AddMeshComp(MeshComponent* mesh)
{
	mMeshes.emplace_back(mesh);
}

void RenderSystem::RemoveMeshComp(MeshComponent* mesh)
{
	auto iter = std::find(mMeshes.begin(), mMeshes.end(), mesh);
	mMeshes.erase(iter);
}

bool RenderSystem::LoadShaders()
{
	mSpriteShader = new Shader();
	if (!mSpriteShader->Load("shaders/Sprite.vert", "shaders/Sprite.frag"))
	{
		return false;
	}
	mSpriteShader->SetActive();
	glm::mat4 viewProj = glm::ortho(
		0.0f,
		static_cast<float>(mWindow->GetWidth()),
		static_cast<float>(mWindow->GetHeight()),
		0.0f,
		-1.0f,
		1.0f
	);
	mSpriteShader->SetMatrixUniform("uViewProj", viewProj);

	mMeshShader = new Shader();
	if (!mMeshShader->Load("shaders/BasicMesh.vert", "shaders/BasicMesh.frag"))
	{
		return false;
	}

	return true;
}

void RenderSystem::CreateSpriteVerts()
{
	float vertices[] = {
		-0.5f, 0.5f, 0.f, 0.f, 0.f, 0.0f, 0.f, 0.f,
		0.5f, 0.5f, 0.f, 0.f, 0.f, 0.0f, 1.f, 0.f,
		0.5f,-0.5f, 0.f, 0.f, 0.f, 0.0f, 1.f, 1.f,
		-0.5f,-0.5f, 0.f, 0.f, 0.f, 0.0f, 0.f, 1.f
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	mSpriteVerts = new VertexArray(vertices, 4, VertexArray::PosNormTex, indices, 6);
}

RenderSystem* RenderSystem::Get()
{
	static RenderSystem* system = new RenderSystem();
	if (!system) { system = new RenderSystem(); }
	assert(system);
	return system;
}