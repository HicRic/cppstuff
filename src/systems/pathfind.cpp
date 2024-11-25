#include "pch.h"
#include "pathfind.h"

#include <queue>
#include <unordered_map>
#include <unordered_set>

#include "state/state.h"

namespace
{
    bool isWalkable(State::Tile tile)
    {
        switch (tile)
        {
        case State::Tile::out_of_bounds:
            return false;
        case State::Tile::floor:
            return true;
        case State::Tile::wall:
            return false;
        case State::Tile::water:
            return true;
        }

        assert(false);
        return false;
    }

    int getCost(State::Tile tile, const State::World& world)
    {
        switch (tile)
        { 
        case State::Tile::floor:
            return world.floorMoveCost;
        case State::Tile::water:
            return world.waterMoveCost;
        case State::Tile::out_of_bounds:
        case State::Tile::wall:
            break;
        }

        assert(false);
        return 1;
    }

    void bfs(State::World& world)
    {
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
                const State::Tile nextTile = world.get(next);
                if (isWalkable(nextTile) && cameFrom.find(next) == cameFrom.cend())
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

    void dijkstras(State::World& world)
    {
        auto compare = [] (const std::pair<Int2, int>& pair1, const std::pair<Int2, int>& pair2)
        {
            return pair1.second > pair2.second;
        };
        std::priority_queue<std::pair<Int2, int>, std::vector<std::pair<Int2, int>>, decltype(compare)> frontier(compare);
        frontier.emplace(world.start, 0);

        std::unordered_map<Int2, Int2, Int2Hash> cameFrom;
        cameFrom[world.start] = Int2{};

        std::unordered_map<Int2, int, Int2Hash> costSoFar;
        costSoFar[world.start] = 0;

        bool pathFound = false;
        
        while (!frontier.empty())
        {
            const auto [currentPos, cost] = frontier.top();
            frontier.pop();

            if (currentPos == world.goal)
            {
                pathFound = true;
                break;
            }

            for (Int2 dir : INT2_DIRECTIONS)
            {
                const Int2 next = currentPos + dir;
                const State::Tile nextTile = world.get(next);
                if (isWalkable(nextTile))
                {
                    const int newCost = costSoFar[currentPos] + getCost(nextTile, world);
                    auto nextCostIter = costSoFar.find(next);
                    const bool hasCost = nextCostIter != costSoFar.cend();
                    if (!hasCost || newCost < nextCostIter->second)
                    {
                        costSoFar[next] = newCost;
                        frontier.emplace(next, newCost);
                        cameFrom[next] = currentPos;
                    }
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

    enum class SearchType
    {
        bfs,
        dijkstras,
        astar
    };
}

namespace Pathfind
{

    void update(State::World& world)
    {
        
        static SearchType searchType = SearchType::bfs;
        
        if (ImGui::TreeNode("Pathfind"))
        {
            if (ImGui::Selectable("BFS", searchType == SearchType::bfs))
            {
                searchType = SearchType::bfs;
            }
            
            if (ImGui::Selectable("Dijkstra's", searchType == SearchType::dijkstras))
            {
                searchType = SearchType::dijkstras;
            }
            
            if (ImGui::Selectable("A*", searchType == SearchType::astar))
            {
                searchType = SearchType::astar;
            }

            ImGui::TreePop();
        }

        world.path.clear();
        if (world.start == world.goal)
        {
            return;
        }

        switch (searchType)
        {
        case SearchType::bfs:
            bfs(world);
            break;
        case SearchType::dijkstras:
            dijkstras(world);
            break;
        case SearchType::astar:
            break;
        }
    }
}
