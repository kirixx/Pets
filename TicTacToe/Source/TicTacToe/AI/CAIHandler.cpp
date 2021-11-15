// Fill out your copyright notice in the Description page of Project Settings.


#include "CAIHandler.h"
#include <vector>
#include "CAlgorithm.h"
#include "Game/CGameField.h"
#include "Game/CGameManager.h"
#include "GenericPlatform/GenericPlatformMath.h"
#include "Math/UnrealMathUtility.h"

ATicTacToeBlock* CAIHandler::Move()
{
    auto gameManagerInstance = CGameManager::GetInstance();
    auto gameFieldInstance = CGameField::GetInstance();
    if (CGameManager::sPlayerTurn != gameManagerInstance->GetAISide())
    {
        if (mIsAIVsAi)
        {
            gameManagerInstance->SetAISide(GameTypes::GetOppositePlayer(gameManagerInstance->GetAISide()));
        }
        return nullptr;
    }
    using GameField = std::vector<std::vector<ATicTacToeBlock*>>;
    GameField field = gameFieldInstance->GetGameField();
    ATicTacToeBlock* bestMove = nullptr;
    int32 bestMoveScore = INT32_MIN;

    CAlgorithm algorithm;
    std::vector<GameTypes::FieldPos> availableMoves = 
        algorithm.GetNodeChildsInRange(
            gameFieldInstance->GetLastPosition(
                GameTypes::GetOppositePlayer(
                    gameManagerInstance->GetAISide())), GameTypes::FIELD_SNAPSHOT_RADIUS);

    for (SIZE_T i  = 0; i < availableMoves.size(); ++i)
    {
        GameTypes::FieldPos tempPos = availableMoves[i];
        if (GameTypes::ePlayer::PLAYER_NONE == field[tempPos.i][tempPos.j]->GetPlayer())
        {
            field[tempPos.i][tempPos.j]->SetPlayer(gameManagerInstance->GetAISide());
            int32 tempScore = algorithm.Minimax({ tempPos.i, tempPos.j }, 0, INT32_MIN, INT32_MAX,
                              gameManagerInstance->GetAISide(), false, GameTypes::FIELD_SNAPSHOT_RADIUS);
            field[tempPos.i][tempPos.j]->SetPlayer(GameTypes::ePlayer::PLAYER_NONE);
            if (tempScore > bestMoveScore)
            {
                bestMoveScore = tempScore;
                bestMove = field[tempPos.i][tempPos.j];
            }
        }
    }
    bestMove->SetPlayer(gameManagerInstance->GetAISide());
    if (mIsAIVsAi)
    {
        if (bestMoveScore == 1 - GameTypes::RECURSION_DEPTH)
        {
            bestMove->SetFieldPos(DoDumbMove());
        }
        gameManagerInstance->SetAISide(GameTypes::GetOppositePlayer(gameManagerInstance->GetAISide()));
    }
    return  bestMove;
}

GameTypes::FieldPos CAIHandler::DoDumbMove()
{
    SIZE_T i = 0;
    SIZE_T j = 0;

    i = FMath::RandRange(0, CGameField::GetInstance()->GetGameField().size() - 1);
    j = FMath::RandRange(0, CGameField::GetInstance()->GetGameField().size() - 1);

    return { i, j };
}