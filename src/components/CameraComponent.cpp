#include "CameraComponent.h"
#include "engine/game/GameObject.h"
#include "systems/RenderSystem.h"

CameraComponent::CameraComponent(GameObject* owner, int updateOrder)
	:Component(owner, updateOrder)
{
}

void CameraComponent::SetProjMatrix(const glm::mat4& proj)
{
	RenderSystem::Get();
}

void CameraComponent::SetViewMatrix(const glm::mat4& view)
{
	RenderSystem::Get();
}