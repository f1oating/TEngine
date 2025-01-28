#pragma once

class VertexArray
{
public:
	enum Layout
	{
		PosNormTex,
		PosNormSkinTex
	};

	VertexArray(const void* verts, unsigned int numVerts, Layout layout,
		const unsigned int* indices, unsigned int numIndices);
	~VertexArray();

	void SetActive();
	unsigned int GetNumIndices() const { return mNumIndices; }
	unsigned int GetNumVerts() const { return mNumVerts; }

private:
	unsigned int mNumVerts;
	unsigned int mNumIndices;
	unsigned int mVertexBuffer;
	unsigned int mIndexBuffer;
	unsigned int mVertexArray;

};