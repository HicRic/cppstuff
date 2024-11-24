#include "pch.h"
#include "grideditor.h"

void GridEditor::update(const State::Input& input, State::World& world)
{
    using namespace State;
    
    if (input.isMouseLeftButtonDown)
    {
        const int mouseGridX = (int)(input.mousePos.x / world.gridScale);
        const int mouseGridY = (int)(input.mousePos.y / world.gridScale);

        if (mouseGridX != m_lastEditedX || mouseGridY != m_lastEditedY)
        {
            if (mouseGridX >= 0 && mouseGridY >= 0 && mouseGridX < Config::GRID_SIZE_X && mouseGridY < Config::GRID_SIZE_Y)
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
}
