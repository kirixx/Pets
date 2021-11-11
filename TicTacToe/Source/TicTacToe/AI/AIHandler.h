// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/Types.h"
#include "TicTacToeBlock.h"
/**
 * 
 */
class TICTACTOE_API AIHandler
{
public:
    AIHandler();

    ~AIHandler();

    void SetAISide(const GameTypes::ePlayer side) { mSide = side; }

public: 
    ATicTacToeBlock* Move();

private:
    int32 FindBestMove();

    GameTypes::ePlayer mSide;

};
