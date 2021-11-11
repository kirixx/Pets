// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Game/Types.h"
#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Components/WidgetComponent.h"
#include "CWinnerWidget.h"
#include "CPlayerTurnWidget.h"
#include "CInGameHUD.generated.h"


/**
 * 
 */
UCLASS()
class TICTACTOE_API ACInGameHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	ACInGameHUD();

	/** The Main Draw loop for the hud.  Gets called before any messaging.  Should be subclassed */
	virtual void DrawHUD() override;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	void UpdateWinner(const GameTypes::ePlayer player);

	void ChangeTurn(const GameTypes::ePlayer player);

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> WinnerWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> PlayerTurnWidget;

private:
	UCWinnerWidget* mWinnerWidget;
	UCPlayerTurnWidget* mPlayerTurnWidget;
};
