#pragma once

struct Resources;
struct Config;
namespace State { struct World; }

void DrawGame(const State::World& world, const Resources& res, const Config& config);
