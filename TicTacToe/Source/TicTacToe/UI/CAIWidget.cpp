// Fill out your copyright notice in the Description page of Project Settings.


#include "CAIWidget.h"

void UCAIWidget::NativeConstruct()
{
    Super::NativeConstruct();
}

bool UCAIWidget::Initialize()
{
    bool success = Super::Initialize();
    if (VsAiButton)
    {
        VsAiButton->OnClicked.AddDynamic(this, &UCAIWidget::VsAiButtonClicked);
    }

    if (AIVsAIButton)
    {
        AIVsAIButton->OnClicked.AddDynamic(this, &UCAIWidget::AIVsAIButtonClicked);
    }

    if (HotseatButton)
    {
        HotseatButton->OnClicked.AddDynamic(this, &UCAIWidget::HotseatButtonClicked);
    }

    if (RestartButton)
    {
        RestartButton->OnClicked.AddDynamic(this, &UCAIWidget::RestartButtonClicked);
    }
    return success;
}

void UCAIWidget::VsAiButtonClicked()
{
    CGameManager* gameManagerInstance = CGameManager::GetInstance();
    gameManagerInstance->SetAISide(GameTypes::GetRandomPlayer());
    gameManagerInstance->SetPlayerSide(GameTypes::GetOppositePlayer(gameManagerInstance->GetAISide()));
    gameManagerInstance->SetGameMode(GameTypes::GameMode::PLAYER_VS_AI);
}

void UCAIWidget::AIVsAIButtonClicked()
{
    CGameManager* gameManagerInstance = CGameManager::GetInstance();
    gameManagerInstance->SetPlayerSide(GameTypes::ePlayer::PLAYER_NONE);
    gameManagerInstance->SetGameMode(GameTypes::GameMode::AI_VS_AI);

}

void UCAIWidget::HotseatButtonClicked()
{
    CGameManager* gameManagerInstance = CGameManager::GetInstance();
    gameManagerInstance->SetPlayerSide(gameManagerInstance->GetPlayerTurn());
    gameManagerInstance->SetGameMode(GameTypes::GameMode::HOTSEAT);
}

void UCAIWidget::RestartButtonClicked()
{
    CGameManager::sPlayerTurn = GameTypes::ePlayer::PLAYER_X;
}