#include "Component.h"
#include "engine/Engine.h"
#include "engine/GameObject.h"

Component::Component(class GameObject* owner, int updateOrder) :
	mEngine(&Engine::Get())
	,mOwner(owner)
	,mUpdateOrder(updateOrder)
{
	mOwner->AddComponent(this);
}

Component::~Component() 
{
	mOwner->RemoveComponent(this);
}

void Component::Update(float deltaTime)
{

}

void Component::ProcessInput()
{

}