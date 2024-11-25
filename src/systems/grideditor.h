#pragma once
#include "state/state.h"

class GridEditor
{
public:
    void update(const State::Input& input, State::World& world);

private:
    int m_lastEditedX = -1;
    int m_lastEditedY = -1;
};
