// Fill out your copyright notice in the Description page of Project Settings.


#include "CPlayerTurnWidget.h"

UCPlayerTurnWidget::UCPlayerTurnWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UCPlayerTurnWidget::NativeConstruct()
{
    Super::NativeConstruct();
}

void UCPlayerTurnWidget::ChangeTurn(const GameTypes::ePlayer player)
{
    if (PlayerXTurn && PlayerOTurn)
    {
        if (player == GameTypes::ePlayer::PLAYER_X)
        {
            PlayAnimation(PlayerXTurn, 0.f, 1, EUMGSequencePlayMode::Forward, 1.f);
        }
        else if (player == GameTypes::ePlayer::PLAYER_O)
        {
            PlayAnimation(PlayerOTurn, 0.f, 1, EUMGSequencePlayMode::Forward, 1.f);
        }
    }
}
