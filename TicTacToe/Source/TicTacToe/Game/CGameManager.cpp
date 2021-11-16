
#include "CGameManager.h"
#include "CGameField.h"
#include "UI/CInGameHUD.h"
#include "Renderer/CMaterialManager.h"
#include "Engine/World.h"

GameTypes::ePlayer CGameManager::sPlayerTurn  = GameTypes::ePlayer::PLAYER_X;
int32  CGameManager::sCurrentScore            = 0;
int32  CGameManager::sCurrentScoreForOpponent = 0;
int32  CGameManager::sMaxScoreGlobal          = 0;

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

void CGameManager::OnMoveMade(ATicTacToeBlock* block)
{
    if (!block)
    {
        return;
    }
    // Change material
    if (GameTypes::ePlayer::PLAYER_X == sPlayerTurn)
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

int32 CGameManager::GetPositionScore(const GameTypes::FieldPos& fieldPosition, const GameTypes::ePlayer owner) const
{
    sMaxScoreGlobal = 0;
    sCurrentScore = 0;
    sCurrentScoreForOpponent = 0;
    GetScoreByDirections(fieldPosition, owner);
    return sMaxScoreGlobal;
}

void CGameManager::GetScoreByDirections(const GameTypes::FieldPos& fieldPosition, const GameTypes::ePlayer owner,
                                        const GameTypes::eCheckFieldDirection checkDirection) const
{
    using GameField = std::vector<std::vector<ATicTacToeBlock*>>&;
    GameField field = CGameField::GetInstance()->GetGameField();

    if ((fieldPosition.i < 0 || fieldPosition.j < 0) ||
        (field.size() <= fieldPosition.i || field[fieldPosition.i].size() <= fieldPosition.j))
    {
        return;
    }
    if (sCurrentScoreForOpponent == 3 || sCurrentScore == 4)
    {
        return;
    }

    if (field[fieldPosition.i][fieldPosition.j]->GetPlayer() == GameTypes::GetOppositePlayer(owner))
    {
        if (sCurrentScore > 1)
            return;
        sCurrentScoreForOpponent++;
    }
    else if (field[fieldPosition.i][fieldPosition.j]->GetPlayer() == owner)
    {
        if (sCurrentScoreForOpponent > 0)
            return;
        ++sCurrentScore;
    }
    else
    {
        return;
    }
    switch (checkDirection)
    {
    case GameTypes::eCheckFieldDirection::IDLE:
        sCurrentScore = 1;
        sCurrentScoreForOpponent = 0;
        GetScoreByDirections({ fieldPosition.i, fieldPosition.j + 1 }, owner, GameTypes::eCheckFieldDirection::HORIZONTAL_RIGHT);
        GetScoreByDirections({ fieldPosition.i, fieldPosition.j - 1 }, owner, GameTypes::eCheckFieldDirection::HORIZONTAL_LEFT);
        if (IsMaxGlobalCounted()) break;
        sCurrentScore = 1;
        sCurrentScoreForOpponent = 0;
        GetScoreByDirections({ fieldPosition.i + 1, fieldPosition.j }, owner, GameTypes::eCheckFieldDirection::VERTICAL_UP);
        GetScoreByDirections({ fieldPosition.i - 1, fieldPosition.j }, owner, GameTypes::eCheckFieldDirection::VERTICAL_DOWN);
        if (IsMaxGlobalCounted()) break;
        sCurrentScore = 1;
        sCurrentScoreForOpponent = 0;
        GetScoreByDirections({ fieldPosition.i + 1, fieldPosition.j + 1 }, owner, GameTypes::eCheckFieldDirection::DIAGONAL_UP_RIGHT);
        GetScoreByDirections({ fieldPosition.i - 1, fieldPosition.j - 1 }, owner, GameTypes::eCheckFieldDirection::DIAGONAL_DOWN_LEFT);
        if (IsMaxGlobalCounted()) break;
        sCurrentScore = 1;
        sCurrentScoreForOpponent = 0;
        GetScoreByDirections({ fieldPosition.i - 1, fieldPosition.j + 1 }, owner, GameTypes::eCheckFieldDirection::DIAGONAL_UP_LEFT);
        GetScoreByDirections({ fieldPosition.i + 1, fieldPosition.j - 1 }, owner, GameTypes::eCheckFieldDirection::DIAGONAL_DOWN_RIGHT);
        break;
    case GameTypes::eCheckFieldDirection::HORIZONTAL_RIGHT:
        GetScoreByDirections({ fieldPosition.i, fieldPosition.j + 1 }, owner, checkDirection);
        break;
    case GameTypes::eCheckFieldDirection::HORIZONTAL_LEFT:
        GetScoreByDirections({ fieldPosition.i, fieldPosition.j - 1 }, owner, checkDirection);
        break;
    case GameTypes::eCheckFieldDirection::VERTICAL_UP:
        GetScoreByDirections({ fieldPosition.i + 1, fieldPosition.j }, owner, checkDirection);
        break;
    case GameTypes::eCheckFieldDirection::VERTICAL_DOWN:
        GetScoreByDirections({ fieldPosition.i - 1, fieldPosition.j }, owner, checkDirection);
        break;
    case GameTypes::eCheckFieldDirection::DIAGONAL_UP_RIGHT:
        GetScoreByDirections({ fieldPosition.i + 1, fieldPosition.j + 1 }, owner, checkDirection);
        break;
    case GameTypes::eCheckFieldDirection::DIAGONAL_UP_LEFT:
        GetScoreByDirections({ fieldPosition.i - 1, fieldPosition.j + 1 }, owner, checkDirection);
        break;
    case GameTypes::eCheckFieldDirection::DIAGONAL_DOWN_RIGHT:
        GetScoreByDirections({ fieldPosition.i + 1, fieldPosition.j - 1 }, owner, checkDirection);
        break;
    case GameTypes::eCheckFieldDirection::DIAGONAL_DOWN_LEFT:
        GetScoreByDirections({ fieldPosition.i - 1, fieldPosition.j - 1 }, owner, checkDirection);
        break;
    default:
        break;
    }
    sMaxScoreGlobal = FGenericPlatformMath::Max(FGenericPlatformMath::Max(sCurrentScore, sCurrentScoreForOpponent + 1), sMaxScoreGlobal);
}

bool CGameManager::IsMaxGlobalCounted() const
{
    bool retVal = false;
    if (sCurrentScoreForOpponent == GameTypes::WIN_POINTS - 1 || sCurrentScore == GameTypes::WIN_POINTS)
    {
        sMaxScoreGlobal = GameTypes::WIN_POINTS;
        retVal = true;
    }
    return retVal;
}

bool CGameManager::CheckForWin(const GameTypes::FieldPos& fieldPosition, const GameTypes::ePlayer owner)
{
    GetPositionScore(fieldPosition, owner);
    return GameTypes::WIN_POINTS <= sCurrentScore;
}

void CGameManager::SetGameMode(const GameTypes::GameMode gameMode)
{
    CGameField* gamefieldInstance = CGameField::GetInstance();
    ACInGameHUD* InGameHUD = Cast<ACInGameHUD>(gamefieldInstance->GetGameField()[0][0]->GetWorld()->GetFirstPlayerController()->GetHUD());
    if (GameTypes::GameMode::PLAYER_VS_AI == gameMode)
    {
        InGameHUD->SetPlayersSide(mPlayerSide);
        InGameHUD->SetAISide(mAISide);
    }
    else
    {
        InGameHUD->SetPlayersSide(GameTypes::ePlayer::PLAYER_NONE);
        InGameHUD->SetAISide(GameTypes::ePlayer::PLAYER_NONE);
    }
    mGameMode = gameMode; 
}