#pragma once

#include "CoreMinimal.h"

#include "../TicTacToeBlock.h"
#include "Types.h"
/**
 * 
 */
class TICTACTOE_API CGameManager
{
public:
    CGameManager();
    ~CGameManager() {}

    static GameTypes::Player PLAYER; 
    static GameTypes::Player GetPlayer() { return PLAYER; }

    bool CheckForWin(const GameTypes::FieldPos& fieldPosition, const GameTypes::Player owner,
                     const GameTypes::CheckFieldDirection checkDirection = GameTypes::CheckFieldDirection::IDLE);
    
    void MadeAMove(UStaticMeshComponent* block, const GameTypes::FieldPos& fieldPos);
};
