#include "pch.h"
#include "input.h"

#include "state/state.h"

namespace
{
	bool imGuiWantsKeyboard()
	{
		const ImGuiIO& io = ImGui::GetIO();
		return io.WantCaptureKeyboard;
	}
	
	bool imGuiWantsMouse()
	{
		const ImGuiIO& io = ImGui::GetIO();
		return io.WantCaptureMouse;
	}
}

bool Input::isKeyDown(int key)
{
	return !imGuiWantsKeyboard() && ::IsKeyDown(key);
}

bool Input::isKeyPressed(int key)
{
	return !imGuiWantsKeyboard() && ::IsKeyPressed(key);
}

bool Input::isKeyReleased(int key)
{
	return !imGuiWantsKeyboard() && ::IsKeyReleased(key);
}

bool Input::isKeyUp(int key)
{
	return !imGuiWantsKeyboard() && ::IsKeyUp(key);
}

void Input::update(State::Input& input) 
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
	input.horizontalMovement += (isKeyDown(KEY_LEFT) || isKeyDown(KEY_A)) ? -1.f : 0;
	input.horizontalMovement += (isKeyDown(KEY_RIGHT) || isKeyDown(KEY_D)) ? 1.f : 0;

	input.verticalMovement = 0;
	input.verticalMovement += (isKeyDown(KEY_UP) || isKeyDown(KEY_W)) ? -1.f : 0;
	input.verticalMovement += (isKeyDown(KEY_DOWN) || isKeyDown(KEY_S)) ? 1.f : 0;

	if (!imGuiWantsMouse())
	{
		input.mousePos = GetMousePosition();
		input.isWallToggleInputActive = IsMouseButtonDown(MOUSE_BUTTON_LEFT);
		input.isWaterToggleInputActive = IsMouseButtonDown(MOUSE_BUTTON_RIGHT);
	}

	if (!imGuiWantsKeyboard())
	{
		input.isStartPlacementInputActive = IsKeyDown(KEY_ONE);
		input.isGoalPlacementInputActive = IsKeyDown(KEY_TWO);
	}
}