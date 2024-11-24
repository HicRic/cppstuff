#include "pch.h"
#include "resources.h"

namespace
{
	constexpr char cannonTexturePath[] = "res/textures/cannon.png";
	constexpr char missileTexturePath[] = "res/textures/missile.png";
	constexpr char alien1TexturePath[] = "res/textures/alien1.png";
	constexpr char alien2TexturePath[] = "res/textures/alien2.png";
}

void Resources::load()
{
	assert(!loaded);
	loaded = true;
	cannon = LoadTexture(cannonTexturePath);
	missile = LoadTexture(missileTexturePath);
	alien1 = LoadTexture(alien1TexturePath);
	alien2 = LoadTexture(alien2TexturePath);
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
