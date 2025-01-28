#pragma once

#include <glm/gtc/quaternion.hpp>

class BoneTransform
{
public:
	glm::quat mRotation;
	glm::vec3 mTranslation;

	glm::mat4 ToMatrix() const;

	static BoneTransform Interpolate(const BoneTransform& a, const BoneTransform& b, float f);

};