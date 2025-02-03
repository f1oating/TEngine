#pragma once

#include "Component.h"

class MeshComponent : public Component
{
public:
	MeshComponent(class GameObject* owner);
	~MeshComponent();

	virtual void Draw(class Shader* shader);
	virtual void SetMesh(class Mesh* mesh) { mMesh = mesh; }

	void SetVisible(bool visible) { mVisible = visible; }
	bool GetVisible() const { return mVisible; }

protected:
	class Mesh* mMesh;
	bool mVisible;

};