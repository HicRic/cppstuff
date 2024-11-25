#include "pch.h"
#include "state.h"

namespace
{
    size_t toIndex(Int2 pos)
    {
        return (size_t)pos.y * Config::GRID_SIZE_X + pos.x;
    }

    bool inBounds(Int2 pos)
    {
        return pos.x >= 0 && pos.y >= 0 && pos.x < Config::GRID_SIZE_X && pos.y < Config::GRID_SIZE_Y;
    }
}

namespace State
{
    Tile World::get(Int2 pos) const
    {
        if (!inBounds(pos))
        {
            return Tile::out_of_bounds;
        }
        return tiles[toIndex(pos)];
    }

    void World::set(Int2 pos, Tile tile)
    {
        if (inBounds(pos))
        {
            tiles[toIndex(pos)] = tile;
        }
    }
}

