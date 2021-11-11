#pragma once
#include "CoreMinimal.h"

#include <vector>
#include "../TicTacToeBlock.h"
/**
 * 
 */
typedef std::vector<std::vector<ATicTacToeBlock*>> Field;
class TICTACTOE_API CGameField
{
public:

    CGameField(const CGameField&) = delete;
    CGameField(const CGameField&&) = delete;
    CGameField& operator=(const CGameField&) = delete;
    CGameField& operator=(CGameField&&) = delete;


    static CGameField& GetInstance()
    {
        static CGameField gameField;
        return gameField;
    }

    Field& GetGameField();

private:
    CGameField() {};
    Field mField;
};
