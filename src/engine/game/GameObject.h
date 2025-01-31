#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

class GameObject
{
public:
	GameObject();
	~GameObject();

	void Update(float deltaTime);
	void UpdateComponents(float deltaTime);

	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);

	const glm::vec3& GetPosition() const { return mPosition; }
	void SetPosition(const glm::vec3& pos) { mPosition = pos; mRecomputeTransform = true; }
	float GetScale() const { return mScale; }
	void SetScale(float scale) { mScale = scale; mRecomputeTransform = true; }
	const glm::quat& GetRotation() const { return mRotation; }
	void SetRotation(const glm::quat& rotation) { mRotation = rotation;   mRecomputeTransform = true; }

	void ComputeWorldTransform();
	const glm::mat4& GetWorldTransform() const { return mWorldTransform; }

private:
	std::vector<class Component*> mComponents;

	glm::mat4 mWorldTransform;
	glm::vec3 mPosition;
	glm::quat mRotation;
	float mScale;
	bool mRecomputeTransform;

};