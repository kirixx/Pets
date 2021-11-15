#pragma once

namespace GameTypes
{
    const int8   WIN_POINTS            = 4;
    const uint8  RECURSION_DEPTH       = 3;
    const uint8  FIELD_SNAPSHOT_RADIUS = 4;
    const SIZE_T GAME_FIELD_SIZE       = 8 * 8;

    enum class ePlayer
    {
        PLAYER_NONE = 1,
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

    enum class GameMode
    {
        HOTSEAT,
        PLAYER_VS_AI,
        AI_VS_AI
    };


    struct FieldPos
    {
        SIZE_T i{ 0 };
        SIZE_T j{ 0 };
    };

    static ePlayer GetRandomPlayer()
    {
        int8 randVal = FMath::RandRange(static_cast<int8>(ePlayer::PLAYER_X), static_cast<int8>(ePlayer::PLAYER_O));
        return static_cast<ePlayer>(randVal);
    }

    //Get second player
    static constexpr GameTypes::ePlayer GetOppositePlayer(const GameTypes::ePlayer player)
    {
        return player == GameTypes::ePlayer::PLAYER_X ? GameTypes::ePlayer::PLAYER_O : GameTypes::ePlayer::PLAYER_X;
    }
}
