#pragma once

#include "CameraComponent.h"

class OrthographicCameraComponent : public CameraComponent
{
public:
	OrthographicCameraComponent(class GameObject* owner);

	void Update(float deltaTime) override;

	void SetAspectRatio(float aspectRatio) override;
	void SetResolution(int width, int height) override;

};