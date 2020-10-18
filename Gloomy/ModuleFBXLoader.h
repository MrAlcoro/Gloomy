#ifndef __MODULEFBXLOADER_H__
#define __MODULEFBXLOADER_H__

#include "Module.h"


struct ModelConfig
{
	uint id_indices = 0;
	uint num_indices = 0;
	uint* indices = nullptr;

	uint id_vertices = 0;
	uint num_vertices = 0;
	float* vertices = nullptr;
};

class ModuleFBXLoader : public Module
{
public:
	ModuleFBXLoader(Application* app, bool start_enabled = true);
	~ModuleFBXLoader();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();
};
#endif