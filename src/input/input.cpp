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

bool Input::isKeyDown(int key)
{
	return !ImGuiWantsKeyboard() && ::IsKeyDown(key);
}

bool Input::isKeyPressed(int key)
{
	return !ImGuiWantsKeyboard() && ::IsKeyPressed(key);
}

bool Input::isKeyReleased(int key)
{
	return !ImGuiWantsKeyboard() && ::IsKeyReleased(key);
}

bool Input::isKeyUp(int key)
{
	return !ImGuiWantsKeyboard() && ::IsKeyUp(key);
}
