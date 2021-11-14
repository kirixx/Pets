// Fill out your copyright notice in the Description page of Project Settings.


#include "CAlgorithm.h"
#include "Game/CGameManager.h"

int32 CAlgorithm::Minimax(const GameTypes::FieldPos& pos, int32 depth, int32 alpha, int32 beta, 
                          const GameTypes::ePlayer owner, const bool isMaximizing, const int32 fieldSnapshotRadius)
{
    auto gameFieldInstance = CGameField::GetInstance();
    using GameField = std::vector<std::vector<ATicTacToeBlock*>>;
    GameField field = gameFieldInstance->GetGameField();
    const int32 WIN_LOSE_SCORE = 8;
    auto gameManagerInstance = CGameManager::GetInstance();

    if (gameManagerInstance->CheckForWin(pos, owner))
    {
        return owner == gameManagerInstance->GetAISide() ? WIN_LOSE_SCORE - depth : depth - WIN_LOSE_SCORE;
    }
    else if (depth == 0)
    {
        return owner == gameManagerInstance->GetAISide() ? gameManagerInstance->GetPositionScore(pos, owner) : 
                                                          -gameManagerInstance->GetPositionScore(pos, owner);
    }
    std::vector<GameTypes::FieldPos> availableMoves = isMaximizing ? 
    GetNodeChildsInRange(gameFieldInstance->GetLastPosition(GameTypes::GetOppositePlayer(gameManagerInstance->GetAISide())), fieldSnapshotRadius) :
    GetNodeChildsInRange(gameFieldInstance->GetLastPosition(gameManagerInstance->GetAISide()), fieldSnapshotRadius);
    int32 bestMoveScore = isMaximizing ? INT32_MIN : INT32_MAX;
    for (SIZE_T i = 0; i < availableMoves.size(); ++i)
    {
        GameTypes::FieldPos tempPos = availableMoves[i];
        if (field[tempPos.i][tempPos.j]->GetPlayer() == GameTypes::ePlayer::PLAYER_NONE)
        {
            GameTypes::ePlayer currentPlayer = isMaximizing ? gameManagerInstance->GetAISide() : 
                                 GameTypes::GetOppositePlayer(gameManagerInstance->GetAISide());
            field[tempPos.i][tempPos.j]->SetPlayer(currentPlayer);
            int32 tempBestScore = Minimax({ tempPos.i, tempPos.j }, depth - 1, alpha, beta, currentPlayer, !isMaximizing, fieldSnapshotRadius);
            field[tempPos.i][tempPos.j]->SetPlayer(GameTypes::ePlayer::PLAYER_NONE);

            if (isMaximizing)
            {
                bestMoveScore = FGenericPlatformMath::Max(tempBestScore, bestMoveScore);
                alpha = FGenericPlatformMath::Max(alpha, tempBestScore);
                if (beta <= alpha)
                {
                    return alpha;
                }
            }
            else
            {
                bestMoveScore = FGenericPlatformMath::Min(tempBestScore, bestMoveScore);
                beta = FGenericPlatformMath::Min(beta, tempBestScore);
                if (beta <= alpha)
                {
                    return beta;
                }
            }
        }
    }
    return bestMoveScore;
}

std::vector<GameTypes::FieldPos> CAlgorithm::GetNodeChildsInRange(const GameTypes::FieldPos& node, const int32 radius)
{
    using GameField = std::vector<std::vector<ATicTacToeBlock*>>;
    GameField field = CGameField::GetInstance()->GetGameField();
    std::vector<GameTypes::FieldPos> retVal;
    retVal.reserve(field.size() * field.size());

    SIZE_T borderIDown    = static_cast<int32>((node.i - radius)) >= 0 ? node.i - radius : 0;
    SIZE_T borderIUp  = (node.i + radius) <= field.size() - 1 ? node.i + radius : field.size() - 1;
    SIZE_T borderJLeft  = static_cast<int32>((node.j - radius)) >= 0 ? node.j - radius : 0;
    SIZE_T borderJRight = (node.j + radius) <= field.size() - 1 ? node.j + radius : field.size() - 1;
    
    for (SIZE_T i = borderIDown; i <= borderIUp; ++i)
    {
        for (SIZE_T j = borderJLeft; j <= borderJRight; ++j)
        {
            retVal.push_back({ i, j });
        }
    }

    return retVal;
}