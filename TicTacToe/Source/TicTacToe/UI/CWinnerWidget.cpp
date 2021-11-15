// Fill out your copyright notice in the Description page of Project Settings.

#include "Game/CGameManager.h"
#include "CWinnerWidget.h"

UCWinnerWidget::UCWinnerWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UCWinnerWidget::NativeConstruct() 
{
    Super::NativeConstruct();
}

bool UCWinnerWidget::Initialize()
{
    bool success = Super::Initialize();
    if (RestartButton)
    {
        RestartButton->OnClicked.AddDynamic(this, &UCWinnerWidget::RestartButtonClicked);
    }
    return success;
}

void UCWinnerWidget::ShowWinner(const GameTypes::ePlayer player)
{
    if (TXTWinner)
    {
        if (TXTWinner->Visibility == ESlateVisibility::Hidden)
        {
            TXTWinner->SetVisibility(ESlateVisibility::Visible);
        }
        if (player == GameTypes::ePlayer::PLAYER_X)
        {
            TXTWinner->SetText(FText::FromString("Player X wins"));
        }
        else if (player == GameTypes::ePlayer::PLAYER_O)
        {
            TXTWinner->SetText(FText::FromString("Player O wins"));
        }
        
    }

    if (WinnerFadeAnimation && GameOverAnimation)
    {
        PlayAnimation(WinnerFadeAnimation, 0.f, 1, EUMGSequencePlayMode::Forward, 1.f);
        PlayAnimation(GameOverAnimation, 0.f, 1, EUMGSequencePlayMode::Forward, 1.f);
    }
}

void UCWinnerWidget::RestartButtonClicked()
{
    CGameManager::sPlayerTurn = GameTypes::ePlayer::PLAYER_X;
}