#pragma once
#include "config/config.h"

namespace State
{
    struct Input
    {
        double time = 0.0;
        float deltaTime = 0.0f;
        
        float horizontalMovement = 0.0f;
        float verticalMovement = 0.0f;
        
        Vector2 mousePos {};
        bool isMouseLeftButtonDown = false;
    };

    enum class Tile : char
    {
        wall = 0,
        floor = 1
    };

    struct World
    {
        float gridLineThickness = 1.0f;
        Color gridLineColor = GRAY;
        float gridScale = 32.0f;
        
        Camera2D cam {};

        Tile get(int x, int y) const;
        void set(int x, int y, Tile tile);
        std::array<Tile, (size_t)Config::GRID_SIZE_X * Config::GRID_SIZE_Y> tiles {};
    };
}
