
#include "CGameManager.h"
#include "CGameField.h"
#include "../UI/CInGameHUD.h"
#include "../Renderer/CMaterialManager.h"

GameTypes::Player CGameManager::PLAYER = GameTypes::Player::PLAYER_X;

#define SCORE_CHECK(SCORE)         \
if (GameTypes::WIN_POINTS <= SCORE)\
{                                  \
    SCORE = 0;                     \
    return true;                   \
}                                  \
SCORE = 1;                         \

namespace GameManagerHelpers
{
    void ChangeTurn()
    {
        if (CGameManager::PLAYER == GameTypes::Player::PLAYER_X)
        {
            CGameManager::PLAYER = GameTypes::Player::PLAYER_O;
        }
        else if (CGameManager::PLAYER == GameTypes::Player::PLAYER_O)
        {
            CGameManager::PLAYER = GameTypes::Player::PLAYER_X;
        }
    }
}

CGameManager::CGameManager() 
{

}

void CGameManager::MadeAMove(UStaticMeshComponent* block, const GameTypes::FieldPos& fieldPos)
{
    // Change material
    if (PLAYER == GameTypes::Player::PLAYER_X)
    {
        block->SetMaterial(0, CMaterialManager::GetInstance().TTT_Cross_Texture);
    }
    else
    {
        block->SetMaterial(0, CMaterialManager::GetInstance().TTT_O_Texture);
    }

    ACInGameHUD* InGameHUD = Cast<ACInGameHUD>(block->GetWorld()->GetFirstPlayerController()->GetHUD());
    if (InGameHUD)
    {
        if (CheckForWin(fieldPos, CGameManager::GetPlayer()))
        {
            InGameHUD->UpdateWinner(CGameManager::GetPlayer());
            PLAYER = GameTypes::Player::PLAYER_X;
            return;
        }
        GameManagerHelpers::ChangeTurn();
        InGameHUD->ChangeTurn(CGameManager::GetPlayer());
    }
}

bool CGameManager::CheckForWin(const GameTypes::FieldPos& fieldPosition, const GameTypes::Player owner,
                               const GameTypes::CheckFieldDirection checkDirection)
{
    using gameField = std::vector<std::vector<ATicTacToeBlock*>>;
    gameField field = CGameField::GetInstance().GetGameField();
    // need to collect 4 point in a row for win
    static int8 score = 0;

    if ((fieldPosition.i < 0 || fieldPosition.j < 0) || 
        (field.size() <= fieldPosition.i || field[fieldPosition.i].size() <= fieldPosition.j))
    {
        return false;
    }
    if (field[fieldPosition.i][fieldPosition.j]->GetPlayer() != owner && GameTypes::WIN_POINTS > score)
    {
        return false;
    }
    ++score;
    switch (checkDirection)
    {
    case GameTypes::CheckFieldDirection::IDLE:
        SCORE_CHECK(score)
        CheckForWin({ fieldPosition.i, fieldPosition.j + 1 }, owner, GameTypes::CheckFieldDirection::HORIZONTAL_RIGHT);
        CheckForWin({ fieldPosition.i, fieldPosition.j - 1 }, owner, GameTypes::CheckFieldDirection::HORIZONTAL_LEFT);
        SCORE_CHECK(score)
        CheckForWin({ fieldPosition.i + 1, fieldPosition.j }, owner, GameTypes::CheckFieldDirection::VERTICAL_UP);
        CheckForWin({ fieldPosition.i - 1, fieldPosition.j }, owner, GameTypes::CheckFieldDirection::VERTICAL_DOWN);
        SCORE_CHECK(score)
        CheckForWin({ fieldPosition.i + 1, fieldPosition.j + 1 }, owner, GameTypes::CheckFieldDirection::DIAGONAL_UP_RIGHT);
        CheckForWin({ fieldPosition.i - 1, fieldPosition.j - 1 }, owner, GameTypes::CheckFieldDirection::DIAGONAL_DOWN_LEFT);
        SCORE_CHECK(score)
        CheckForWin({ fieldPosition.i - 1, fieldPosition.j + 1 }, owner, GameTypes::CheckFieldDirection::DIAGONAL_UP_LEFT);
        CheckForWin({ fieldPosition.i + 1, fieldPosition.j - 1}, owner, GameTypes::CheckFieldDirection::DIAGONAL_DOWN_RIGHT);
        SCORE_CHECK(score)
        break;
    case GameTypes::CheckFieldDirection::HORIZONTAL_RIGHT:
        CheckForWin({ fieldPosition.i, fieldPosition.j + 1 }, owner, checkDirection);
        break;
    case GameTypes::CheckFieldDirection::HORIZONTAL_LEFT:
        CheckForWin({ fieldPosition.i, fieldPosition.j - 1 }, owner, checkDirection);
        break;
    case GameTypes::CheckFieldDirection::VERTICAL_UP:
        CheckForWin({ fieldPosition.i + 1, fieldPosition.j }, owner, checkDirection);
        break;
    case GameTypes::CheckFieldDirection::VERTICAL_DOWN:
        CheckForWin({ fieldPosition.i - 1, fieldPosition.j }, owner, checkDirection);
        break;
    case GameTypes::CheckFieldDirection::DIAGONAL_UP_RIGHT:
        CheckForWin({ fieldPosition.i + 1, fieldPosition.j + 1}, owner, checkDirection);
        break;
    case GameTypes::CheckFieldDirection::DIAGONAL_UP_LEFT:
        CheckForWin({ fieldPosition.i - 1, fieldPosition.j + 1 }, owner, checkDirection);
        break;
    case GameTypes::CheckFieldDirection::DIAGONAL_DOWN_RIGHT:
        CheckForWin({ fieldPosition.i + 1, fieldPosition.j - 1 }, owner, checkDirection);
        break;
    case GameTypes::CheckFieldDirection::DIAGONAL_DOWN_LEFT:
        CheckForWin({ fieldPosition.i - 1, fieldPosition.j - 1 }, owner, checkDirection);
        break;
    default:
        break;
    }
    return false;
}
