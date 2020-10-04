#include "Application.h"
#include "ModuleImGUI.h"
#include "Glew\include\glew.h"
#include "ImGUI/imgui_impl_sdl_gl3.h"

#pragma comment( lib, "Glew/libx86/glew32.lib" )

ModuleImGUI::ModuleImGUI(Application* app, bool start_enabled) : Module(app, start_enabled) {}

ModuleImGUI::~ModuleImGUI() {}

// -----------------------------------------------------------------
bool ModuleImGUI::Start()
{
	LOG("Setting up the ImGUI's interface");
	bool ret = true;

	glewInit();
	ImGui_ImplSdlGL3_Init(App->window->window);

	return ret;
}

// -----------------------------------------------------------------
update_status ModuleImGUI::PreUpdate(float dt)
{
	ImGui_ImplSdlGL3_NewFrame(App->window->window);
	return(UPDATE_CONTINUE);
}

// ------------------------------------------------------------------
update_status ModuleImGUI::Update(float dt)
{
	static bool show_test_window = false;
	static bool quit = false;

	if (show_test_window)
	{
		ImGui::ShowTestWindow();
	}

	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			ImGui::Text("New file");
			ImGui::Text("Open file");
			ImGui::Separator();
			ImGui::Text("Save file");
			ImGui::Separator();
			if (ImGui::MenuItem("Exit"))
			{
				App->input->Quit();
			}
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Window"))
		{
			ImGui::Checkbox("Show test window", &show_test_window);
			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();
	}

	ImGui::Render();

	return (UPDATE_CONTINUE);
}

// ------------------------------------------------------------------
bool ModuleImGUI::CleanUp()
{
	LOG("Cleaning ImGUI's interface");
	ImGui_ImplSdlGL3_Shutdown();

	return true;
}