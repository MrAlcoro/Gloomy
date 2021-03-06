#include "Application.h"

Application::Application()
{
	window = new ModuleWindow(this);
	input = new ModuleInput(this);
	scene_intro = new ModuleSceneIntro(this);
	renderer3D = new ModuleRenderer3D(this);
	camera = new ModuleCamera3D(this);
	imgui = new ModuleImGUI(this);
	fbx_loader = new ModuleFBXLoader(this);

	// The order of calls is very important!
	// Modules will Init() Start() and Update in this order
	// They will CleanUp() in reverse order

	// Main Modules
	AddModule(window);
	AddModule(camera);
	AddModule(input);
	
	// Scenes
	AddModule(scene_intro);
	AddModule(fbx_loader);
	
	// Renderer last!
	AddModule(renderer3D);

	// Interface
	AddModule(imgui);
	
}

Application::~Application()
{
	list<Module*>::iterator item = list_modules.begin();

	while (item != list_modules.end())
	{
		delete (item._Ptr->_Myval);
		item++;
	}
}

bool Application::Init()
{
	bool ret = true;

	void json_set_allocation_functions(JSON_Malloc_Function malloc_fun, JSON_Free_Function free_fun);
	config = json_parse_file("config.json");

	if (config != NULL)
	{
		modules_object = json_value_get_object(config);

		LOG("Document loaded successfully.");
	}
	else
	{
		LOG("Document could not be loaded.");
	}

	// Call Init() in all modules
	list<Module*>::iterator item = list_modules.begin();

	while (item != list_modules.end() && ret == true)
	{
		ret = item._Ptr->_Myval->Init();
		item++;
	}

	// After all Init calls we call Start() in all modules
	LOG("Application Start --------------");
	item = list_modules.begin();

	while (item != list_modules.end() && ret == true)
	{
		ret = item._Ptr->_Myval->Start();
		item++;
	}
	
	ms_timer.Start();
	return ret;
}

// ---------------------------------------------
void Application::PrepareUpdate()
{
	dt = (float)ms_timer.Read() / 1000.0f;
	ms_timer.Start();
}

// ---------------------------------------------
void Application::FinishUpdate()
{
}

// ---------------------------------------------
void Application::RequestBrowser(const char* website_url)
{
	ShellExecuteA(NULL, "open", website_url, NULL, NULL, 0);
}

// Call PreUpdate, Update and PostUpdate on all modules
update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;
	PrepareUpdate();
	

	list<Module*>::iterator item = list_modules.begin();

	while (item != list_modules.end() && ret == UPDATE_CONTINUE)
	{
		ret = item._Ptr->_Myval->PreUpdate(dt);
		item++;
	}

	item = list_modules.begin();

	while (item != list_modules.end() && ret == UPDATE_CONTINUE)
	{
		ret = item._Ptr->_Myval->Update(dt);
		item++;
	}

	item = list_modules.begin();

	while (item != list_modules.end() && ret == UPDATE_CONTINUE)
	{
		ret = item._Ptr->_Myval->PostUpdate(dt);
		item++;
	}

	FinishUpdate();
	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;
	list<Module*>::iterator item = list_modules.begin();

	while (item != list_modules.end() && ret == true)
	{
		ret = item._Ptr->_Myval->CleanUp();
		item++;
	}
	return ret;
}

void Application::AddModule(Module* mod)
{
	list_modules.push_back(mod);
}