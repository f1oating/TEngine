#include "Component.h"
#include "engine/game/GameObject.h"

Component::Component(class GameObject* owner, int updateOrder) :
	mOwner(owner)
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