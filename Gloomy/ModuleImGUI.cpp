#include "Application.h"
#include <vector>
#include "ModuleImGUI.h"
#include "Glew\include\glew.h"
#include "ImGUI/imgui_impl_sdl_gl3.h"

#pragma comment( lib, "Glew/libx86/glew32.lib" )

#define IM_ARRAYSIZE(_ARR)  ((int)(sizeof(_ARR)/sizeof(*_ARR)))

ModuleImGUI::ModuleImGUI(Application* app, bool start_enabled) : Module(app, start_enabled) 
{
	name.assign("imgui");
}

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
	static bool show_about_window = false;
	static bool show_engine_configuration = false;
	static bool quit = false;
	static bool direct_mode_cube = false;
	static bool vertex_array_cube = false;
	static bool indices_cube = false;


	if (direct_mode_cube)
	{
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
	}

	if (vertex_array_cube)
	{
		GLuint VertexArrayID;
		glGenVertexArrays(1, &VertexArrayID);
		glBindVertexArray(VertexArrayID);

		static const GLfloat g_vertex_buffer_data[] = {
			-1.0f,-1.0f,-1.0f,
			-1.0f,-1.0f, 1.0f,
			-1.0f, 1.0f, 1.0f,
			1.0f, 1.0f,-1.0f,
			-1.0f,-1.0f,-1.0f,
			-1.0f, 1.0f,-1.0f,
			1.0f,-1.0f, 1.0f,
			-1.0f,-1.0f,-1.0f,
			1.0f,-1.0f,-1.0f,
			1.0f, 1.0f,-1.0f,
			1.0f,-1.0f,-1.0f,
			-1.0f,-1.0f,-1.0f,
			-1.0f,-1.0f,-1.0f,
			-1.0f, 1.0f, 1.0f,
			-1.0f, 1.0f,-1.0f,
			1.0f,-1.0f, 1.0f,
			-1.0f,-1.0f, 1.0f,
			-1.0f,-1.0f,-1.0f,
			-1.0f, 1.0f, 1.0f,
			-1.0f,-1.0f, 1.0f,
			1.0f,-1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,
			1.0f,-1.0f,-1.0f,
			1.0f, 1.0f,-1.0f,
			1.0f,-1.0f,-1.0f,
			1.0f, 1.0f, 1.0f,
			1.0f,-1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,
			1.0f, 1.0f,-1.0f,
			-1.0f, 1.0f,-1.0f,
			1.0f, 1.0f, 1.0f,
			-1.0f, 1.0f,-1.0f,
			-1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,
			-1.0f, 1.0f, 1.0f,
			1.0f,-1.0f, 1.0f
		};

		GLuint vertexbuffer;
		glGenBuffers(1, &vertexbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,
			3,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)0
		);
	}

	if (indices_cube)
	{
		std::vector<GLfloat> vertices;
		std::vector<GLfloat> indices;
		
		vertices = { -1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f };

		indices = { 0, 1, 2,   2, 3, 0,
			4, 5, 6,   6, 7, 4,
			8, 9,10,  10,11, 8,
			12,13,14,  14,15,12,
			16,17,18,  18,19,16,
			20,21,22,  22,23,20 };

		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices[0]);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, &indices[0]);
		glDrawArrays(GL_TRIANGLES, 0, 12 * 3);

		glDisableVertexAttribArray(0);

		glDisableClientState(0);
	}

	if (show_test_window)
	{
		ImGui::ShowTestWindow();
	}

	if (show_engine_configuration)
	{
		ImGui::Begin("Engine configuration");

		if (ImGui::CollapsingHeader("Application"))
		{
			ImGui::TextWrapped("Engine name: Gloomy");

			ImGui::Separator();

			for (uint i = 0; i < GRAPH_ARRAY_SIZE; i++)
			{
				fps_array[i] = fps_array[i + 1];
			}
			fps_array[GRAPH_ARRAY_SIZE - 1] = ImGui::GetIO().Framerate;
			char fps_title[25];
			sprintf_s(fps_title, 25, "Framerate %.1f", fps_array[GRAPH_ARRAY_SIZE - 1]);
			ImGui::PlotHistogram("", fps_array, IM_ARRAYSIZE(fps_array), 30, fps_title, 0.0f, 130.0f, ImVec2(0, 80));

			for (uint i = 0; i < GRAPH_ARRAY_SIZE; i++)
			{
				ms_array[i] = ms_array[i + 1];
			}
			ms_array[GRAPH_ARRAY_SIZE - 1] = 1000.0f / ImGui::GetIO().Framerate;
			char ms_title[25];
			sprintf_s(ms_title, 25, "Milliseconds %.1f", ms_array[GRAPH_ARRAY_SIZE - 1]);
			ImGui::PlotHistogram("", ms_array, IM_ARRAYSIZE(ms_array), 30, ms_title, 0.0f, 130.0f, ImVec2(0, 80));
		}

		if (ImGui::CollapsingHeader("Screen configuration"))
		{
			ImGuiStyle& style = ImGui::GetStyle();
			ImGui::DragFloat("Alpha", &style.Alpha, 0.005f, 0.20f, 1.0f, "%.2f");

			ImGui::SliderFloat("Brightness", &brightness, 0, 2, NULL);

			ImGui::SliderInt("Width", &width, 0, 1920, NULL);

			ImGui::SliderInt("Height", &height, 0, 1080, NULL);

			if (ImGui::Checkbox("Fullscreen", &App->window->wfullscreen))
			{
				App->window->SetFullScreen(&App->window->wfullscreen);
			}

			if (ImGui::Checkbox("Windowed", &App->window->wwindowed_fullscreen))
			{
				App->window->SetWindowed(&App->window->wwindowed_fullscreen);
			}

			if (ImGui::Checkbox("Borderless", &App->window->wborderless))
			{
				App->window->SetWindowFullDesktop();
				width = 1920;
				height = 1080;
			}

			if (ImGui::Button("Apply"))
			{
				App->window->SetWindowSize(width, height);
				App->window->SetWindowBrigthness(brightness);
			}
		}

		if (ImGui::CollapsingHeader("Input"))
		{
			ImGui::TextWrapped("Mouse position:");
			ImGui::SameLine();
			ImGui::TextColored({ 255, 255, 0, 255 }, "X: %i ", App->input->GetMouseX());
			ImGui::SameLine();
			ImGui::TextColored({ 255, 255, 0, 255 }, "Y: %i", App->input->GetMouseY());
		}

		if (ImGui::CollapsingHeader("User's information"))
		{
			ImGui::Text("Glew version: %s", glewGetString(GLEW_VERSION));
			ImGui::Separator();
			ImGui::Text("Vendor: %s", glGetString(GL_VENDOR));
			ImGui::Text("Renderer: %s", glGetString(GL_RENDERER));
			ImGui::Text("OpenGL version supported: %s", glGetString(GL_VERSION));
			ImGui::Text("GLSL: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
		}

		ImGui::End();
	}

	if (show_about_window)
	{
		ImGui::Begin("About");

		ImGui::SetNextWindowSize(ImVec2(520, 600), ImGuiCond_FirstUseEver);

		ImGui::TextWrapped("Gloomy - by Alexis Cosano Rodriguez");
		ImGui::Separator();
		ImGui::TextWrapped("3D Game Engine created as a college project.");
		ImGui::Separator();
		ImGui::TextWrapped("Libraries used");
		ImGui::Text("- ImGui  v1.52");
		ImGui::SameLine();
		if (ImGui::MenuItem("Download here"))
		{
			App->RequestBrowser("https://github.com/ocornut/imgui");
		}
		ImGui::Text("- Parson");
		ImGui::SameLine();
		if (ImGui::MenuItem("Download here"))
		{
			App->RequestBrowser("http://kgabis.github.com/parson/");
		}

		ImGui::Text("- MathGeoLib  v2.0");
		ImGui::SameLine();
		if (ImGui::MenuItem("Download here"))
		{
			App->RequestBrowser("https://github.com/juj/MathGeoLib");
		}

		ImGui::Text("- Glew  v7.0");
		ImGui::SameLine();
		if (ImGui::MenuItem("Download here"))
		{
			App->RequestBrowser("http://glew.sourceforge.net/");
		}

		ImGui::Text("- SDL  v2.0");
		ImGui::SameLine();
		if (ImGui::MenuItem("Download here"))
		{
			App->RequestBrowser("https://www.libsdl.org/download-2.0.php");
		}

		ImGui::Text("- Assimp  v3.3.1");
		ImGui::SameLine();
		if (ImGui::MenuItem("Download here"))
		{
			App->RequestBrowser("http://assimp.sourceforge.net/");
		}

		ImGui::Text("- PCG  v0.98.1");
		ImGui::SameLine();
		if (ImGui::MenuItem("Download here"))
		{
			App->RequestBrowser("https://github.com/imneme/pcg-cpp/releases");
		}

		ImGui::Separator();
		ImGui::Text("This engine is under the MIT license, to know more, click");
		ImGui::SameLine(); if (ImGui::Button("here.")) { App->RequestBrowser("https://opensource.org/about"); }

		ImGui::End();
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

			if (ImGui::MenuItem("Save engine configuration"))
			{
				App->CallSave();
			}
			if (ImGui::MenuItem("Load engine configuration"))
			{
				App->CallLoad();
			}

			ImGui::Separator();

			if (ImGui::MenuItem("Exit"))
			{
				App->input->Quit();
			}
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Shapes"))
		{		
			ImGui::Text("Cubes");
			ImGui::Separator();

			ImGui::Checkbox("Direct mode", &direct_mode_cube);

			ImGui::Checkbox("Array of vertices", &vertex_array_cube);

			ImGui::Checkbox("Indices", &indices_cube);
			
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Rendering"))
		{
			if (ImGui::Checkbox("Wireframe", &App->renderer3D->enable_wireframe))
			{
				(App->renderer3D->enable_wireframe) ? glPolygonMode(GL_FRONT_AND_BACK, GL_LINE) : glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Help"))
		{
			ImGui::Checkbox("Show test window", &show_test_window);

			ImGui::Separator();

			if (ImGui::MenuItem("Download the latest release"))
				App->RequestBrowser("https://github.com/MrAlcoro/Gloomy/releases");

			if (ImGui::MenuItem("Report a bug"))
				App->RequestBrowser("https://github.com/MrAlcoro/Gloomy/issues");

			ImGui::Checkbox("About", &show_about_window);

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Utilities"))
		{
			ImGui::Checkbox("Engine configuration", &show_engine_configuration);

			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();
	}

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

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

// Save & load ----------------------------------------------------------------------
bool ModuleImGUI::Save()
{
	if (App->config != NULL)
	{
		if (json_object_has_value(App->modules_object, name.c_str()) == false)
		{
			json_object_set_null(App->modules_object, name.c_str());
			json_serialize_to_file_pretty(App->config, "config.json");
		}

		LOG("Saving module %s", name.c_str());
	}
	else
	{
		json_object_set_null(App->modules_object, name.c_str());

		LOG("Saving module %s", name.c_str());
	}


	return(true);
}

bool ModuleImGUI::Load()
{
	bool ret = false;

	if (App->config != NULL)
	{
		if (json_object_has_value(App->modules_object, name.c_str()) != false)
		{
			LOG("Loading module %s", name.c_str());
			ret = true;
		}
		else
		{
			LOG("Could not find the node named %s inside the file config.json", name.c_str());
			ret = false;
		}
	}
	else
	{
		LOG("Document config.json not found.");
		ret = false;
	}

	return ret;
}
