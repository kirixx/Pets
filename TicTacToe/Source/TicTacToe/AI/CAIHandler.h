// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/Types.h"
#include "TicTacToeBlock.h"
/**
 * 
 */
class TICTACTOE_API CAIHandler
{
public:
    CAIHandler() : mIsAIVsAi(false) {}

    ~CAIHandler() {}

    ATicTacToeBlock* Move();

    void SetIsAIVsAI(const bool isAIvsAI) { mIsAIVsAi = isAIvsAI; }

    GameTypes::FieldPos DoDumbMove();

private:
    bool mIsAIVsAi;

};
