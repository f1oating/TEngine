#include "GameObject.h"
#include "engine/Engine.h"
#include "components/Component.h"

GameObject::GameObject() :
	mPosition(0)
	, mRotation(1.0f, 0.0f, 0.0f, 0.0f)
	, mWorldTransform(1.0f)
	, mScale(1.0f)
	, mRecomputeTransform(true)
{
	Engine::Get()->AddObject(this);
}

GameObject::~GameObject() 
{
	Engine::Get()->RemoveObject(this);

	while (!mComponents.empty())
	{
		delete mComponents.back();
	}
}

void GameObject::Update(float deltaTime)
{
	if (mRecomputeTransform)
	{
		ComputeWorldTransform();
	}
}

void GameObject::UpdateComponents(float deltaTime)
{
	for (auto comp : mComponents)
	{
		comp->Update(deltaTime);
	}
}

void GameObject::ComputeWorldTransform()
{
	mRecomputeTransform = false;
	glm::mat4 scaleMat = glm::scale(glm::mat4(1.0f), glm::vec3(mScale));
	glm::mat4 rotationMat = glm::mat4_cast(mRotation);
	glm::mat4 translationMat = glm::translate(glm::mat4(1.0f), mPosition);
	mWorldTransform = translationMat * rotationMat * scaleMat;
}

void GameObject::AddComponent(class Component* component)
{
	int myOrder = component->GetUpdateOrder();
	auto iter = mComponents.begin();
	for (;
		iter != mComponents.end();
		++iter)
	{
		if (myOrder < (*iter)->GetUpdateOrder())
		{
			break;
		}
	}

	mComponents.insert(iter, component);
}

void GameObject::RemoveComponent(class Component* component)
{
	auto iter = std::find(mComponents.begin(), mComponents.end(), component);
	if (iter != mComponents.end())
	{
		mComponents.erase(iter);
	}
}