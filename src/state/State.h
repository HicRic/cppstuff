#pragma once
#include "config/config.h"
#include "math/int2.h"

namespace State
{
    struct Input
    {
        double time = 0.0;
        float deltaTime = 0.0f;
        
        float horizontalMovement = 0.0f;
        float verticalMovement = 0.0f;
        
        Vector2 mousePos {};
        bool isWallToggleInputActive = false;
        bool isWaterToggleInputActive = false;
        bool isStartPlacementInputActive = false;
        bool isGoalPlacementInputActive = false;
    };

    enum class Tile : char
    {
        out_of_bounds = -1,
        floor = 0,
        wall = 1,
        water = 2,
    };

    struct World
    {
        float gridLineThickness = 1.0f;
        Color gridLineColor = GRAY;
        float gridScale = 32.0f;

        int floorMoveCost = 1;
        int waterMoveCost = 3;
        
        Camera2D cam {};

        Tile get(Int2 pos) const;
        void set(Int2 pos, Tile tile);
        std::array<Tile, (size_t)Config::GRID_SIZE_X * Config::GRID_SIZE_Y> tiles {};

        Int2 start {};
        Int2 goal {};
        
        std::vector<Int2> path;
    };
}
