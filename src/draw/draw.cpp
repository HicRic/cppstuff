#include "pch.h"
#include "draw.h"

#include "resources/resources.h"
#include "config/config.h"
#include "text.h"
#include "state/State.h"

namespace
{
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

	void DrawGrid(const State::World& world)
	{
		const float gridWidth = world.gridScale * (float)Config::GRID_SIZE_X;
		const float gridHeight = world.gridScale * (float)Config::GRID_SIZE_Y;
		
		for (int gridY = 0; gridY <= Config::GRID_SIZE_Y; ++gridY)
		{
			const float y = (float)gridY * world.gridScale;
			
			DrawLineEx({0, y}, {gridWidth, y}, world.gridLineThickness, world.gridLineColor);
			
			for (int gridX = 0; gridX <= Config::GRID_SIZE_X; ++gridX)
			{
				const float x = (float)gridX * world.gridScale;
				DrawLineEx({x, 0}, {x, gridHeight}, world.gridLineThickness, world.gridLineColor);
			}
		}
	}

	void DrawTiles(const State::World& world)
	{
		const float offset = world.gridLineThickness;
		const float squareSize = world.gridScale - world.gridLineThickness * 2.0f;
		
		for (int gridY = 0; gridY < Config::GRID_SIZE_Y; ++gridY)
		{
			const float y = (float)gridY * world.gridScale + offset;
			
			for (int gridX = 0; gridX < Config::GRID_SIZE_X; ++gridX)
			{
				const float x = (float)gridX * world.gridScale + offset;
				if (world.get(gridX, gridY) == State::Tile::wall)
				{
					DrawRectangleRounded({x, y, squareSize, squareSize}, 0.5f, 10, WHITE);
				}
			}
		}
	}

	void DrawAll2D(const State::World& world, const Resources& /*res*/)
	{
		BeginMode2D(world.cam);

		DrawGrid(world);
		DrawTiles(world);
	
		//DrawTextureCentered(res.alien1, config.testpos, 0, 1, RED);

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
}

void DrawGame(const State::World& world, const Resources& res)
{
	ClearBackground(BLACK);
	DrawAll2D(world, res);
	DrawUI(world);
}
