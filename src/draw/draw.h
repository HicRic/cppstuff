#pragma once

struct Resources;
namespace State { struct World; }

namespace Draw
{
    void drawGame(const State::World& world, const Resources& res);
}
