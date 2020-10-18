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
update_status ModuleFBXLoader::Update(float dt)
{

	return UPDATE_CONTINUE;
}
