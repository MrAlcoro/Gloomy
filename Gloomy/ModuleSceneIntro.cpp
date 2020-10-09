#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
// Provisional
#include "SDL\include\SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>

#pragma comment (lib, "glu32.lib")    /* link OpenGL Utility lib     */
#pragma comment (lib, "opengl32.lib") /* link Microsoft OpenGL lib   */

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");
	return true;
}

// PreUpdate
update_status ModuleSceneIntro::PreUpdate(float dt)
{
	return(UPDATE_CONTINUE);
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();

	// Provisional
	/*
	glLineWidth(2.0f);

	glBegin(GL_LINES);
	glVertex3f(0.f, 0.f, 0.f);
	glVertex3f(0.f, 10.f, 0.f);
	glEnd();

	glLineWidth(1.0f);
	*/

	glBegin(GL_TRIANGLES);

	glVertex3f(0.f, 0.f, 0.f); // 0
	glVertex3f(0.f, 1.f, 0.f); // Y
	glVertex3f(1.f, 0.f, 0.f); // X
	
	glVertex3f(1.f, 0.f, 0.f); // X
	glVertex3f(0.f, 1.f, 0.f); // Y
	glVertex3f(1.f, 1.f, 0.f); // 0
	
	glVertex3f(0.f, 0.f, 1.f); // Z
	glVertex3f(0.f, 1.f, 0.f); // Y
	glVertex3f(0.f, 0.f, 0.f); // 0	
	
	glVertex3f(0.f, 1.f, 1.f); // 0	
	glVertex3f(0.f, 1.f, 0.f); // Y
	glVertex3f(0.f, 0.f, 1.f); // Z	
	
	glVertex3f(1.f, 0.f, 0.f); // X
	glVertex3f(1.f, 1.f, 1.f); // Y
	glVertex3f(1.f, 0.f, 1.f); // 0	
	
	glVertex3f(1.f, 1.f, 0.f); // 0	
	glVertex3f(1.f, 1.f, 1.f); // Y
	glVertex3f(1.f, 0.f, 0.f); // X

	glVertex3f(0.f, 1.f, 1.f); // 0	
	glVertex3f(0.f, 0.f, 1.f); // Z
	glVertex3f(1.f, 1.f, 1.f); // Y
	
	glVertex3f(1.f, 0.f, 1.f); // Y
	glVertex3f(1.f, 1.f, 1.f); // 0
	glVertex3f(0.f, 0.f, 1.f); // Z	
	
	// Top
	glVertex3f(0.f, 1.f, 0.f); // Y
	glVertex3f(1.f, 1.f, 1.f); // 0
	glVertex3f(1.f, 1.f, 0.f); // X

	glVertex3f(0.f, 1.f, 1.f); // 0
	glVertex3f(1.f, 1.f, 1.f); // X
	glVertex3f(0.f, 1.f, 0.f); // Y
	
	// Bottom
	glVertex3f(0.f, 0.f, 0.f); // Y
	glVertex3f(1.f, 0.f, 0.f); // X
	glVertex3f(1.f, 0.f, 1.f); // 0
	
	glVertex3f(0.f, 0.f, 1.f); // 0
	glVertex3f(0.f, 0.f, 0.f); // Y
	glVertex3f(1.f, 0.f, 1.f); // X
	
	glEnd();

	return UPDATE_CONTINUE;
}