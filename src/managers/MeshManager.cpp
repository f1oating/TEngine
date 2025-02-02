#include "MeshManager.h"
#include "graphics/Mesh.h"

#include <assert.h>

MeshManager::MeshManager() :
	mMeshFolder("res\\meshes")
{
}

bool MeshManager::StartUp()
{
	return true;
}

void MeshManager::Shutdown()
{
	for (auto pair : mMeshes)
	{
		pair.second->Unload();
		delete pair.second;
	}
	mMeshes.clear();
}

Mesh* MeshManager::GetMesh(std::string fileName)
{
	Mesh* tex = nullptr;
	auto iter = mMeshes.find(fileName);
	if (iter != mMeshes.end())
	{
		tex = iter->second;
	}
	else
	{
		tex = new Mesh();
		if (tex->Load(mMeshFolder + "\\" + fileName))
		{
			mMeshes.emplace(fileName, tex);
		}
		else
		{
			delete tex;
			tex = nullptr;
		}
	}
	return tex;
}

MeshManager* MeshManager::Get()
{
	static MeshManager* manager = new MeshManager();
	if (!manager) { manager = new MeshManager(); }
	assert(manager);
	return manager;
}