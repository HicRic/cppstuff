#pragma once

namespace State { struct Input; }

namespace Input
{
	bool isKeyDown(int key);
	bool isKeyPressed(int key);
	bool isKeyReleased(int key);
	bool isKeyUp(int key);
	void update(State::Input& input);
}