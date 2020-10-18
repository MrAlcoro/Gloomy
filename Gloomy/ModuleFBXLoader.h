#ifndef __MODULEFBXLOADER_H__
#define __MODULEFBXLOADER_H__

#include "Module.h"
#include <vector>
#include <string>

using namespace std;

class aiScene;
class aiNode;

struct ModelConfig
{
	uint id_indices = 0;
	uint num_indices = 0;
	uint* indices = nullptr;

	uint id_vertices = 0;
	uint num_vertices = 0;
	uint* vertices = nullptr;
};

class ModuleFBXLoader : public Module
{
public:
	ModuleFBXLoader(Application* app, bool start_enabled = true);
	~ModuleFBXLoader();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();
	bool LoadFBX(string file_name);
	void LoadModel(const aiScene* scene, aiNode* node);

public:
	ModelConfig data;
	vector<ModelConfig> meshes;
};
#endif