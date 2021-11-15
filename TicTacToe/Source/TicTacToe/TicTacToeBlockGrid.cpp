// Copyright Epic Games, Inc. All Rights Reserved.

#include "TicTacToeBlockGrid.h"
#include "Components/TextRenderComponent.h"
#include "Engine/World.h"
#include "Game/CGameManager.h"
#include "Game/Types.h"


#define LOCTEXT_NAMESPACE "PuzzleBlockGrid"

ATicTacToeBlockGrid::ATicTacToeBlockGrid()
{
	// Create dummy root scene component
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;

	// Set defaults
	Size = GameTypes::GAME_FIELD_SIZE / 8; // 8 * 8
	BlockSpacing = 130.0f;
}

void ATicTacToeBlockGrid::GenerateGameField()
{
	const int32 NumBlocks = Size * Size;
	CGameField::GetInstance()->GetGameField().resize(Size);
	// Loop to spawn each block
	for (int32 i = 0; i < Size; ++i)
	{
		CGameField::GetInstance()->GetGameField()[i].resize(Size);
		for (int32 j = 0; j < Size; ++j)
		{
			const float XOffset = (i + j / NumBlocks) * BlockSpacing; // Divide by dimension
			const float YOffset = (j % NumBlocks) * BlockSpacing; // Modulo gives remainder

			// Make position vector, offset from Grid location
			const FVector BlockLocation = FVector(XOffset, YOffset, 0.f) + GetActorLocation();

			// Spawn a block
			if (ATicTacToeBlock* NewBlock = GetWorld()->SpawnActor<ATicTacToeBlock>(BlockLocation, FRotator(0, 0, 0)))
			{
				// Tell the block about its owner
				if (NewBlock != nullptr)
				{
					NewBlock->OwningGrid = this;
					NewBlock->SetFieldPos({ static_cast<SIZE_T>(i), static_cast<SIZE_T>(j) });
					NewBlock->SetPlayer(GameTypes::ePlayer::PLAYER_NONE);
				}
				CGameField::GetInstance()->GetGameField()[i][j] = NewBlock;
			}
		}
	}
}

void ATicTacToeBlockGrid::BeginPlay()
{
	Super::BeginPlay();
	GenerateGameField();
	// Number of blocks
}


void ATicTacToeBlockGrid::AddScore()
{
	// Increment score
	Score++;
}

#undef LOCTEXT_NAMESPACE
