#include "pch.h"
#include "draw.h"

#include "resources/resources.h"
#include "config/config.h"
#include "text.h"
#include "state/state.h"

namespace
{
	Vector2 gridToWorld(int x, int y, float gridScale)
	{
		const Vector2 result { (float)x * gridScale + gridScale/2.0f, (float)y * gridScale + gridScale/2.0f};
		return result;
	}
	
	void drawTextureCentered(const Texture2D& texture, Vector2 position, float rotation, float scale, Color color)
	{
		const float width = (float)texture.width * scale;
		const float height = (float)texture.height * scale;

		const Vector2 offset = { width / 2.f, height / 2.f };
		const Rectangle sourceRect { 0, 0, (float)texture.width, (float)texture.height };
		const Rectangle destRect { position.x, position.y, width, height };
		
		DrawTexturePro(texture, sourceRect, destRect, offset, rotation, color);
	}

	void drawGrid(const State::World& world)
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

	void drawTiles(const State::World& world)
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
					DrawRectangleRounded({x, y, squareSize, squareSize}, 0.5f, 10, GRAY);
				}
			}
		}
	}

	void drawAll2D(const State::World& world, const Resources& res)
	{
		BeginMode2D(world.cam);

		drawGrid(world);
		drawTiles(world);

		const Vector2 startPos = gridToWorld(world.startX, world.startY, world.gridScale);
		drawTextureCentered(res.cannon, startPos, 0.0f, 0.75f, DARKBLUE);

		const Vector2 goalPos = gridToWorld(world.goalX, world.goalY, world.gridScale);
		drawTextureCentered(res.alien1, goalPos, 0.0f, 1.0f, RED);

		EndMode2D();
	}

	void drawLabeledInt(const char* label, int value, int xPos, int yPos, int fontSize, Color color)
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

	void drawUI(const State::World& /*world*/)
	{
		//DrawLabeledInt(Text::Score, state.sim.rules.score, 20, 20, 20, WHITE);
		//DrawLabeledInt(Text::Lives, state.sim.rules.lives, 20, 45, 20, WHITE);
		DrawFPS(GetScreenWidth() - 100, 20);
	}
}

namespace Draw
{
	void drawGame(const State::World& world, const Resources& res)
	{
		ClearBackground(BLACK);
		drawAll2D(world, res);
		drawUI(world);
	}
}
