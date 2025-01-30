#include "SpriteComponent.h"
#include "graphics/Texture.h"
#include "graphics/Shader.h"
#include "engine/game/GameObject.h"
#include "systems/RenderSystem.h"

SpriteComponent::SpriteComponent(GameObject* owner, int drawOrder)
	:Component(owner)
	, mTexture(nullptr)
	, mDrawOrder(drawOrder)
	, mTexWidth(0)
	, mTexHeight(0)
	, mVisible(true)
{
	RenderSystem::Get()->AddSprite(this);
}

SpriteComponent::~SpriteComponent()
{
	RenderSystem::Get()->RemoveSprite(this);
}

void SpriteComponent::Draw(Shader* shader)
{
	if (mTexture)
	{
		mTexture->SetActive();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	}
}

void SpriteComponent::SetTexture(Texture* texture)
{
	mTexture = texture;
	mTexWidth = texture->GetWidth();
	mTexHeight = texture->GetHeight();
}