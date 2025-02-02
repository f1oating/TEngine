#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include "Mesh.h"
#include "VertexArray.h"
#include "Texture.h"
#include "managers/TextureManager.h"

Mesh::Mesh()
    : mFileName("")
{
}

Mesh::~Mesh()
{
    Unload();
}

bool Mesh::Load(const std::string& fileName)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(fileName,
        aiProcess_Triangulate |
        aiProcess_GenNormals |
        aiProcess_FlipUVs |
        aiProcess_CalcTangentSpace
    );

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        return false;
    }

    for (unsigned int i = 0; i < scene->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[i];

        std::vector<float> vertices;
        std::vector<unsigned int> indices;
        unsigned int numVertex = 0;
        unsigned int numIndex = 0;

        for (unsigned int j = 0; j < mesh->mNumVertices; j++)
        {
            vertices.push_back(mesh->mVertices[j].x);
            vertices.push_back(mesh->mVertices[j].y);
            vertices.push_back(mesh->mVertices[j].z);

            if (mesh->HasNormals())
            {
                vertices.push_back(mesh->mNormals[j].x);
                vertices.push_back(mesh->mNormals[j].y);
                vertices.push_back(mesh->mNormals[j].z);
            }

            if (mesh->mTextureCoords[0])
            {
                vertices.push_back(mesh->mTextureCoords[0][j].x);
                vertices.push_back(mesh->mTextureCoords[0][j].y);
            }

            numVertex++;
        }

        for (unsigned int j = 0; j < mesh->mNumFaces; j++)
        {
            aiFace face = mesh->mFaces[j];
            for (unsigned int k = 0; k < face.mNumIndices; k++)
            {
                indices.push_back(face.mIndices[k]);
            }

            numIndex++;
        }

        VertexArray* vertexArray = new VertexArray(vertices.data(), numVertex,
            VertexArray::PosNormTex, indices.data(), numIndex);
        mVertexArrays.push_back(vertexArray);

        if (mesh->mMaterialIndex >= 0)
        {
            aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
            mTextures.emplace_back();

            LoadTextures(material, aiTextureType_DIFFUSE, "texture_diffuse", i);
            LoadTextures(material, aiTextureType_SPECULAR, "texture_specular", i);
        }
    }

    mFileName = fileName;
    return true;
}

void Mesh::Unload()
{
    for (auto vertexArray : mVertexArrays)
    {
        delete vertexArray;
    }
    mVertexArrays.clear();

    mTextures.clear();
}

Texture* Mesh::GetTexture(size_t meshIndex, size_t textureIndex)
{
    if (meshIndex < mTextures.size() && textureIndex < mTextures[meshIndex].size())
    {
        return mTextures[meshIndex][textureIndex];
    }
    return nullptr;
}

void Mesh::LoadTextures(aiMaterial* material, aiTextureType type, 
    const std::string& typeName, size_t meshIndex)
{
    for (unsigned int i = 0; i < material->GetTextureCount(type); i++)
    {
        aiString str;
        material->GetTexture(type, i, &str);

        Texture* texture = TextureManager::Get()->GetTexture(str.C_Str());
        if (texture)
        {
            mTextures[meshIndex].push_back(texture);
        }
    }
}