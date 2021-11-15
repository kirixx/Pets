// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Game/CGameManager.h"
#include "CAIWidget.generated.h"

/**
 * 
 */
UCLASS()
class TICTACTOE_API UCAIWidget : public UUserWidget
{
    GENERATED_BODY()

public:

    virtual void NativeConstruct() override;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    class UButton* VsAiButton;
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    class UButton* AIVsAIButton;
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    class UButton* HotseatButton;
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    class UButton* RestartButton;

    UFUNCTION()
    void VsAiButtonClicked();
    UFUNCTION()
    void AIVsAIButtonClicked();
    UFUNCTION()
    void HotseatButtonClicked();

    UFUNCTION()
    void RestartButtonClicked();

protected:
    virtual bool Initialize();
};
