#pragma once

#include <vector>
#include <string>
#include <assimp/scene.h>

struct GeometryChunk {
	class VertexArray* vertexArray;
	std::vector<class Texture*> textures;
};

class Mesh
{
public:
	Mesh();
	~Mesh();

	bool Load(const std::string& fileName);
	void Unload();

	size_t GetNumChunks() const { return mGeometryChunks.size(); }
	const GeometryChunk& GetGeometryChunk(size_t index) const { return mGeometryChunks[index]; }
	const std::string& GetFileName() const { return mFileName; }

private:
	void LoadTextures(aiMaterial* material, aiTextureType type,
		const std::string& typeName, GeometryChunk& chunk);

	std::vector<GeometryChunk> mGeometryChunks;
	std::string mFileName;

};