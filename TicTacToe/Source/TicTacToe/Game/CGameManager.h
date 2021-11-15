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

    void SetAISide(const GameTypes::ePlayer& side) { mAISide = side; }
    GameTypes::ePlayer GetAISide() const { return mAISide; }

    void SetPlayerSide(const GameTypes::ePlayer side) { mPlayerSide = side; }
    GameTypes::ePlayer GetPlayerSide() const { return mPlayerSide; }

    GameTypes::GameMode GetGameMode() const { return mGameMode; }
    void SetGameMode(const GameTypes::GameMode gameMode);

private:
    void GetScoreByDirections(const GameTypes::FieldPos& fieldPosition, const GameTypes::ePlayer owner,
                              const GameTypes::eCheckFieldDirection checkDirection = GameTypes::eCheckFieldDirection::IDLE );
    
    CGameManager() : mAISide(GameTypes::GetRandomPlayer())
                    ,mPlayerSide(GameTypes::GetOppositePlayer(mAISide))
                    ,mGameMode(GameTypes::GameMode::HOTSEAT)
    {}

    bool IsMaxGlobalCounted();

    GameTypes::ePlayer mAISide;
    GameTypes::ePlayer mPlayerSide;
    GameTypes::GameMode mGameMode;
};
