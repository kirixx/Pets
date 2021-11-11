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
    CGameManager();
    ~CGameManager() {}

    static GameTypes::ePlayer sPlayerTurn; 
    static GameTypes::ePlayer GetPlayer() { return sPlayerTurn; }

    bool CheckForWin(const GameTypes::FieldPos& fieldPosition, const GameTypes::ePlayer owner,
                     const GameTypes::eCheckFieldDirection checkDirection = GameTypes::eCheckFieldDirection::IDLE);
    
    void MadeAMove(ATicTacToeBlock* block);
};
