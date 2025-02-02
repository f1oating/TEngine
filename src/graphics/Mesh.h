#pragma once

#include <vector>
#include <string>
#include <assimp/scene.h>

class Mesh
{
public:
	Mesh();
	~Mesh();

	bool Load(const std::string& fileName);
	void Unload();

	size_t GetNumVertexArrays() const { return mVertexArrays.size(); }
	class VertexArray* GetVertexArray(size_t index) { return mVertexArrays[index]; }
	class Texture* GetTexture(size_t meshIndex, size_t textureIndex);
	const std::string& GetFileName() const { return mFileName; }

	/*
		TODO
		LoadBinary();
		SaveBinary();
	*/

private:
	void LoadTextures(aiMaterial* material, aiTextureType type,
		const std::string& typeName, size_t meshIndex);

	std::vector<std::vector<class Texture*>> mTextures;
	std::vector<class VertexArray*> mVertexArrays;
	std::string mFileName;

};