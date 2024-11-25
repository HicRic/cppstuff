#include "pch.h"
#include "grideditor.h"

void GridEditor::update(const State::Input& input, State::World& world)
{
    using namespace State;
    
    const int mouseGridX = (int)(input.mousePos.x / world.gridScale);
    const int mouseGridY = (int)(input.mousePos.y / world.gridScale);
    const bool isMouseInGridBounds = mouseGridX >= 0 && mouseGridY >= 0 && mouseGridX < Config::GRID_SIZE_X && mouseGridY < Config::GRID_SIZE_Y;
    
    if (input.isTileToggleInputActive)
    {
        if (mouseGridX != m_lastEditedX || mouseGridY != m_lastEditedY)
        {
            if (isMouseInGridBounds)
            {
                const Tile current = world.get(mouseGridX, mouseGridY);
                world.set(mouseGridX, mouseGridY, current == Tile::wall ? Tile::floor : Tile::wall);
            }
            
            m_lastEditedX = mouseGridX;
            m_lastEditedY = mouseGridY;
        }
    }
    else
    {
        m_lastEditedX = -1;
        m_lastEditedY = -1;
    }

    if (input.isStartPlacementInputActive && isMouseInGridBounds)
    {
        world.start.x = mouseGridX;
        world.start.y = mouseGridY;
    }

    if (input.isGoalPlacementInputActive && isMouseInGridBounds)
    {
        world.goal.x = mouseGridX;
        world.goal.y = mouseGridY;
    }
}
