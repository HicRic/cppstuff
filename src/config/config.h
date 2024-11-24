#pragma once

namespace Config
{
	constexpr int GRID_SIZE_X = 64;
	constexpr int GRID_SIZE_Y = 32;
	constexpr float START_GRID_SCALE = 32.0f;  

	constexpr int SCREEN_WIDTH = (int)((float)GRID_SIZE_X * START_GRID_SCALE);
	constexpr int SCREEN_HEIGHT = (int)((float)GRID_SIZE_Y * START_GRID_SCALE);
};
