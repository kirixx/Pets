// Copyright Epic Games, Inc. All Rights Reserved.

#include "TicTacToeBlock.h"
#include "TicTacToeBlockGrid.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Materials/MaterialInstance.h"
#include "Game/CGameManager.h"


ATicTacToeBlock::ATicTacToeBlock() 
	: mOwner(GameTypes::ePlayer::PLAYER_NONE)
	, mGameFieldPos({0, 0})
{
	//// Structure to hold one-time initialization
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> PlaneMesh;
		FConstructorStatics()
			: PlaneMesh(TEXT("/Game/TicTacToe/Meshes/TicTacToeCube.TicTacToeCube"))
		{
		}
	};
	static FConstructorStatics ConstructorStatics;

	// Create dummy root scene component
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;
	// Create static mesh component
	BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockMesh0"));
	BlockMesh->SetStaticMesh(ConstructorStatics.PlaneMesh.Get());
	BlockMesh->SetRelativeScale3D(FVector(0.50f, 0.50f, 0.25f));
	BlockMesh->SetRelativeLocation(FVector(0.f,0.f,25.f));
	BlockMesh->SetMaterial(0, CMaterialManager::GetInstance().BaseMaterial);
	BlockMesh->SetupAttachment(DummyRoot);
	BlockMesh->OnClicked.AddDynamic(this, &ATicTacToeBlock::BlockClicked);
	BlockMesh->OnInputTouchBegin.AddDynamic(this, &ATicTacToeBlock::OnFingerPressedBlock);
}

void ATicTacToeBlock::BlockClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked)
{
	HandleClicked();
}


void ATicTacToeBlock::OnFingerPressedBlock(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent)
{
	HandleClicked();
}

void ATicTacToeBlock::HandleClicked()
{
	// Check we are not already active
	CGameManager* gameManagerInstance = CGameManager::GetInstance();

	if (GameTypes::GameMode::HOTSEAT == gameManagerInstance->GetGameMode())
	{
		gameManagerInstance->SetPlayerSide(gameManagerInstance->GetPlayerTurn());
	}

	if (GetPlayer() == GameTypes::ePlayer::PLAYER_NONE &&
		CGameManager::GetInstance()->GetPlayerSide() == CGameManager::GetPlayerTurn())
	{
		SetPlayer(CGameManager::GetInstance()->GetPlayerSide());
		// Tell the Grid
		if (OwningGrid != nullptr)
		{
			OwningGrid->AddScore();
		}
		CGameManager::GetInstance()->OnMoveMade(this);
	}
}

void ATicTacToeBlock::Highlight(bool bOn)
{
	// Do not highlight if the block has already been activated.
	if (bIsActive)
	{
		return;
	}
}


