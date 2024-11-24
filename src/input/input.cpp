#include "pch.h"
#include "input.h"

namespace
{
	bool ImGuiWantsKeyboard()
	{
		const ImGuiIO& io = ImGui::GetIO();
		return io.WantCaptureKeyboard;
	}
}

bool Input::IsKeyDown(int key)
{
	return !ImGuiWantsKeyboard() && ::IsKeyDown(key);
}

bool Input::IsKeyPressed(int key)
{
	return !ImGuiWantsKeyboard() && ::IsKeyPressed(key);
}

bool Input::IsKeyReleased(int key)
{
	return !ImGuiWantsKeyboard() && ::IsKeyReleased(key);
}

bool Input::IsKeyUp(int key)
{
	return !ImGuiWantsKeyboard() && ::IsKeyUp(key);
}
