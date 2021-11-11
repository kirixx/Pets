// Fill out your copyright notice in the Description page of Project Settings.


#include "CMaterialManager.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/MaterialInstance.h"

CMaterialManager::CMaterialManager()
{
    InitializeMaterials();
}

void CMaterialManager::InitializeMaterials()
{
    // Structure to hold one-time initialization
    struct FConstructorStatics
    {
        ConstructorHelpers::FObjectFinderOptional<UMaterial> BaseMaterial;
        ConstructorHelpers::FObjectFinderOptional<UMaterial> TTT_Cross_Texture;
        ConstructorHelpers::FObjectFinderOptional<UMaterial> TTT_O_Texture;
        ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> BlueMaterial;
        ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> OrangeMaterial;
        FConstructorStatics()
            : BaseMaterial(TEXT("Material'/Game/TicTacToe/Meshes/BaseMaterial.BaseMaterial'"))
            , TTT_Cross_Texture(TEXT("Material'/Game/TicTacToe/Meshes/TTT_Cross_Texture.TTT_Cross_Texture'"))
            , TTT_O_Texture(TEXT("Material'/Game/TicTacToe/Meshes/TTT_O_Texture.TTT_O_Texture'"))
            , BlueMaterial(TEXT("Material'/Game/TicTacToe/Meshes/BlueMaterial.BlueMaterial'"))
            , OrangeMaterial(TEXT("Material'/Game/TicTacToe/Meshes/OrangeMaterial.OrangeMaterial'"))
        {
        }
    };
    static FConstructorStatics ConstructorStatics;
    // Save a pointer to the orange material
    BaseMaterial = ConstructorStatics.BaseMaterial.Get();
    TTT_Cross_Texture = ConstructorStatics.TTT_Cross_Texture.Get();
    TTT_O_Texture = ConstructorStatics.TTT_O_Texture.Get();
    BlueMaterial = ConstructorStatics.BlueMaterial.Get();
    OrangeMaterial = ConstructorStatics.OrangeMaterial.Get();
}

CMaterialManager::~CMaterialManager()
{
}
