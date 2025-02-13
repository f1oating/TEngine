#pragma once

class Component
{
public:
	Component(class GameObject* owner, int updateOrder = 100);
	virtual ~Component();

	virtual void Update(float deltaTime);
	virtual void ProcessInput();

	int GetUpdateOrder() const { return mUpdateOrder; }

protected:
	class GameObject* mOwner;
	int mUpdateOrder;

};