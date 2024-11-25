#include "pch.h"

#include "cppstuff.h"

#include <cstdio>

#include "text.h"
#include "config/config.h"
#include "resources/resources.h"
#include "draw/draw.h"
#include "input/input.h"
#include "state/state.h"
#include "systems/grideditor.h"
#include "systems/pathfind.h"

namespace
{
	bool showImgui = false;
}



void update(const State::Input& input, State::World& world)
{
	static GridEditor gridEditorSystem;
	gridEditorSystem.update(input, world);

	Pathfind::update(world);
}

void initSim(State::World& world)
{
	world.cam.target = Vector2 {0,0};
	world.cam.zoom = 1.f;
	world.cam.offset = Vector2 {0,0};

	//RulesSystem::Init(world, config);

}

void imGuiInit()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplRaylib_Init();
	ImGui_ImplRaylib_LoadDefaultFontAtlas();
}

void imGuiUpdate()
{
	ImGui_ImplRaylib_NewFrame();
	ImGui::NewFrame();
	ImGui_ImplRaylib_ProcessEvent();

	if(IsKeyPressed(KEY_GRAVE))
	{
		showImgui = !showImgui;
	}

	if (showImgui)
	{
		ImGui::ShowDemoWindow(&showImgui);
	}
}

void imGuiRender()
{
	ImGui::Render();
	ImGui_ImplRaylib_Render(ImGui::GetDrawData());
}

int main(int /*argc*/, char* /*args*/[])
{
	SetConfigFlags(/*FLAG_VSYNC_HINT |*/ FLAG_WINDOW_RESIZABLE);
	//SetTargetFPS(144);
	
	InitWindow(Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT, Text::TITLE);
	SetWindowMinSize(Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);
	SetExitKey(KEY_ESCAPE);

	Resources res = {};
	printf("Resources struct: %llu bytes\n", sizeof(Resources));
	res.load();
	
	State::Input input = {};
	printf("Input struct: %llu bytes\n", sizeof(input));

	State::World world = {};
	printf("World struct: %llu bytes\n", sizeof(world));

	imGuiInit();

	Input::update(input);
	initSim(world);
	
	while (!WindowShouldClose())
	{
		imGuiUpdate();
		
		Input::update(input);
		update(input, world);

		BeginDrawing();
		Draw::drawGame(world, res);
		imGuiRender();
		EndDrawing();
	}

	res.unload();

	ImGui_ImplRaylib_Shutdown();
	ImGui::DestroyContext();

	CloseWindow();

	return 0;
}
