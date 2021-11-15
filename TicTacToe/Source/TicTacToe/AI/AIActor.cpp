// Fill out your copyright notice in the Description page of Project Settings.


#include "AIActor.h"

// Sets default values

//Spawned only if vs AI chosen BP TTT_MainMenu
AAIActor::AAIActor()
	: mAIHandler()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AAIActor::BeginPlay()
{
    Super::BeginPlay();
    float DeltaTime = 2;
    SetActorTickInterval(DeltaTime);
}

// Called every frame
void AAIActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    auto gameManagerInstance = CGameManager::GetInstance();
    mAIHandler.SetIsAIVsAI(IsAIVSAI);

    if (IsPlayerVSAi || IsAIVSAI)
    {
        CGameManager::GetInstance()->MadeAMove(mAIHandler.Move());
    }
}