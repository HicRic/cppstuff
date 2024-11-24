#pragma once

namespace State
{
    struct Input
    {
        double time = 0.0;
        float deltaTime = 0.0f;
        
        float horizontalMovement = 0.0f;
        float verticalMovement = 0.0f;
    };

    struct World
    {
        Camera2D cam {};
    };
}