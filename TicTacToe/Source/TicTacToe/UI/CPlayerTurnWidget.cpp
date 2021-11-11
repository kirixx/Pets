// Fill out your copyright notice in the Description page of Project Settings.


#include "CPlayerTurnWidget.h"

UCPlayerTurnWidget::UCPlayerTurnWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UCPlayerTurnWidget::NativeConstruct()
{
    Super::NativeConstruct();
}

void UCPlayerTurnWidget::ChangeTurn(const GameTypes::Player& player)
{
    if (PlayerXTurn && PlayerOTurn)
    {
        if (player == GameTypes::Player::PLAYER_X)
        {
            PlayAnimation(PlayerXTurn, 0.f, 1, EUMGSequencePlayMode::Forward, 1.f);
        }
        else if (player == GameTypes::Player::PLAYER_O)
        {
            PlayAnimation(PlayerOTurn, 0.f, 1, EUMGSequencePlayMode::Forward, 1.f);
        }
    }
}
