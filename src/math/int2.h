#pragma once

struct Int2
{
    int32_t x, y;

    bool constexpr operator==(const Int2& other) const
    {
        return x == other.x && y == other.y;
    }

    bool constexpr operator!=(const Int2& other) const
    {
        return !(*this == other);
    }

    Int2 constexpr operator+(const Int2& other) const
    {
        return Int2{ x + other.x, y + other.y };
    }

    Int2 constexpr operator-(const Int2& other) const
    {
        return Int2{ x - other.x, y - other.y };
    }

    Int2 constexpr operator*(int32_t value) const
    {
        return Int2{ x * value, y * value };
    }
};

constexpr Int2 VEC2_UP{ 0, -1 };
constexpr Int2 VEC2_DOWN{ 0, 1 };
constexpr Int2 VEC2_LEFT{ -1, 0 };
constexpr Int2 VEC2_RIGHT{ 1, 0 };

struct Int2Hash
{
    size_t operator()(const Int2& int2) const
    {
        return std::hash<int32_t>{}(int2.x) ^ std::hash<int32_t>{}(int2.y);
    }
};
