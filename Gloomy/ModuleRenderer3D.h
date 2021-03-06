#ifndef __MODULERENDERER3D_H__
#define __MODULERENDERER3D_H__

#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "Light.h"

#define MAX_LIGHTS 8

struct ModelConfig;

class ModuleRenderer3D : public Module
{
public:
	ModuleRenderer3D(Application* app, bool start_enabled = true);
	~ModuleRenderer3D();

	bool Init();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	void OnResize(int width, int height);
	bool DrawMeshes(ModelConfig mesh);

public:

	Light lights[MAX_LIGHTS];
	SDL_GLContext context;
	mat3x3 NormalMatrix;
	mat4x4 ModelMatrix, ViewMatrix, ProjectionMatrix;

	bool enable_wireframe = false;
};

#endif