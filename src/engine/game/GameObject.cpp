#include "GameObject.h"
#include "engine/Engine.h"
#include "components/Component.h"

GameObject::GameObject() :
	mEngine(&Engine::Get())
	, mPosition(0)
	, mRotation(1.0f, 0.0f, 0.0f, 0.0f)
	, mWorldTransform(1.0f)
	, mScale(1.0f)
	, mRecomputeTransform(true)
{
	mEngine->AddObject(this);
}

GameObject::~GameObject() 
{
	mEngine->RemoveObject(this);

	while (!mComponents.empty())
	{
		delete mComponents.back();
	}
}

void GameObject::Update(float deltaTime)
{

}

void GameObject::UpdateComponents(float deltaTime)
{
	for (auto comp : mComponents)
	{
		comp->Update(deltaTime);
	}
}

void GameObject::UpdateActor(float deltaTime)
{

}

void GameObject::ProcessInput()
{

}

void GameObject::ActorInput()
{

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