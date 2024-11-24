#include "pch.h"
#include "draw.h"

#include "resources/resources.h"
#include "config/config.h"
#include "text.h"
#include "state/State.h"


void DrawTextureCentered(const Texture2D& texture, Vector2 position, float rotation, float scale, Color color)
{
	const float width = (float)texture.width * scale;
	const float height = (float)texture.height * scale;

	const Vector2 offset = { width / 2.f, height / 2.f };
	const Rectangle sourceRect { 0, 0, (float)texture.width, (float)texture.height };
	const Rectangle destRect { position.x, position.y, width, height };
	//DrawRectanglePro(destRect, offset, rotation, YELLOW);
	DrawTexturePro(texture, sourceRect, destRect, offset, rotation, color);
}

// void DrawEnemies(double time, const Enemies& enemies, const Resources& res, const Config& config)
// {
// 	const Vector2 offset = { -res.alien1.width / 2.f, -res.alien1.height / 2.f };
//
// 	const int frame = (int64_t)(time * 2.5) % 2;
//
// 	for (int i = 0; i < enemies.activeCount; ++i)
// 	{
// 		Vector2 pos = enemies.formationPosition;
// 		pos.x += enemies.formationCoords[i].x * config.formationDistX;
// 		pos.x += offset.x;
// 		pos.y += enemies.formationCoords[i].y * config.formationDistY;
// 		pos.y += offset.y;
// 		DrawTextureEx(frame == 0 ? res.alien1 : res.alien2, pos, 0, 1, GRAY);
//
// 		//DrawRectangleLinesEx(CollisionSystem::CalcRect(enemies, config, i), 1.0f, RED);
// 	}
//
// 	/*Rectangle enemyRect = EnemySystem::CalcFormationRect(enemies, config);
// 	enemyRect.x += enemies.formationPosition.x;
// 	enemyRect.y += enemies.formationPosition.y;
// 	Rectangle boundsRect = EnemySystem::CalcBoundsRect(config);
// 	DrawRectangleLinesEx(enemyRect, 2.f, RED);
// 	DrawRectangleLinesEx(boundsRect, 2.f, GREEN);*/
// }

void DrawAll2D(const State::World& world, const Resources& res, const Config& config)
{
	BeginMode2D(world.cam);

	DrawTextureCentered(res.alien1, config.testpos, 0, 1, RED);

	// DrawProjectiles(state.sim.playerProjectiles, config, res.missile, 0, BLUE);
	// DrawProjectiles(state.sim.enemyProjectiles, config, res.missile, 180, RED);
	// DrawPlayer(state, res, config);
	//
	// DrawEnemies(state.input.time, state.sim.enemies, res, config);

	EndMode2D();
}

void DrawLabeledInt(const char* label, int value, int xPos, int yPos, int fontSize, Color color)
{
	DrawText(label, xPos, yPos, fontSize, color);
	int labelWidth = MeasureText(label, fontSize);

	constexpr int len = 12;
	static char textBuffer[len] = {};
	int charCount = sprintf_s(textBuffer, len, "%d", value);
	if(charCount > 0)
	{
		DrawText(textBuffer, xPos + labelWidth, yPos, fontSize, color);
	}
}

void DrawUI(const State::World& /*world*/)
{
	//DrawLabeledInt(Text::Score, state.sim.rules.score, 20, 20, 20, WHITE);
	//DrawLabeledInt(Text::Lives, state.sim.rules.lives, 20, 45, 20, WHITE);
	DrawFPS(GetScreenWidth() - 100, 20);
}

void DrawGame(const State::World& world, const Resources& res, const Config& config)
{
	ClearBackground(BLACK);
	DrawAll2D(world, res, config);
	DrawUI(world);
}
