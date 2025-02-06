#include "OrthographicCameraComponent.h"
#include "engine/game/GameObject.h"
#include "systems/RenderSystem.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

OrthographicCameraComponent::OrthographicCameraComponent(GameObject* owner)
	: CameraComponent(owner)
{
	glm::mat4 proj = glm::ortho(
		0.0f,
		static_cast<float>(800),
		static_cast<float>(600),
		0.0f,
		-1.0f,
		1.0f
	);
	RenderSystem::Get()->SetProjMatrix(proj);
	RenderSystem::Get()->SetViewMatrix(glm::mat4(1.0f));
}

void OrthographicCameraComponent::Update(float deltaTime)
{

}

void OrthographicCameraComponent::SetAspectRatio(float aspectRatio)
{

}

void OrthographicCameraComponent::SetResolution(int width, int height)
{
	glm::mat4 proj = glm::ortho(
		0.0f,
		static_cast<float>(width),
		static_cast<float>(height),
		0.0f,
		-1.0f,
		1.0f
	);
	RenderSystem::Get()->SetProjMatrix(proj);
}