#include "MeshComponent.h"
#include "graphics/Shader.h"
#include "graphics/Mesh.h"
#include "graphics/Texture.h"
#include "engine/game/GameObject.h"
#include "systems/RenderSystem.h"

MeshComponent::MeshComponent(GameObject* owner)
	:Component(owner)
	, mMesh(nullptr)
	, mVisible(true)
{
	RenderSystem::Get()->AddMeshComp(this);
}

MeshComponent::~MeshComponent()
{
	RenderSystem::Get()->RemoveMeshComp(this);
}

void MeshComponent::Draw(Shader* shader)
{
	if (mMesh)
	{
		shader->SetMatrixUniform("uWorldTransform",
			mOwner->GetWorldTransform());
	}
}