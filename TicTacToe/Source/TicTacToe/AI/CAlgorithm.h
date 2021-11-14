// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/Types.h"
#include "Game/CGameField.h"
#include "TicTacToeBlock.h"
#include <vector>

/**
 * 
 */
class TICTACTOE_API CAlgorithm
{
public:
    CAlgorithm() {};
    ~CAlgorithm() {};

    //realisation of minimax algorithm with alpha-beta pruning
    int32 Minimax(const GameTypes::FieldPos& pos, int32 depth, int32 alpha, int32 beta,
                  const GameTypes::ePlayer owner, const bool isMaximizing, const int32 fieldSnapshotRadius);
    std::vector<GameTypes::FieldPos> GetNodeChildsInRange(const GameTypes::FieldPos& pos, const int32 radius);
};

