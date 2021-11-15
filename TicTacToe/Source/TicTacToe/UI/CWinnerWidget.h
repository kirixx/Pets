// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Game/Types.h"
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"
#include "CWinnerWidget.generated.h"

/**
 * 
 */
UCLASS()
class TICTACTOE_API UCWinnerWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    UCWinnerWidget(const FObjectInitializer& ObjectInitializer);

    virtual void NativeConstruct() override;

    void ShowWinner(const GameTypes::ePlayer player);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
    class UTextBlock* TXTWinner;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    class UButton* RestartButton;

    UFUNCTION()
    void RestartButtonClicked();

protected:
    virtual bool Initialize();

private:
    UPROPERTY(Transient, meta = (BindWidgetAnim))
    UWidgetAnimation* WinnerFadeAnimation;
    UPROPERTY(Transient, meta = (BindWidgetAnim))
    UWidgetAnimation* GameOverAnimation;
};
