// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Game/Types.h"
#include "Renderer/CMaterialManager.h"
#include "TicTacToeBlock.generated.h"

/** A block that can be clicked */
UCLASS(minimalapi)
class ATicTacToeBlock : public AActor
{

	GENERATED_BODY()

	/** Dummy root component */
	UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* DummyRoot;

	/** StaticMesh component for the clickable block */
	UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* BlockMesh;

public:
	ATicTacToeBlock();

	/** Are we currently active? */
	bool bIsActive;

	/** Grid that owns us */
	UPROPERTY()
	class ATicTacToeBlockGrid* OwningGrid;

	/** Handle the block being clicked */
	UFUNCTION()
	void BlockClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked);

	/** Handle the block being touched  */
	UFUNCTION()
	void OnFingerPressedBlock(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent);

	void HandleClicked();

	void Highlight(bool bOn);

	void SetFieldPos(const GameTypes::FieldPos& fieldPosition) { mGameFieldPos = fieldPosition; }

	GameTypes::FieldPos GetGameFieldPos() const { return mGameFieldPos; }

	void SetPlayer(const GameTypes::ePlayer player) { mOwner = player; }

	GameTypes::ePlayer GetPlayer() const { return mOwner; }

public:
	/** Returns DummyRoot subobject **/
	FORCEINLINE class USceneComponent* GetDummyRoot() const { return DummyRoot; }
	/** Returns BlockMesh subobject **/
	FORCEINLINE class UStaticMeshComponent* GetBlockMesh() const { return BlockMesh; }
	
private:

	GameTypes::ePlayer		mOwner;
	GameTypes::FieldPos		mGameFieldPos;
};



