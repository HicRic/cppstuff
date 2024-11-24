#include "pch.h"

#include "cppstuff.h"

#include <cstdio>

#include "text.h"
#include "config/config.h"
#include "resources/resources.h"
#include "draw/draw.h"
#include "input/input.h"
#include "state/State.h"
#include "systems/grideditor.h"

namespace
{
	bool showImgui = false;
}

void UpdateInput(State::Input& input) 
{
	input.deltaTime = GetFrameTime();

	// Why add UINT_MAX to time?
	// https://randomascii.wordpress.com/2012/02/13/dont-store-that-in-a-float/
	// Time is best stored in a double due to precision issues after running for a while,
	// and 'starting' time at 2^32 means the precision doesn't change over time.
	// This helps us discover precision issues where we've used floats to store time,
	// as the precision issues will occur immediately instead of requiring hours of play.
	input.time = GetTime() + UINT_MAX;

	input.horizontalMovement = 0;
	input.horizontalMovement += (Input::IsKeyDown(KEY_LEFT) || Input::IsKeyDown(KEY_A)) ? -1.f : 0;
	input.horizontalMovement += (Input::IsKeyDown(KEY_RIGHT) || Input::IsKeyDown(KEY_D)) ? 1.f : 0;

	input.verticalMovement = 0;
	input.verticalMovement += (Input::IsKeyDown(KEY_UP) || Input::IsKeyDown(KEY_W)) ? -1.f : 0;
	input.verticalMovement += (Input::IsKeyDown(KEY_DOWN) || Input::IsKeyDown(KEY_S)) ? 1.f : 0;

	input.mousePos = GetMousePosition();
	input.isMouseLeftButtonDown = IsMouseButtonDown(MOUSE_BUTTON_LEFT);
}

void Update(const State::Input& input, State::World& world)
{
	static GridEditor gridEditorSystem;
	gridEditorSystem.update(input, world);
}

void InitSim(State::World& world)
{
	world.cam.target = Vector2 {0,0};
	world.cam.zoom = 1.f;
	world.cam.offset = Vector2 {0,0};

	//RulesSystem::Init(world, config);

}

void ImGuiInit()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplRaylib_Init();
	ImGui_ImplRaylib_LoadDefaultFontAtlas();
}

void ImGuiUpdate()
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

void ImGuiRender()
{
	ImGui::Render();
	ImGui_ImplRaylib_Render(ImGui::GetDrawData());
}

int main(int /*argc*/, char* /*args*/[])
{
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
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

	ImGuiInit();

	UpdateInput(input);
	InitSim(world);
	
	while (!WindowShouldClose())
	{
		ImGuiUpdate();
		
		UpdateInput(input);
		Update(input, world);

		BeginDrawing();
		DrawGame(world, res);
		ImGuiRender();
		EndDrawing();
	}

	res.unload();

	ImGui_ImplRaylib_Shutdown();
	ImGui::DestroyContext();

	CloseWindow();

	return 0;
}
