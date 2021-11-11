// Fill out your copyright notice in the Description page of Project Settings.


#include "AIHandler.h"
#include <vector>
#include "Game/CGameField.h"
#include "Game/CGameManager.h"

AIHandler::AIHandler()
    : mSide(GameTypes::ePlayer::PLAYER_NONE)
{
}

AIHandler::~AIHandler()
{
}

ATicTacToeBlock* AIHandler::Move()
{
    if (CGameManager::sPlayerTurn != mSide)
    {
        return nullptr;
    }
    using GameField = std::vector<std::vector<ATicTacToeBlock*>>;
    GameField field = CGameField::GetInstance().GetGameField();

    for (SIZE_T i  = 0; i < field.size(); ++i)
    {
        for (SIZE_T j = 0; j < field[i].size(); ++j)
        {
            if (field[i][j]->GetPlayer() != mSide)
            {
                field[i][j]->SetPlayer(mSide);
                return field[i][j];
            }
        }
    }

    return nullptr;
}

int32 AIHandler::FindBestMove()
{
    return 0;
}