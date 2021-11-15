// Fill out your copyright notice in the Description page of Project Settings.


#include "CAIHandler.h"
#include <vector>
#include "CAlgorithm.h"
#include "Game/CGameField.h"
#include "Game/CGameManager.h"
#include "GenericPlatform/GenericPlatformMath.h"
#include "Math/UnrealMathUtility.h"

GameTypes::ePlayer sSide = GameTypes::ePlayer::PLAYER_NONE;

CAIHandler::CAIHandler()
    : mSide(GameTypes::ePlayer::PLAYER_NONE)
{
}

CAIHandler::~CAIHandler()
{
}

ATicTacToeBlock* CAIHandler::Move()
{
    if (CGameManager::sPlayerTurn != mSide)
    {
        return nullptr;
    }
    using GameField = std::vector<std::vector<ATicTacToeBlock*>>;
    GameField field = CGameField::GetInstance()->GetGameField();
    ATicTacToeBlock* bestMove = nullptr;
    int32 bestMoveScore = INT32_MIN;

    CAlgorithm algorithm;
    std::vector<GameTypes::FieldPos> availableMoves = algorithm.GetNodeChildsInRange(CGameField::GetInstance()->GetLastPosition(GameTypes::GetOppositePlayer(mSide)), GameTypes::FIELD_SNAPSHOT_RADIUS);

    for (SIZE_T i  = 0; i < availableMoves.size(); ++i)
    {
        GameTypes::FieldPos tempPos = availableMoves[i];
        if (GameTypes::ePlayer::PLAYER_NONE == field[tempPos.i][tempPos.j]->GetPlayer())
        {
            field[tempPos.i][tempPos.j]->SetPlayer(mSide);
            int32 tempScore = algorithm.Minimax({ tempPos.i, tempPos.j }, 0, INT32_MIN, INT32_MAX,
                                                mSide, false, GameTypes::FIELD_SNAPSHOT_RADIUS);
            field[tempPos.i][tempPos.j]->SetPlayer(GameTypes::ePlayer::PLAYER_NONE);
            if (tempScore > bestMoveScore)
            {
                bestMoveScore = tempScore;
                bestMove = field[tempPos.i][tempPos.j];
            }
        }
    }
    bestMove->SetPlayer(mSide);
    return  bestMove;
}
