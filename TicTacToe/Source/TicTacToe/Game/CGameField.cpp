// Fill out your copyright notice in the Description page of Project Settings.


#include "CGameField.h"

Field& CGameField::GetGameField() 
{ 
    return mField; 
}

void CGameField::StoreLastMovePos(const GameTypes::FieldPos& pos, const GameTypes::ePlayer owner)
{
    owner == GameTypes::ePlayer::PLAYER_X ? mLastPosX = pos : mLastPosO = pos;
}

const GameTypes::FieldPos& CGameField::GetLastPosition(const GameTypes::ePlayer owner) const
{
    return owner == GameTypes::ePlayer::PLAYER_X ? mLastPosX : mLastPosO;
}