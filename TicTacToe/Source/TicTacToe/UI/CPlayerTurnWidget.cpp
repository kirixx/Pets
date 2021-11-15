// Fill out your copyright notice in the Description page of Project Settings.


#include "CPlayerTurnWidget.h"
#include "Game/CGameManager.h"

namespace
{
    FText GetPlayerSideName(const GameTypes::ePlayer side)
    {
        FText retVal = FText::FromString("");
        if (side == GameTypes::ePlayer::PLAYER_X)
        {
            retVal = FText::FromString("Player: X");
        }
        else if (side == GameTypes::ePlayer::PLAYER_O)
        {
            retVal = FText::FromString("Player: O");
        }
        return retVal;
    }

    FText GetAISideName(const GameTypes::ePlayer side)
    {
        FText retVal = FText::FromString("");
        if (side == GameTypes::ePlayer::PLAYER_X)
        {
            retVal = FText::FromString("AI: X");
        }
        else if (side == GameTypes::ePlayer::PLAYER_O)
        {
            retVal = FText::FromString("AI: O");
        }
        return retVal;
    }
}

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

void UCPlayerTurnWidget::SetAISide(const GameTypes::ePlayer side)
{
    if (AISideTxt)
    {
        AISideTxt->SetText(GetAISideName(side));
    }
}

void UCPlayerTurnWidget::SetPlayerSide(const GameTypes::ePlayer side)
{
    if (PlayerSideTxt)
    {
        PlayerSideTxt->SetText(GetPlayerSideName(side));
    }
}

