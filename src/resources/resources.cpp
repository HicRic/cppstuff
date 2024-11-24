#include "pch.h"
#include "resources.h"

namespace
{
	constexpr char CANNON_TEXTURE_PATH[] = "res/textures/cannon.png";
	constexpr char MISSILE_TEXTURE_PATH[] = "res/textures/missile.png";
	constexpr char ALIEN1_TEXTURE_PATH[] = "res/textures/alien1.png";
	constexpr char ALIEN2_TEXTURE_PATH[] = "res/textures/alien2.png";
}

void Resources::load()
{
	assert(!loaded);
	loaded = true;
	cannon = LoadTexture(CANNON_TEXTURE_PATH);
	missile = LoadTexture(MISSILE_TEXTURE_PATH);
	alien1 = LoadTexture(ALIEN1_TEXTURE_PATH);
	alien2 = LoadTexture(ALIEN2_TEXTURE_PATH);
}

void Resources::unload()
{
	assert(loaded);
	loaded = false;
	UnloadTexture(cannon);
	UnloadTexture(missile);
	UnloadTexture(alien1);
	UnloadTexture(alien2);
}
