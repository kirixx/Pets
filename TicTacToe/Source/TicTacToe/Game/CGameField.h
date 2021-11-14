#pragma once
#include "CoreMinimal.h"

#include <vector>
#include "TicTacToeBlock.h"
/**
 * 
 */
typedef std::vector<std::vector<ATicTacToeBlock*>> Field;
class TICTACTOE_API CGameField
{
public:

    CGameField(const CGameField&) = delete;

    static CGameField* GetInstance()
    {
        static CGameField gameField;
        return &gameField;
    }

    Field& GetGameField();
    void StoreLastMovePos(const GameTypes::FieldPos& pos, const GameTypes::ePlayer owner);
    const GameTypes::FieldPos& GetLastPosition(const GameTypes::ePlayer owner) const;

    std::vector<GameTypes::FieldPos> GetAvailableMoves();

private:
    CGameField() : mLastPosX(), mLastPosO(), mField() {};
    GameTypes::FieldPos mLastPosX;
    GameTypes::FieldPos mLastPosO;
    Field               mField;
};
