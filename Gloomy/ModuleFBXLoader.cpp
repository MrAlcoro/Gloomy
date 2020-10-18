#include "Application.h"
#include "ModuleFBXLoader.h"
#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"
#include "Assimp/include/cfileio.h"
#include "Glew/include/glew.h"
#include "SDL\include\SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>

#pragma comment( lib, "Glew/libx86/glew32.lib" )
#pragma comment (lib, "glu32.lib")    /* link OpenGL Utility lib     */
#pragma comment (lib, "opengl32.lib") /* link Microsoft OpenGL lib   */

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
bool ModuleFBXLoader::LoadFBX(string file_name)
{
	bool ret = true;
	
	const aiScene* scene = aiImportFile(file_name.c_str(), aiProcessPreset_TargetRealtime_MaxQuality);

	if (scene != nullptr && scene->HasMeshes())
	{
		aiNode* root = scene->mRootNode;

		for (int i = 0; i < root->mNumChildren; i++)
		{
			LoadModel(scene, root->mChildren[i]);
		}

		aiReleaseImport(scene);
		LOG("Loading scene with path: %s", file_name.c_str());
		return ret;
	}
	else
	{
		LOG("Error loading scene %s", file_name.c_str());
		return false;
	}
}

// -----------------------------------------------------------------
void ModuleFBXLoader::LoadModel(const aiScene* scene, aiNode* node)
{
	if (node->mNumMeshes >= 0)
	{
		for (int i = 0; i < node->mNumMeshes; ++i)
		{
			aiMesh* current_mesh = scene->mMeshes[node->mMeshes[i]];
			data = ModelConfig();

			data.num_vertices = current_mesh->mNumVertices;
			data.vertices = new uint[data.num_vertices * 3];

			memcpy(data.vertices, current_mesh->mVertices, sizeof(float) * data.num_vertices * 3);

			glGenBuffers(1, (GLuint*)&(data.id_vertices));
			glBindBuffer(GL_ARRAY_BUFFER, data.id_vertices);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * data.num_vertices, data.vertices, GL_STATIC_DRAW);

			LOG("Mesh with %d vertices.", data.num_vertices);

			if (current_mesh->HasFaces())
			{
				data.num_indices = current_mesh->mNumFaces * 3;
				data.indices = new uint[data.num_indices];

				for (uint j = 0; j < current_mesh->mNumFaces; ++j)
				{
					if (current_mesh->mFaces[j].mNumIndices != 3)
					{
						LOG("WARNING: geometry face with != 3 index!");
					}
					else
					{
						memcpy(&data.indices[j * 3], current_mesh->mFaces[j].mIndices, 3 * sizeof(float));
					}
				}

				glGenBuffers(1, (GLuint*)&(data.id_indices));
				glBindBuffer(GL_ARRAY_BUFFER, data.id_indices);
				glBufferData(GL_ARRAY_BUFFER, sizeof(float) * data.num_indices, data.indices, GL_STATIC_DRAW);
			}

			meshes.push_back(data);

			LOG("Loaded mesh with %i vertices.", data.num_vertices);
			LOG("Loaded mesh with %i indices.", data.num_indices);
			LOG("Loaded mesh with %i triangles.", data.num_vertices / 3);
		}
	}
	else
	{
		LOG("This node has no meshes.");
	}

	for (int k = 0; k < node->mNumChildren; k++)
	{
		LoadModel(scene, node->mChildren[k]);
	}
}

// -----------------------------------------------------------------
update_status ModuleFBXLoader::Update(float dt)
{

	return UPDATE_CONTINUE;
}
