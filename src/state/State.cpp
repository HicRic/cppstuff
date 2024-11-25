#include "pch.h"
#include "state.h"

namespace
{
    size_t toIndex(int x, int y)
    {
        return (size_t)y * Config::GRID_SIZE_X + x;
    }
}

State::Tile State::World::get(int x, int y) const
{
    return tiles[toIndex(x, y)];
}

void State::World::set(int x, int y, Tile tile)
{
    tiles[toIndex(x, y)] = tile;
}
