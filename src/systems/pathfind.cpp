#include "pch.h"
#include "pathfind.h"

#include <queue>
#include <unordered_map>
#include <unordered_set>

#include "state/state.h"

namespace Pathfind
{
    bool isFloor(Int2 pos, const State::World& world)
    {
        const bool inBounds = pos.x >= 0 && pos.y >= 0 && pos.x < Config::GRID_SIZE_X && pos.y < Config::GRID_SIZE_Y;
        if (!inBounds)
        {
            return false;
        }

        return world.get(pos.x, pos.y) == State::Tile::floor;
    }

    void update(State::World& world)
    {
        world.path.clear();

        if (world.start == world.goal)
        {
            return;
        }
        
        std::queue<Int2> frontier;
        frontier.push(world.start);

        std::unordered_map<Int2, Int2, Int2Hash> cameFrom;
        cameFrom[world.start] = Int2{};

        bool pathFound = false;
        
        while (!frontier.empty())
        {
            const Int2 current = frontier.front();
            frontier.pop();

            if (current == world.goal)
            {
                pathFound = true;
                break;
            }

            for (Int2 dir : INT2_DIRECTIONS)
            {
                const Int2 next = current + dir;
                if (isFloor(next, world) && cameFrom.find(next) == cameFrom.cend())
                {
                    frontier.push(next);
                    cameFrom[next] = current;
                }
            }
        }

        if (pathFound)
        {
            Int2 current = world.goal;
            while (current != world.start)
            {
                world.path.push_back(current);
                current = cameFrom[current];
            }
        }
    }
}
