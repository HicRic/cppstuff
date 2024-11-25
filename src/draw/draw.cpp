#include "pch.h"
#include "draw.h"

#include "resources/resources.h"
#include "config/config.h"
#include "text.h"
#include "state/state.h"

namespace
{
	Vector2 gridToWorld(Int2 pos, float gridScale)
	{
		const Vector2 result { (float)pos.x * gridScale + gridScale/2.0f, (float)pos.y * gridScale + gridScale/2.0f};
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
				
				switch (world.get({gridX,gridY}))
				{
					case State::Tile::floor:
						break;
					case State::Tile::wall:
						DrawRectangleRounded({x, y, squareSize, squareSize}, 0.5f, 10, GRAY);
						break;
					case State::Tile::water:
						DrawRectangleRounded({x, y, squareSize, squareSize}, 0.5f, 10, BLUE);
						break;
					case State::Tile::out_of_bounds:
						break;
				}
			}
		}
	}

	void drawPath(const State::World& world)
	{
		for (const Int2 step : world.path)
		{
			const Vector2 pos = gridToWorld(step, world.gridScale);
			DrawCircleV(pos, world.gridScale/2.0f, GREEN);
		}
	}

	void drawAll2D(const State::World& world, const Resources& res)
	{
		BeginMode2D(world.cam);

		drawGrid(world);
		drawTiles(world);
		drawPath(world);

		const Vector2 startPos = gridToWorld(world.start, world.gridScale);
		drawTextureCentered(res.cannon, startPos, 0.0f, 0.75f, DARKBLUE);

		const Vector2 goalPos = gridToWorld(world.goal, world.gridScale);
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
		drawLabeledInt(Text::FRAME_TIME_MICROSECONDS, (int)(GetFrameTime()*1'000'000.0f), 20, 40, 20, GREEN);
		DrawFPS(20, 20);
		
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
