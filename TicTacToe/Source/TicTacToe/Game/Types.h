#pragma once

namespace GameTypes
{
    const int8 WIN_POINTS = 4;

    enum class ePlayer
    {
        PLAYER_NONE,
        PLAYER_X,
        PLAYER_O
    };

    enum class eCheckFieldDirection
    {
        HORIZONTAL_LEFT,
        HORIZONTAL_RIGHT,
        VERTICAL_UP,
        VERTICAL_DOWN,
        DIAGONAL_UP_RIGHT,
        DIAGONAL_UP_LEFT,
        DIAGONAL_DOWN_RIGHT,
        DIAGONAL_DOWN_LEFT,
        IDLE
    };

    struct FieldPos
    {
        int32 i{ 0 };
        int32 j{ 0 };
    };
}
