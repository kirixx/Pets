// Fill out your copyright notice in the Description page of Project Settings.


#include "CGameField.h"

Field& CGameField::GetGameField() 
{ 
    return mField; 
}

std::vector<GameTypes::FieldPos> CGameField::GetAvailableMoves()
{
    std::vector<GameTypes::FieldPos> availableMoves;
    availableMoves.reserve(GameTypes::GAME_FIELD_SIZE);
    for (SIZE_T i = 0; i < mField.size(); ++i)
    {
        for (SIZE_T j = 0; j < mField[i].size(); ++j)
        {
            if (mField[i][j]->GetPlayer() == GameTypes::ePlayer::PLAYER_NONE)
            {
                availableMoves.push_back({ i, j });
            }
        }
    }

    return availableMoves;
}

void CGameField::StoreLastMovePos(const GameTypes::FieldPos& pos, const GameTypes::ePlayer owner)
{
    owner == GameTypes::ePlayer::PLAYER_X ? mLastPosX = pos : mLastPosO = pos;
}

const GameTypes::FieldPos& CGameField::GetLastPosition(const GameTypes::ePlayer owner) const
{
    return owner == GameTypes::ePlayer::PLAYER_X ? mLastPosX : mLastPosO;
}