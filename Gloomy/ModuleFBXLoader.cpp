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
void ModuleFBXLoader::LoadModel(const char* file_name)
{
	aiMesh* new_mesh = nullptr;
	ModelConfig model;
	const aiScene* scene = aiImportFile(file_name, aiProcessPreset_TargetRealtime_MaxQuality);

	if (scene != nullptr && scene->HasMeshes())
	{
		for (int i = 0; i <= scene->mNumMeshes; ++i)
		{
			// TODO: cycle through the array of meshes
		}
		aiReleaseImport(scene);
	}
	else
		LOG("Error loading scene %s", file_name);

	model.num_vertices = new_mesh->mNumVertices;
	model.vertices = new float[model.num_vertices * 3];
	memcpy(model.vertices, new_mesh->mVertices, sizeof(float) * model.num_vertices * 3);
	LOG("New mesh with %d vertices", model.num_vertices);

	if (new_mesh->HasFaces())
	{
		model.num_indices = new_mesh->mNumFaces * 3;
		model.indices = new uint[model.num_indices];

		for (uint i = 0; i < new_mesh->mNumFaces; ++i)
		{
			if (new_mesh->mFaces[i].mNumIndices != 3)
			{
				LOG("WARNING, geometry face with != 3 inidces!");
			}
			else
			{
				memcpy(&model.indices[i * 3], new_mesh->mFaces[i].mIndices, 3 * sizeof(uint));
			}
		}
	}
}

// -----------------------------------------------------------------
update_status ModuleFBXLoader::Update(float dt)
{

	return UPDATE_CONTINUE;
}
