#ifndef __MODULEIMGUI_H__
#define __MODULEIMGUI_H__

#include "Module.h"
#include "Globals.h"
#include "imGUI/imgui.h"

#define GRAPH_ARRAY_SIZE 70

class ModuleImGUI : public Module
{
private:
	int width = 1280;
	int height = 1024;
	float brightness = 1.0;
	float fps_array[GRAPH_ARRAY_SIZE];
	float ms_array[GRAPH_ARRAY_SIZE];

public:
	ModuleImGUI(Application* app, bool start_enabled = true);
	~ModuleImGUI();

	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	bool CleanUp();

	// Save & load
	bool Save();
	bool Load();
};

#endif