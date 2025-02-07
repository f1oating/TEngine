#pragma once

#include "Component.h"

#include <glm/glm.hpp>

class CameraComponent : public Component
{
public:
	CameraComponent(class GameObject* owner, int updateOrder = 200);

	virtual void SetAspectRatio(float aspectRatio) = 0;
	virtual void SetResolution(int width, int height) = 0;

protected:
	void SetProjMatrix(const glm::mat4& proj);
	void SetViewMatrix(const glm::mat4& view);

};
