// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class TICTACTOE_API CMaterialManager
{
public:
    CMaterialManager(const CMaterialManager&) = delete;
    CMaterialManager(const CMaterialManager&&) = delete;
    CMaterialManager& operator=(const CMaterialManager&) = delete;
    CMaterialManager& operator=(CMaterialManager&&) = delete;

    ~CMaterialManager();

    static CMaterialManager& GetInstance()
    {
        static CMaterialManager gameField;
        return gameField;
    }

    void InitializeMaterials();

    /** Pointer to white material used on the focused block */
    UPROPERTY()
    class UMaterial* BaseMaterial;

    UPROPERTY()
    class UMaterial* TTT_Cross_Texture;

    UPROPERTY()
    class UMaterial* TTT_O_Texture;

    /** Pointer to blue material used on inactive blocks */
    UPROPERTY()
    class UMaterialInstance* BlueMaterial;

    /** Pointer to orange material used on active blocks */
    UPROPERTY()
    class UMaterialInstance* OrangeMaterial;

private:
    CMaterialManager();
};
