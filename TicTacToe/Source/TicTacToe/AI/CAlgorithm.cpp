// Fill out your copyright notice in the Description page of Project Settings.


#include "CAlgorithm.h"
#include "Game/CGameManager.h"

int32 CAlgorithm::Minimax(const GameTypes::FieldPos& pos, int32 depth, int32 alpha, int32 beta,
                          const GameTypes::ePlayer owner, const bool isMaximizing, const int32 fieldSnapshotRadius)
{
    using GameField = std::vector<std::vector<ATicTacToeBlock*>>&;
    CGameField* gameFieldInstance = CGameField::GetInstance();
    const CGameManager* gameManagerInstance = CGameManager::GetInstance();
    GameField field = gameFieldInstance->GetGameField();

    int32 maxScore = gameManagerInstance->GetPositionScore(pos, owner);

    if (maxScore > GameTypes::MINIMUM_SCORE)
    {
        return owner == gameManagerInstance->GetAISide() ? maxScore - depth : depth - maxScore ;
    }
    else if (GameTypes::RECURSION_DEPTH == depth)
    {
        return owner == gameManagerInstance->GetAISide() ? maxScore : -maxScore;
    }
    std::vector<GameTypes::FieldPos> availableMoves; 
    isMaximizing ? StorePositionSnapshot(gameFieldInstance->GetLastPosition(GameTypes::GetOppositePlayer(gameManagerInstance->GetAISide())), availableMoves, fieldSnapshotRadius) :
    StorePositionSnapshot(gameFieldInstance->GetLastPosition(gameManagerInstance->GetAISide()), availableMoves, fieldSnapshotRadius);
    int32 bestMoveScore = isMaximizing ? INT32_MIN : INT32_MAX ;
    for (SIZE_T i = 0; i < availableMoves.size(); ++i)
    {
        GameTypes::FieldPos tempPos = availableMoves[i];
        if (field[tempPos.i][tempPos.j]->GetPlayer() == GameTypes::ePlayer::PLAYER_NONE)
        {
            GameTypes::ePlayer currentPlayer = isMaximizing ? gameManagerInstance->GetAISide() :
                                               GameTypes::GetOppositePlayer(gameManagerInstance->GetAISide());

            field[tempPos.i][tempPos.j]->SetPlayer(currentPlayer);
            int32 tempBestScore = Minimax({ tempPos.i, tempPos.j }, depth + 1, alpha, beta, currentPlayer, owner == gameManagerInstance->GetAISide(), fieldSnapshotRadius);
            field[tempPos.i][tempPos.j]->SetPlayer(GameTypes::ePlayer::PLAYER_NONE);

            if ((tempBestScore > bestMoveScore && isMaximizing) ||
                (tempBestScore <= bestMoveScore && !isMaximizing))
            {
                bestMoveScore = tempBestScore;
            }

            if (isMaximizing)
            {
                alpha = FGenericPlatformMath::Max(alpha, tempBestScore);
            }
            else
            {
                beta = FGenericPlatformMath::Min(beta, tempBestScore);
            }
            if (beta <= alpha)
            {
                break;
            }
        }
    }
    return bestMoveScore;
}

void CAlgorithm::StorePositionSnapshot(const GameTypes::FieldPos& node, 
                                       std::vector<GameTypes::FieldPos>& storeTo, const int32 radius)
{
    using GameField = std::vector<std::vector<ATicTacToeBlock*>>&;
    GameField field = CGameField::GetInstance()->GetGameField();
    storeTo.resize(field.size() * field.size());

    SIZE_T borderIDown  = static_cast<int32>((node.i - radius)) >= 0 ? node.i - radius : 0;
    SIZE_T borderIUp    = (node.i + radius) <= field.size() - 1 ? node.i + radius : field.size() - 1;
    SIZE_T borderJLeft  = static_cast<int32>((node.j - radius)) >= 0 ? node.j - radius : 0;
    SIZE_T borderJRight = (node.j + radius) <= field.size() - 1 ? node.j + radius : field.size() - 1;
    
    for (SIZE_T i = borderIDown; i <= borderIUp; ++i)
    {
        for (SIZE_T j = borderJLeft; j <= borderJRight; ++j)
        {
            storeTo.push_back({ i, j });
        }
    }
}