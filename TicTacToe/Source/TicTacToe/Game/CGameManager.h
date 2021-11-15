#pragma once

#include "CoreMinimal.h"

#include "TicTacToeBlock.h"
#include "Types.h"
/**
 * 
 */

class TICTACTOE_API CGameManager
{
public:
    CGameManager(const CGameManager&) = delete;

    static CGameManager* GetInstance()
    {
        static CGameManager gameManager;
        return &gameManager;
    }

    static GameTypes::ePlayer sPlayerTurn; 
    static GameTypes::ePlayer GetPlayerTurn() { return sPlayerTurn; }

    static int32 sCurrentScore;
    static int32 sCurrentScoreForOpponent;
    static int32 sMaxScoreGlobal;

    bool CheckForWin(const GameTypes::FieldPos& fieldPosition, const GameTypes::ePlayer owner);

    int32 GetPositionScore(const GameTypes::FieldPos& fieldPosition, const GameTypes::ePlayer owner);
    
    void MadeAMove(ATicTacToeBlock* block);

    void SetAI(const GameTypes::ePlayer& side) { mAISide = side; }

    GameTypes::ePlayer GetAISide() const { return mAISide; }

    GameTypes::ePlayer GetPlayerSide() const { return mPlayerSide; }

private:
    void GetScoreByDirections(const GameTypes::FieldPos& fieldPosition, const GameTypes::ePlayer owner,
                              const GameTypes::eCheckFieldDirection checkDirection = GameTypes::eCheckFieldDirection::IDLE );
    
    CGameManager() : mAISide(GameTypes::ePlayer::PLAYER_NONE), mPlayerSide(GameTypes::ePlayer::PLAYER_NONE)
    {}

    bool IsMaxGlobalCounted();

    GameTypes::ePlayer mAISide;
    GameTypes::ePlayer mPlayerSide;
};
