// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "pcg/engine/math/Vector4.hpp"
#include "MyPCG/PCGEnums.h"
#include "WFCGeneration4DData.generated.h"

/**
 * 
 */
UCLASS()
class PCG_WINDOW_API UWFCGeneration4DData : public UObject
{
	GENERATED_BODY()
	
    UFUNCTION(BlueprintCallable, CallInEditor, Category = "WFC Dimension Generation Data")
    void GenerateLevel() const;

    UPROPERTY(EditAnywhere, Category = "WFC Dimension Generation Data")
    int count;
    UPROPERTY(EditAnywhere, Category = "WFC Dimension Generation Data")
    TSubclassOf<AActor> block;
    UPROPERTY(EditAnywhere, Category = "WFC Dimension Generation Data")
    float nodeSize;
    UPROPERTY(EditAnywhere, Category = "WFC Dimension Generation Data")
    EExpansionMode expansionMode;
    UPROPERTY(EditAnywhere, Category = "WFC Dimension Generation Data", meta = (Bitmask, BitmaskEnum = "EGenerationAxis"))
    uint8 axes;
    UPROPERTY(EditAnywhere, Category = "WFC Dimension Generation Data")
    FVector startPosition;
    UPROPERTY(EditAnywhere, Category = "WFC Dimension Generation Data")
    unsigned int seed;

private:
    void SpawnNode(pcg::engine::math::Vector4 position, pcg::engine::utility::enums::Direction adjacentNodes) const;
    FString GetFolderName() const;

    mutable TMap<int, AActor*> dimensions{};
};
