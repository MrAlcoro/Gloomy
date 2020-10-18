#include "Application.h"
#include "ModuleFBXLoader.h"
#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"
#include "Assimp/include/cfileio.h"

#pragma comment (lib, "Assimp/libx86/assimp.lib")


ModuleFBXLoader::ModuleFBXLoader(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	name.assign("fbx_loader");
}

ModuleFBXLoader::~ModuleFBXLoader()
{}

// -----------------------------------------------------------------
bool ModuleFBXLoader::Start()
{
	bool ret = true;

	struct aiLogStream stream;
	stream = aiGetPredefinedLogStream(aiDefaultLogStream_DEBUGGER, nullptr);
	aiAttachLogStream(&stream);

	return ret;
}

// -----------------------------------------------------------------
bool ModuleFBXLoader::CleanUp()
{
	aiDetachAllLogStreams();

	return true;
}

// -----------------------------------------------------------------
bool ModuleFBXLoader::LoadFBX(const char* file_name)
{
	bool ret = true;
	const aiScene* scene = aiImportFile(file_name, aiProcessPreset_TargetRealtime_MaxQuality);

	if (scene != nullptr && scene->HasMeshes())
	{
		aiNode* rootNode = scene->mRootNode;

		for (int i = 0; i < rootNode->mNumChildren; ++i)
		{
			LoadModel(scene, rootNode->mChildren[i], file_name);
		}

		aiReleaseImport(scene);
		return ret;
	}
	else
		return false;
}

// -----------------------------------------------------------------
void ModuleFBXLoader::LoadModel(const aiScene* scene, aiNode* node, const char* path)
{
	if (node->mNumMeshes <= 0)
	{
		LOG("MESH NOT FOUND! =================");
	}
	else
	{
		for (int i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* new_mesh = scene->mMeshes[node->mMeshes[i]];
			ModelConfig mesh = ModelConfig();
			mesh.num_vertices = new_mesh->mNumVertices;
			mesh.vertices = new uint[mesh.num_vertices * 3];
			memcpy(mesh.vertices, new_mesh->mVertices, sizeof(float) * mesh.num_vertices * 3);

			if (new_mesh->HasFaces())
			{
				mesh.num_indices = new_mesh->mNumFaces * 3;
				mesh.indices = new uint[mesh.num_indices];
				for (uint j = 0; j < new_mesh->mNumFaces; j++)
				{
					if (new_mesh->mFaces[j].mNumIndices == 3)
					{
						memcpy(&mesh.indices[j * 3], new_mesh->mFaces[j].mIndices, 3 * sizeof(uint));
					}
				}
			}

			meshes.push_back(mesh);
		}
	}

	for (int i = 0; i < node->mNumChildren; i++)
	{
		LoadModel(scene, node->mChildren[i], path);
	}
}

// -----------------------------------------------------------------
update_status ModuleFBXLoader::Update(float dt)
{

	return UPDATE_CONTINUE;
}
