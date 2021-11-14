
#include "CGameManager.h"
#include "CGameField.h"
#include "UI/CInGameHUD.h"
#include "Renderer/CMaterialManager.h"

GameTypes::ePlayer CGameManager::sPlayerTurn = GameTypes::ePlayer::PLAYER_X;

namespace GameManagerHelpers
{
    void ChangeTurn()
    {
        if (CGameManager::sPlayerTurn == GameTypes::ePlayer::PLAYER_X)
        {
            CGameManager::sPlayerTurn = GameTypes::ePlayer::PLAYER_O;
        }
        else if (CGameManager::sPlayerTurn == GameTypes::ePlayer::PLAYER_O)
        {
            CGameManager::sPlayerTurn = GameTypes::ePlayer::PLAYER_X;
        }
    }
}

void CGameManager::MadeAMove(ATicTacToeBlock* block)
{
    using GameField = std::vector<std::vector<ATicTacToeBlock*>>;
    GameField field = CGameField::GetInstance()->GetGameField();
    if (!block)
    {
        return;
    }
    // Change material
    if (sPlayerTurn == GameTypes::ePlayer::PLAYER_X)
    {
        block->GetBlockMesh()->SetMaterial(0, CMaterialManager::GetInstance().TTT_Cross_Texture);
    }
    else
    {
        block->GetBlockMesh()->SetMaterial(0, CMaterialManager::GetInstance().TTT_O_Texture);
    }
    CGameField::GetInstance()->StoreLastMovePos(block->GetGameFieldPos(), sPlayerTurn);
    ACInGameHUD* InGameHUD = Cast<ACInGameHUD>(block->GetWorld()->GetFirstPlayerController()->GetHUD());
    if (InGameHUD)
    {
        if (CheckForWin(block->GetGameFieldPos(), CGameManager::GetPlayerTurn()))
        {
            InGameHUD->UpdateWinner(CGameManager::GetPlayerTurn());
            sPlayerTurn = GameTypes::ePlayer::PLAYER_X;
            return;
        }
        GameManagerHelpers::ChangeTurn();
        InGameHUD->ChangeTurn(CGameManager::GetPlayerTurn());
    }
}

int32 CGameManager::GetPositionScore(const GameTypes::FieldPos& fieldPosition, const GameTypes::ePlayer owner)
{
    int8 maxScore = 0;
    GetScoreByDirections(fieldPosition, owner, maxScore);
    return maxScore;
}

void CGameManager::GetScoreByDirections(const GameTypes::FieldPos& fieldPosition, const GameTypes::ePlayer owner, int8& maxScore,
                                        const GameTypes::eCheckFieldDirection checkDirection)
{
    static int8 currentScore = 0;
    using GameField = std::vector<std::vector<ATicTacToeBlock*>>;
    GameField field = CGameField::GetInstance()->GetGameField();

    if ((fieldPosition.i < 0 || fieldPosition.j < 0) ||
        (field.size() <= fieldPosition.i || field[fieldPosition.i].size() <= fieldPosition.j))
    {
        return;
    }
    if (field[fieldPosition.i][fieldPosition.j]->GetPlayer() != owner)
    {
        return;
    }
    ++currentScore;
    switch (checkDirection)
    {
    case GameTypes::eCheckFieldDirection::IDLE:
        currentScore = 1;
        GetScoreByDirections({ fieldPosition.i, fieldPosition.j + 1 }, owner, maxScore, GameTypes::eCheckFieldDirection::HORIZONTAL_RIGHT);
        GetScoreByDirections({ fieldPosition.i, fieldPosition.j - 1 }, owner, maxScore, GameTypes::eCheckFieldDirection::HORIZONTAL_LEFT);
        currentScore = 1;
        GetScoreByDirections({ fieldPosition.i + 1, fieldPosition.j }, owner, maxScore, GameTypes::eCheckFieldDirection::VERTICAL_UP);
        GetScoreByDirections({ fieldPosition.i - 1, fieldPosition.j }, owner, maxScore, GameTypes::eCheckFieldDirection::VERTICAL_DOWN);
        currentScore = 1;
        GetScoreByDirections({ fieldPosition.i + 1, fieldPosition.j + 1 }, owner, maxScore, GameTypes::eCheckFieldDirection::DIAGONAL_UP_RIGHT);
        GetScoreByDirections({ fieldPosition.i - 1, fieldPosition.j - 1 }, owner, maxScore, GameTypes::eCheckFieldDirection::DIAGONAL_DOWN_LEFT);
        currentScore = 1;
        GetScoreByDirections({ fieldPosition.i - 1, fieldPosition.j + 1 }, owner, maxScore, GameTypes::eCheckFieldDirection::DIAGONAL_UP_LEFT);
        GetScoreByDirections({ fieldPosition.i + 1, fieldPosition.j - 1 }, owner, maxScore, GameTypes::eCheckFieldDirection::DIAGONAL_DOWN_RIGHT);
        currentScore = 1;
        break;
    case GameTypes::eCheckFieldDirection::HORIZONTAL_RIGHT:
        GetScoreByDirections({ fieldPosition.i, fieldPosition.j + 1 }, owner, maxScore, checkDirection);
        break;
    case GameTypes::eCheckFieldDirection::HORIZONTAL_LEFT:
        GetScoreByDirections({ fieldPosition.i, fieldPosition.j - 1 }, owner, maxScore, checkDirection);
        break;
    case GameTypes::eCheckFieldDirection::VERTICAL_UP:
        GetScoreByDirections({ fieldPosition.i + 1, fieldPosition.j }, owner, maxScore, checkDirection);
        break;
    case GameTypes::eCheckFieldDirection::VERTICAL_DOWN:
        GetScoreByDirections({ fieldPosition.i - 1, fieldPosition.j }, owner, maxScore, checkDirection);
        break;
    case GameTypes::eCheckFieldDirection::DIAGONAL_UP_RIGHT:
        GetScoreByDirections({ fieldPosition.i + 1, fieldPosition.j + 1 }, owner, maxScore, checkDirection);
        break;
    case GameTypes::eCheckFieldDirection::DIAGONAL_UP_LEFT:
        GetScoreByDirections({ fieldPosition.i - 1, fieldPosition.j + 1 }, owner, maxScore, checkDirection);
        break;
    case GameTypes::eCheckFieldDirection::DIAGONAL_DOWN_RIGHT:
        GetScoreByDirections({ fieldPosition.i + 1, fieldPosition.j - 1 }, owner, maxScore, checkDirection);
        break;
    case GameTypes::eCheckFieldDirection::DIAGONAL_DOWN_LEFT:
        GetScoreByDirections({ fieldPosition.i - 1, fieldPosition.j - 1 }, owner, maxScore, checkDirection);
        break;
    default:
        break;
    }
    maxScore = FGenericPlatformMath::Max(currentScore, maxScore);
    currentScore = 0;
}

bool CGameManager::CheckForWin(const GameTypes::FieldPos& fieldPosition, const GameTypes::ePlayer owner)
{
    return GetPositionScore(fieldPosition, owner) >= GameTypes::WIN_POINTS;
}
