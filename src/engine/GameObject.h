#pragma once

#include <vector>

class GameObject
{
public:
	GameObject();
	~GameObject();

	void Update(float deltaTime);
	void UpdateComponents(float deltaTime);
	virtual void UpdateActor(float deltaTime);

	void ProcessInput();
	virtual void ActorInput();

	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);

private:
	class Engine* mEngine;
	std::vector<class Component*> mComponents;

};