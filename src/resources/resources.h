#pragma once

#include <raylib.h>

struct Resources
{
	Resources() = default;
	~Resources() = default;

	Resources(const Resources& other) = delete;
	Resources& operator=(const Resources& other) = delete;

	Resources(Resources&& other) = delete;
	Resources& operator=(Resources&& other) = delete;

	Texture2D cannon;
	Texture2D missile;
	Texture2D alien1, alien2;

	bool loaded = false;

	void load();
	void unload();
};
