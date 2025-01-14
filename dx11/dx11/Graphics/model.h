#pragma once
#include "mesh.h"
using namespace DirectX;

class Model
{
public:
	bool Initialize(const std::string & filePath,ID3D11Device* device, ID3D11DeviceContext* deviceContext,  ConstantBuffer<CB_VS_VertexShader>& cb_vs_vertexshader);
	void Draw(const XMMATRIX& worldMatrix, const XMMATRIX& viewProjectionMatrix);

private:

	std::vector<Mesh> meshes;
	bool LoadModel(const std::string filePath);
	void ProcessNode(aiNode* node, const aiScene* Scene);
	Mesh ProcessMesh(aiMesh* mesh, const aiScene* Scene);
	std::vector<Texture> LoadMaterialTextures(aiMaterial* pMaterial, aiTextureType textureType, const aiScene* pScene);
	TextureStorageType DetermineTextureStorageType(const aiScene* pScene, aiMaterial* pMat, unsigned int index, aiTextureType textureType);
	int GetTextureIndex(aiString * pStr);

	ID3D11Device* device = nullptr;
	ID3D11DeviceContext* deviceContext = nullptr;

	ConstantBuffer<CB_VS_VertexShader>* cb_vs_vertexshader = nullptr;
	std::string directory = "";
};